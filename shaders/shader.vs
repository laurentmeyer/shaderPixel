#version 330 core
layout(location = 0) in vec3 aPos;

out vec2 fragCoord;
uniform vec3 iResolution;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


void main() {
  // gl_Position = vec4(aPos, 1.f);
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.f);
  fragCoord = gl_Position.xy;
  // fragCoord = (gl_Position.xy / 2.f + 0.5f) * iResolution.xy;
}