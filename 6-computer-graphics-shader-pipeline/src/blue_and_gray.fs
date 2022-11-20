// Set the pixel color to blue or gray depending on is_moon.
//
// Uniforms:
uniform bool is_moon;
// Outputs:
out vec3 color;
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  if (is_moon){
      color = vec3(0.2, 0.2, 0.2); // gray
  }
  else{
      color = vec3(0.0, 0.0, 1.0); // blue
  }
  /////////////////////////////////////////////////////////////////////////////
}
