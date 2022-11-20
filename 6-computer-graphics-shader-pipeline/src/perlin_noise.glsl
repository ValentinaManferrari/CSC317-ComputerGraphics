// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
float perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Reference: https://en.wikipedia.org/wiki/Perlin_noise
  
  vec3 base = floor(st);
  vec3 top = ceil(st);
  vec3 frac = fract(st);

  // Unit cube creation around seed point
  vec3 p_000 = base;
  vec3 p_001 = vec3(base.xy, top.z);
  vec3 p_010 = vec3(base.x, top.y, base.z);
  vec3 p_011 = vec3(base.x, top.y, top.z);
  vec3 p_100 = vec3(top.x, base.yz);
  vec3 p_101 = vec3(top.x, base.y, top.z);
  vec3 p_110 = vec3(top.x, top.y, base.z);
  vec3 p_111 = vec3(top.x, top.y, top.z);

  // Gradient creation at each vertex
  vec3 g_000 = random_direction(p_000);
  vec3 g_001 = random_direction(p_001);
  vec3 g_010 = random_direction(p_010);
  vec3 g_011 = random_direction(p_011);
  vec3 g_100 = random_direction(p_100);
  vec3 g_101 = random_direction(p_101);
  vec3 g_110 = random_direction(p_110);  
  vec3 g_111 = random_direction(p_111);

  // Distance vectors 
  vec3 d_000 = normalize(st - p_000);
  vec3 d_001 = normalize(st - p_001);
  vec3 d_010 = normalize(st - p_010);
  vec3 d_011 = normalize(st - p_011);
  vec3 d_100 = normalize(st - p_100);
  vec3 d_101 = normalize(st - p_101);
  vec3 d_110 = normalize(st - p_110);
  vec3 d_111 = normalize(st - p_111);

  // Influence values at each vertex
  float i_000 = dot(g_000, d_000);
  float i_001 = dot(g_001, d_001);
  float i_010 = dot(g_010, d_010);
  float i_011 = dot(g_011, d_011);
  float i_100 = dot(g_100, d_100);
  float i_101 = dot(g_101, d_101);
  float i_110 = dot(g_110, d_110);
  float i_111 = dot(g_111, d_111);

  // Interpolation
  vec3 iw = smooth_step(frac);  

  float ip_x1, ip_x2, ip_y1, ip_y2, ip_value;
 
  ip_x1 = mix(i_000, i_100, iw.x);
  ip_x2 = mix(i_010, i_110, iw.x);
  ip_y1 = mix(ip_x1, ip_x2, iw.y);

  ip_x1 = mix(i_001, i_101, iw.x);
  ip_x2 = mix(i_011, i_111, iw.x);
  ip_y2 = mix(ip_x1, ip_x2, iw.y);

  ip_value = mix(ip_y1, ip_y2, iw.z);
  return ip_value / sqrt(3);
  /////////////////////////////////////////////////////////////////////////////
}

