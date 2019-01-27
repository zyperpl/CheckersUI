#pragma once

#include <cstdio>
#include <cstdlib>
#include <vector>

class Window;
class Model;
class Drawable;
class Pawn;
class Board;

#include "drawable.hpp"
#include "model.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define BOARD_SIZE_W 10
#define BOARD_SIZE_H 10

struct Color
{
  float r, g, b;
  Color(float rComponent, float gComponent, float bComponent)
    : r{rComponent}, g{gComponent}, b{bComponent}
  { }
};

struct Camera
{
  float angle = 72.0f;
  glm::vec3 position{4.0f,3.0f,3.0f};
};

class View
{
  public:
    View();   
    ~View();
    
    inline glm::mat4 getProjection()
    {
      return glm::perspective(glm::radians(camera.angle), 1.778f, 0.01f, 1000.0f);
    };

    inline glm::mat4 getView()
    {
      return glm::lookAt(camera.position, origin, glm::vec3(0,1,0) );
    }

    glm::vec2 cast(glm::vec2 mousePosition, glm::vec2 screenSize);
    Pawn *getPawn(glm::vec2 boardCoord);
    Pawn *getPawn(int x, int y);

    void movePawn(glm::vec2 oldCoord, glm::vec2 newCoord);

    void update(float dt);
  
  protected:
    std::vector<Drawable*> drawables;
    Board *board;
    Pawn ***boardMap;
    Camera camera;
    glm::vec3 origin{0.0,0.0,0.0};

  friend class Window;
};
