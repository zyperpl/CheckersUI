#include "window.hpp"
#include "view.hpp"
#include "model.hpp"
#include "board.hpp"
#include "pawn.hpp"

#include <cstdio>
#include <cstdlib>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

static int GLFW_INITIALIZED = 0;

Window::Window(int width, int height)
{
  if (GLFW_INITIALIZED <= 0)
  {
    if (!glfwInit())
    {
      fprintf(stderr, "Cannot initialize GLFW!\n");
    } else
    {
      GLFW_INITIALIZED = 1;
    }
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_SAMPLES, 4);

  this->window = glfwCreateWindow(width, height, WINDOW_TITLE, NULL, NULL);

  if (!this->window)
  {
    fprintf(stderr, "Cannot open window!\n");
  }

  glfwMakeContextCurrent(this->window);

  glewExperimental = GL_TRUE; 
  glewInit();
  glGetError(); //reset error from glewInit


  GLuint vaID; glGenVertexArrays(1, &vaID); glBindVertexArray(vaID);
}

Window::~Window()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

bool Window::isOpen()
{
  return !glfwWindowShouldClose(this->window);
}

void Window::update(double deltaTime, View &view)
{
  glfwPollEvents();
  
  int framebufferWidth, framebufferHeight;
  glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
  glViewport(0, 0, framebufferWidth, framebufferHeight);

  int windowWidth, windowHeight;
  glfwGetWindowSize(window, &windowWidth, &windowHeight);

  auto forward = glm::normalize(view.camera.position - view.origin);
  auto right   = glm::cross(forward, glm::vec3(0,1,0));
  auto up      = glm::cross(forward, right);

  float step = 0.01*deltaTime;

  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) step *= 6;
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))   step *= 8;
  if (glfwGetKey(window, GLFW_KEY_LEFT_ALT))     step *= 10;

  if (glfwGetKey(window, GLFW_KEY_LEFT))  view.camera.position += right*step;
  if (glfwGetKey(window, GLFW_KEY_RIGHT)) view.camera.position -= right*step;
  if (glfwGetKey(window, GLFW_KEY_UP))    view.camera.position -= up*step;
  if (glfwGetKey(window, GLFW_KEY_DOWN))  view.camera.position += up*step;
  
  if (glfwGetKey(window, GLFW_KEY_EQUAL))  view.camera.position += forward*step;
  if (glfwGetKey(window, GLFW_KEY_MINUS))  view.camera.position -= forward*step;

  if (glfwGetKey(window, GLFW_KEY_A))
  {
    for (auto &d : view.drawables) { d->scale -= 0.1*step; }
  }
  if (glfwGetKey(window, GLFW_KEY_Q))
  {
    for (auto &d : view.drawables) { d->scale += 0.1*step; }
  }
  
  if (glfwGetKey(window, GLFW_KEY_R)) { Board::contrast += 1*step; }
  if (glfwGetKey(window, GLFW_KEY_F)) { Board::contrast -= 1*step; }
    
  double mx, my;
  glfwGetCursorPos(window, &mx, &my);

  auto currentBoardCoord = view.cast({mx,my}, {framebufferWidth,framebufferHeight});
  static glm::vec2 selectedBoardCoord(-1,-1);


  Pawn *selected = view.getPawn(selectedBoardCoord);
  if (selected)
  {
    selected->acolor = { 0.1, 0.9, 0.5 };  
  }

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
  {
    if (Pawn *currentPawn = view.getPawn(currentBoardCoord))
    {
      // place already occupied
      
      if (!currentPawn->moving)
      {
        // item select
        selectedBoardCoord = currentBoardCoord;
      }
    } else
    {
      // place is empty
      if (selected)
      {
        // move selected item into that
        view.movePawn(selectedBoardCoord, currentBoardCoord);
        selectedBoardCoord = {-1,-1};
      }
    }
  }

  view.update(deltaTime);

  if (glfwGetKey(window, GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);
}

void Window::render(View &view)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (const auto drawable : view.drawables)
  {
    drawable->draw(view.getProjection(), view.getView());
  }

  glfwSwapBuffers(this->window);
}
