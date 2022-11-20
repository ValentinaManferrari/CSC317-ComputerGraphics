// Construct the model transformation matrix. The moon should orbit around the
// origin. The other object should stay still.
//
// Inputs:
//   is_moon  whether we're considering the moon
//   time  seconds on animation clock
// Returns affine model transformation as 4x4 matrix
//
// expects: identity, rotate_about_y, translate, PI
mat4 model(bool is_moon, float time)
{
  /////////////////////////////////////////////////////////////////////////////
  if (is_moon){
    // Scale moon to be 30% of Earth size
    mat4 scale = uniform_scale(0.3);
    
    // Define Moon's revolution around Earth
    float theta = 0.5 * M_PI * time;
    mat4 rotation = rotate_about_y(theta);
    
    // Define Moon's rotation on itself
    mat4 translation = transpose(translate(vec3(-2*cos(theta), 0, 2*sin(theta))));
    
    // Sum up all transformations
    mat4 res = translation * scale * rotation;
    return res; 
  }
  else{
    return identity();
  }
  /////////////////////////////////////////////////////////////////////////////
}
