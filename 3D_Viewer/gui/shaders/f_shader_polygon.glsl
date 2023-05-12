#version 330 core

flat in vec3 startPos;
in vec3 vertPos;

out vec4 FragColor;
uniform vec4 color;
uniform bool dashedLine;
uniform float dashSize;
uniform float gapSize;
uniform vec2 resolution;

void main()
{
  if (dashedLine) {
    vec2 dir  = (vertPos.xy - startPos.xy) * resolution / 2.0;
    float dist = length(dir);
    if (fract(dist / (dashSize + gapSize)) > dashSize / (dashSize + gapSize))
        discard;
  }

  FragColor = color;
}