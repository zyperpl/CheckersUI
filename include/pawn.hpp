#pragma once

class Pawn;
class View;

struct Color;

#include "view.hpp"
#include "model.hpp"
#include "shader_manager.hpp"
#include "drawable.hpp"

class Pawn : public Drawable
{
  public:
    Pawn(glm::vec3 pos, Color c);
    void draw(glm::mat4 projection, glm::mat4 view);
    inline void setTargetPosition(glm::vec3 target)
    {
      this->target = target;
    }

    void update(float dt);
    Color acolor{255,0,0};
    bool moving{false};
  private:
    Color color{255,0,0};
    glm::vec3 target;
};
