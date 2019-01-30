#include "board.hpp"
#include "shader_manager.hpp"

float Board::contrast = 200.0;

Board::Board(int squareX, int squareY)
  : squaresX{squareX}, squaresY{squareY}
{
  this->position = glm::vec3(0,0,0);
  this->rotation = glm::vec3(0,0,0);
  this->scale    = glm::vec3(1,1,1);

  this->model.reset(Model::generatePlane(squareX*2, squareY*2));
  this->program = ShaderManager::getProgram(2, "data/board_vertex.glsl",   GL_VERTEX_SHADER,
                                               "data/board_fragment.glsl", GL_FRAGMENT_SHADER);
}

void Board::draw(glm::mat4 projection, glm::mat4 view)
{
  glUseProgram(program);
  
  GLuint pID = glGetUniformLocation(program, "P");
  glUniformMatrix4fv(pID, 1, GL_FALSE, &projection[0][0]);

  GLuint vID = glGetUniformLocation(program, "V");
  glUniformMatrix4fv(vID, 1, GL_FALSE, &view[0][0]);

  glm::mat4 m = this->getMatrix();
  GLuint mID = glGetUniformLocation(program, "M");
  glUniformMatrix4fv(mID, 1, GL_FALSE, &m[0][0]);

  GLuint cID = glGetUniformLocation(program, "contrast");
  glUniform1f(cID, Board::contrast);

 

  GLuint selID = glGetUniformLocation(program, "selected");
  glUniform2fv(selID, 1, &selected[0]);

  
  this->model->draw();
}
