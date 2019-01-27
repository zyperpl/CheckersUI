#pragma once

#include "drawable.hpp"

class Board : public Drawable
{
  public:
    Board(int squareX = 10, int squareY = 10);
    void draw(glm::mat4 projection, glm::mat4 view);

    static float contrast;
  private:
    int squaresX, squaresY;
};
