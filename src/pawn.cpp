#include "model.hpp"
#include "pawn.hpp"


Pawn::Pawn(glm::vec3 pos, Color c) :
    acolor{c}, color{c}
{
  this->position = pos;
  this->target = pos;
  this->rotation = glm::vec3(0,0,0);
  this->scale = glm::vec3(0.8,1.0,0.8);

  uint32_t sides = 100+rand()%256;
  double shrink  = 0.9+((double)(rand()%100)/100.0);

  this->model.reset(Model::generatePawn(sides, shrink));
  //printf("%d %f\n", sides, shrink);
  this->program = ShaderManager::getProgram(2, "data/pawn_vertex.glsl",   GL_VERTEX_SHADER,
                                               "data/pawn_fragment.glsl", GL_FRAGMENT_SHADER);
}

void Pawn::draw(glm::mat4 projection, glm::mat4 view)
{
  glUseProgram(program);
  
  GLuint pID = glGetUniformLocation(program, "P");
  glUniformMatrix4fv(pID, 1, GL_FALSE, &projection[0][0]);

  GLuint vID = glGetUniformLocation(program, "V");
  glUniformMatrix4fv(vID, 1, GL_FALSE, &view[0][0]);

  glm::mat4 m = this->getMatrix();
  GLuint mID = glGetUniformLocation(program, "M");
  glUniformMatrix4fv(mID, 1, GL_FALSE, &m[0][0]);
  
  GLuint pawnColorID = glGetUniformLocation(program, "pawnColor");
  glUniform3f(pawnColorID, acolor.r, acolor.g, acolor.b);

  this->model->draw();

  acolor = color;
}

void Pawn::update(float dt)
{
  moving = false; 

  float speed = glm::distance2(target,position)/1000.0;
  if (speed > .005) speed = .005;
  if (speed < 0.000001) { position = target; return; }
  if (speed < 0.001) speed = 0.001;

  //position.y = speed*100;

  if (target.x < position.x) position.x -= speed*dt; 
  if (target.x > position.x) position.x += speed*dt; 

  if (target.z < position.z) position.z -= speed*dt; 
  if (target.z > position.z) position.z += speed*dt; 

  moving = true;
}
