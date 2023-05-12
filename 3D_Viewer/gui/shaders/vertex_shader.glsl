#version 330 core
layout (location = 0) in vec4 aPos;
uniform mat4 projection, rotX, rotY, rotZ, moveXYZ, scale;

void main()
{
  mat4 model = moveXYZ * rotX * rotY * rotZ * scale;
  gl_Position = projection * model * aPos;
}
