// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
  /////////////////////////////////////////////////////////////////////////////
  // Random distrubution over a sphere.
  vec2 rand = random2(seed);
  float theta = M_PI * rand.x;	    // Inclination level in range [0, PI]
  float phi = 2 * M_PI * rand.y;	// Azimuthal angle in range [0, 2PI]

  float x = cos(phi) * sin(theta);
  float y = sin(phi) * sin(theta);
  float z = cos(theta);

  return normalize(vec3(x, y, z));
  /////////////////////////////////////////////////////////////////////////////
}
