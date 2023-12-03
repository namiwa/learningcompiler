#version 330 core

out vec4 fragColor;

in vec2 v;

void main() {
  vec4 color = vec4(1.0, 0.5, 1.0, 0.5);
  fragColor = color;
}

