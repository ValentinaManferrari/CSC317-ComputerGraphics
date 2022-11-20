// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Calculate where the light is
  float theta = 0.25 * M_PI * animation_seconds;
  vec4 light = view * vec4(4*cos(theta), 4, 4*sin(theta), 0.75);
  
  // Blinn Phong parameters
  vec3 ka, ks, kd;
  float p;
  if(is_moon){
	  ka = vec3(0.1, 0.1, 0.1);
	  ks = vec3(0.8, 0.8, 0.8);
	  kd = vec3(0.85, 0.85, 0.85);
	  p = 1000;
  }else{ 
      // Creating MARS planet
	  ka = vec3(0.1, 0.1, 0.1);
	  ks = vec3(0.8, 0.8, 0.8);
	  kd = vec3(0.9, 0.1, 0.1); // red
	  p = 2000; // matte

	  float bump_height = bump_height(is_moon, sphere_fs_in);
      // Set height thresholds
      float lower_bound = 1.0;
      float higher_bound = 1.05;

	  // Midrange color is orange
	  if (bump_height > lower_bound && bump_height < higher_bound) {
          ka = vec3(0.2, 0.2, 0.2);
		  ks = vec3(1, 0.5, 0); 
		  kd = vec3(1, 0.5, 0); 
      }
	  // Highest peaks color is yellow
      else if (bump_height > higher_bound) {
		  ka = vec3(0.2, 0.2, 0.2);
		  ks = vec3(1.0, 0.7, 0.2);
          kd = vec3(1.0, 0.7, 0.2); 
      }
  }

  // Add bumps on surface
  // Reference: https://github.com/karansher/computer-graphics-shader-pipeline#bump-and-normal-maps
  vec3 T, B;
  tangent(sphere_fs_in, T, B);
  vec3 bump = bump_position(is_moon, sphere_fs_in);

  float e = 0.0001;
  vec3 dp_dt = (bump_position (is_moon, sphere_fs_in + e * T) - bump) / e;
  vec3 dp_db = (bump_position (is_moon, sphere_fs_in + e * B) - bump) / e;
  vec3 perceived_normal = normalize(cross(dp_dt, dp_db));

  // convert perceived_normal to positive value if needed
  if ( dot(perceived_normal, sphere_fs_in) < 0 ) {
    perceived_normal *= -1;
  }

  mat4 model = model(is_moon, animation_seconds);

  vec3 n = normalize((transpose(inverse(view)) * transpose(inverse(model)) * vec4(perceived_normal,1)).xyz );
  vec3 v = -normalize(view_pos_fs_in.xyz); // from a point on surface to the eye
  vec3 l = normalize(light.xyz - view_pos_fs_in.xyz); // from a point on surface to the light

  color = blinn_phong(ka, kd, ks, p, n, v, l);

  // Generate Clouds
  if (!is_moon){
      vec3 seed = 0.1 * vec3(10, 80, 10);
      // density = 2, frequency = 0.1, amplitude = 1.5, rotation_period = 5
      float cloud_anim_val = 1.5 * sin(0.1 * M_PI * animation_seconds);
      float clouds = 0.2 * improved_perlin_noise((2 + cloud_anim_val) * seed * (rotate_about_y(mod(animation_seconds, 5.0) * 2 * M_PI / 5.0) * vec4(sphere_fs_in, 1)).xyz);
      if (clouds > 0.02){
          ka = vec3(clouds, clouds, clouds);
          kd = vec3(clouds, clouds, clouds);
          ks = vec3(0.0, 0.0, 0.0);
          n = normalize(normal_fs_in);
          vec3 cloud_overlay = blinn_phong(ka, kd, ks, p, n, v, l);
          color += 10.0 * cloud_overlay;
      }
  }
  /////////////////////////////////////////////////////////////////////////////
}
