#version 330 core

out vec3 color;

in vec3 vertexPosition_worldspace;
in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;
in float distanceToLight;

uniform vec3 pawnColor;

void main()
{
  vec3 n = normalize(Normal_cameraspace);
  vec3 l = normalize(LightDirection_cameraspace);

  float cosTheta = dot(n,l);

  vec3 modelColor = vec3(0.4,0.4,0.4) + pawnColor*cosTheta;
  color = modelColor;
}
