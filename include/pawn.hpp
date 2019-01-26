#pragma once

#include "view.hpp"
#include "model.hpp"
#include "shader_manager.hpp"
#include "drawable.hpp"

class Pawn : public Drawable
{
  public:
    Pawn(glm::vec3 pos, Color c);
    void draw(glm::mat4 projection, glm::mat4 view);

  private:
    Color color{255,0,0};
};
