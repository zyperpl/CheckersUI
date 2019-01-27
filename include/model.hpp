#pragma once

class View;
class Window;

#include <vector>
#include <cstdio>

#include "window.hpp"

class Model
{
  public:
    Model();
    void draw();

    /*
     *  Creates rounded piece staying upward on OY axis.
     */
    static Model *generatePawn(uint32_t sides = 8, double shrink = 1.2);

    /*
     *  Creates flat plane laying on XOZ.
     */
    static Model *generatePlane(float width, float height);
  protected:
    GLuint vertexBuffer, normalBuffer;

    std::vector<float> vertices;
    std::vector<float> normals;

    void generateVertexBuffer();



  friend class Window;
  friend class View;
};
