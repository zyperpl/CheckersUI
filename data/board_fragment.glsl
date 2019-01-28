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

uniform vec2 selected;

const float SCALE = 2;

void main()
{
  float cont = contrast;

  vec3 n = normalize(Normal_cameraspace);

  vec3 l = normalize(light.direction);
  float dist = length(vertexPosition_worldspace - light.position);

  float cosTheta = clamp(dot(n,l), 0.0, 1.0);

  float sx = selected.x;
  if (sx < 0) sx -= SCALE;
  sx = (int(sx/SCALE))*SCALE;

  float sy = selected.y;
  if (sy < 0) sy -= SCALE;
  sy = (int(sy/SCALE))*SCALE;

  float vx = vertexPosition_worldspace.x;
  float vz = vertexPosition_worldspace.z;

  vec3 col = vec3(1.0,1.0,1.0);
  vec3 scolor = vec3(0,0,0);

  if (sx <= vx && sx+SCALE >= vx 
  &&  sy <= vz && sy+SCALE >= vz) {
    scolor = vec3(0.1,0.6,1.0);
    cont = 10.0;
  }

  vec3 fieldColor = col * ((cos((a+position_modelspace.z)*b))*(cos((a+position_modelspace.x)*b)))*cont;

  vec3 modelColor = vec3(0.2,0.2,0.2)*cosTheta/pow(dist,2)*200;
  color = vec4(modelColor*fieldColor+scolor, 0.1);
}
