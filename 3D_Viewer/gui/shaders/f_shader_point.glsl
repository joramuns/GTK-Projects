#version 330 core
out vec4 FragColor;
uniform vec4 color;
uniform bool roundVertices;


void main()
{
  vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
  if (roundVertices && dot(circCoord, circCoord) > 1.0) {
      discard;
  }
  FragColor = color;
}