#version 330 core

out vec4 color;

in vec3 vertexPosition_worldspace;
in vec3 Normal_cameraspace;
in vec3 position_modelspace;

in struct Light
{
  vec3 position;
  vec3 direction;
} light;

float a = 1.0;
float b = 3.1415/2.;
uniform float contrast;

void main()
{
  vec3 n = normalize(Normal_cameraspace);

  vec3 l = normalize(light.direction);
  float dist = length(vertexPosition_worldspace - light.position);

  float cosTheta = clamp(dot(n,l), 0.0, 1.0);

  vec3 fieldColor = vec3(1.0,1.0,1.0) 
    * ((cos((a+position_modelspace.z)*b))*(cos((a+position_modelspace.x)*b)))*contrast;

  vec3 modelColor = vec3(0.2,0.2,0.2)*cosTheta/pow(dist,2)*200;
  color = vec4(modelColor*fieldColor, 0.1);
}
