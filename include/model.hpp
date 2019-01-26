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

    static Model *generatePawn();
  protected:
    GLuint vertexBuffer, normalBuffer;

    std::vector<float> vertices;
    std::vector<float> normals;

    void generateVertexBuffer();



  friend class Window;
  friend class View;
};
