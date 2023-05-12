#version 330 core
layout (location = 0) in vec4 aPos;
uniform mat4 projection, rotX, rotY, rotZ, moveXYZ, scale;

flat out vec3 startPos;
out vec3 vertPos;

void main()
{
  mat4 model = moveXYZ * rotX * rotY * rotZ * scale;
  gl_Position = projection * model * aPos;
  vertPos = gl_Position.xyz / gl_Position.w;
  startPos = vertPos;
}
