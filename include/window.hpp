#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WINDOW_TITLE "Checkers OpenGL"

class View;

class Window
{
  public:
    Window(int width, int height);
    ~Window();

    bool isOpen();
    void update(double deltaTime, View &view);
    void render(View &view);

  private:
    GLFWwindow *window;
};
