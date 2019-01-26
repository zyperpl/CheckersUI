#include "model.hpp"
#include "pawn.hpp"

Pawn::Pawn(glm::vec3 pos, Color c) :
    color{c}
{
  this->position = pos;

  this->model.reset(Model::generatePawn());
  this->program = ShaderManager::getProgram(2, "data/pawn_vertex.glsl", GL_VERTEX_SHADER,
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
  glUniform3f(pawnColorID, color.r, color.g, color.b);

  this->model->draw();
}
