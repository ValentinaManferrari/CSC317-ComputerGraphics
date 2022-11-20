// Filter an input value to perform an even smoother step. This function should
// be a quintic polynomial with improved_smooth_step(0) = 0,
// improved_smooth_step(1) = 1, and zero first _and_ second derivatives at f=0
// and f=1. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   f  input value
// Returns filtered output value
float improved_smooth_step( float f)
{
  /////////////////////////////////////////////////////////////////////////////
  /* General Cubic Polynomial: f(x) = ax^5 + bx^4 + cx^3 + dx^2 + ex + f
  * Its Prime Derivative:      f'(x) = 5ax^4 + 4bx^3 + 3cx^2 + 2dx + e
  * Its Second Derivative:     f''(x) = 20ax^3 + 12bx^2 + 6cx
  *
  * f(0) = 0   -->  f = 0
  * f'(0) = 0  -->  e = 0
  * f''(0) = 0 -->  d = 0
  * f(1) = 1   -->  a + b + c = 1
  * f'(1) = 0  -->  5a + 4b + 3c = 0
  * f''(1) = 0  --> 20a + 12b + 6c  = 0
  *
  * 3 equations & 3 unknowns --> a = 6, b = -15, c = 10
  * The wanted Polynomial is: f(x) = 6x^5 - 15x^4 + 10x^3
  */

  int a = 6;
  int b = -15;
  int c = 10;
  
  // Reference: https://en.wikipedia.org/wiki/Smoothstep
  if (f <= 0) {
      return 0;
  }
  if (f >= 1) {
      return 1;
  } 
  return a * pow(f, 5) + b * pow(f, 4) + c * pow(f, 3);
  /////////////////////////////////////////////////////////////////////////////
}
vec3 improved_smooth_step( vec3 f)
{
  /////////////////////////////////////////////////////////////////////////////
  return vec3(improved_smooth_step(f.x), improved_smooth_step(f.y), improved_smooth_step(f.z));;
  /////////////////////////////////////////////////////////////////////////////
}
