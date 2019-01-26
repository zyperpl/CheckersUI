#pragma once

#include <GL/glew.h>
#include <memory>

class Shader
{
  public:
    Shader(const char *name, GLenum type);

    void compile();
    void free();

  private:
    GLint id;
    const char *name;
    GLenum type;
    std::unique_ptr<char[]> bufferPtr;

    friend class ShaderManager;
};
