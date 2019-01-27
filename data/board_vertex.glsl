#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

out vec3 vertexPosition_worldspace;
out vec3 Normal_cameraspace;
out vec3 LightDirection_cameraspace;
out vec3 position_modelspace;

out struct Light
{
  vec3 position;
  vec3 direction;
} light;

void main()
{
  gl_Position = P * V * M * vec4(vertexPosition_modelspace,1);
  position_modelspace = vertexPosition_modelspace;

  vertexPosition_worldspace = (P*V*M*vec4(vertexPosition_modelspace,1)).xyz;
  vec3 vertexPosition_cameraspace = (V*M*vec4(vertexPosition_modelspace,1)).xyz;

  Normal_cameraspace = (V * M * vec4(vertexNormal_modelspace,0)).xyz;

  light.position = vec3(3.0,12.0,-4.0);
  vec3 LightPosition_cameraspace = ( V * vec4(light.position,1)).xyz;
  light.direction = LightPosition_cameraspace + -vertexPosition_cameraspace;
};
