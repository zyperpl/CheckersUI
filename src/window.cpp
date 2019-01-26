#include "window.hpp"
#include "view.hpp"
#include "model.hpp"

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

  if (glfwGetKey(window, GLFW_KEY_LEFT))  view.camera.position.x -= 0.1;
  if (glfwGetKey(window, GLFW_KEY_RIGHT)) view.camera.position.x += 0.1;
  if (glfwGetKey(window, GLFW_KEY_UP))    view.camera.position.y += 0.1;
  if (glfwGetKey(window, GLFW_KEY_DOWN))  view.camera.position.y -= 0.1;
  
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
