// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  /////////////////////////////////////////////////////////////////////////////
  // Reference: Textbook Chapter 11.5.3 (Turbulence)
  float height_factor = 2.5;
  float obj_factor, noise;

  if (is_moon){
    obj_factor = 5;
    noise = sqrt( abs (1 + cos( s.x + obj_factor * improved_perlin_noise(height_factor * s) ) / 3));

    return smooth_heaviside(noise, 1.5);
  
  }else{
    obj_factor = 10;
    noise = sqrt( abs (1 + cos( s.x + obj_factor * improved_perlin_noise(height_factor * s) ) / 5));

    return smooth_heaviside(noise, 0.5);
  } 
  /////////////////////////////////////////////////////////////////////////////
}
