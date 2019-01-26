#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdarg>
#include <string.h>
#include <thread>

#include <GLFW/glfw3.h>

class Shader;

#include "shader.hpp"

struct ShaderProgram
{
  GLuint programID{0};
  std::vector<Shader*> shaders;

  ShaderProgram(GLuint id, std::vector<Shader*> shaders) 
    : programID{id}, shaders{shaders}
  {}
};

class ShaderManager
{
  public:
    static GLuint getProgram(int shadersN, ...);
    static Shader *getShader(const char *name, GLuint type);

  private:

    static GLuint linkProgram(std::vector<Shader*> programShaders);

    static std::vector<std::unique_ptr<Shader>> shaders;
    static std::vector<std::unique_ptr<ShaderProgram>> programs;

};

