// Filter an input value to perform a smooth step. This function should be a
// cubic polynomial with smooth_step(0) = 0, smooth_step(1) = 1, and zero first
// derivatives at f=0 and f=1. 
//
// Inputs:
//   f  input value
// Returns filtered output value
float smooth_step( float f)
{
  /////////////////////////////////////////////////////////////////////////////
  /* General Cubic Polynomial: f(x) = ax^3 + bx^2 + cx + d
   * Its Prime Derivative:     f'(x) = 3ax^2 + 2bx + c
   *
   * f(0) = 0   -->  d = 0
   * f'(0) = 0  -->  c = 0
   * f(1) = 1   -->  a + b = 1
   * f'(1) = 0  -->  3a + 2b = 0
   *
   * 2 equations & 2 unknowns --> a = -2, b = 3
   * The wanted Polynomial is: f(x) = -2x^3 + 3x^2
   */
   int a = -2;
   int b = 3;
   
   // Reference: https://en.wikipedia.org/wiki/Smoothstep
   if (f <= 0) {
        return 0;
   }
   if (f >= 1) {
        return 1;
   } 
   return a * pow(f, 3) + b * pow(f, 2);
  /////////////////////////////////////////////////////////////////////////////
}

vec3 smooth_step( vec3 f)
{
  /////////////////////////////////////////////////////////////////////////////
  return vec3(smooth_step(f.x), smooth_step(f.y), smooth_step(f.z));
  /////////////////////////////////////////////////////////////////////////////
}
