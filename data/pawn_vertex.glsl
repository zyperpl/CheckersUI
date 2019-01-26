#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

out vec3 vertexPosition_worldspace;
out vec3 Normal_cameraspace;
out vec3 LightDirection_cameraspace;
out float distanceToLight;

void main()
{
  gl_Position = P * V * M * vec4(vertexPosition_modelspace,1);

  vertexPosition_worldspace = (P*V*M*vec4(vertexPosition_modelspace,1)).xyz;
  vec3 vertexPosition_cameraspace = (V*M*vec4(vertexPosition_modelspace,1)).xyz;

  Normal_cameraspace = (V * M * vec4(vertexNormal_modelspace,0)).xyz;

  vec3 LightPosition_worldspace = vec3(30.0,5.0,-20.0);
  vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace,1)).xyz;
  distanceToLight = distance(LightPosition_worldspace, vertexPosition_worldspace);
  LightDirection_cameraspace = LightPosition_cameraspace + -vertexPosition_cameraspace;
};
