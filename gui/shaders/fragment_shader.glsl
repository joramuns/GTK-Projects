#version 330 core
out vec4 FragColor;
uniform bool round_vertices;
uniform vec4 color;

void main()
{
  vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
  if (round_vertices && dot(circCoord, circCoord) > 1.0) {
      discard;
  }
  FragColor = color;
}

