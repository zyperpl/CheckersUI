#include "shader.hpp"
#include "shader_manager.hpp"
 

std::vector<std::unique_ptr<Shader>> ShaderManager::shaders;
std::vector<std::unique_ptr<ShaderProgram>> ShaderManager::programs;

GLuint ShaderManager::getProgram(int shadersN, ...)
{
  va_list args;
  va_start(args, shadersN);

  std::vector<Shader*> programShaders;
  programShaders.reserve(shadersN);
  for (int i = 0; i < shadersN; i++)
  {
    // read name
    const char *name = va_arg(args, const char*);

    // read type
    GLuint type = va_arg(args, GLuint);

    //printf("%d) %s type=%d\n", i, name, type);

    Shader *shader{nullptr};

    shader = getShader(name, type);
    
    // when shader does not exist
    if (!shader)
    {
      shader = new Shader(name, type);

      // add to global list
      ShaderManager::shaders.emplace_back(std::move(shader));
    }

    // add to current program list
    programShaders.push_back(shader);
  }

  va_end(args);


  // search in existing programs
  GLuint id = 0;
  for (const auto &p : ShaderManager::programs)
  {
    if (p->shaders == programShaders)
      id = p->programID;
  }
 
  if (id <= 0)
  {
    id = ShaderManager::linkProgram(programShaders);
    ShaderManager::programs.emplace_back(std::move(new ShaderProgram(id, programShaders)) );
  }

  return id;
}

GLuint ShaderManager::linkProgram(std::vector<Shader*> programShaders)
{
  GLuint id = glCreateProgram();
  for (const auto &shader : programShaders)
  {
    glAttachShader(id, shader->id);
  }
  
  glLinkProgram(id);

  int infoLogLength;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

  int linkStatus;
  glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);
  
  if (infoLogLength > 0 || linkStatus == GL_FALSE)
  {
    std::unique_ptr<char[]> bufPtr(new char[infoLogLength+1]);
    char *buf = bufPtr.get();
    glGetProgramInfoLog(id, infoLogLength, NULL, buf);
    fprintf(stderr, "Shader linking error:\n%s!\n", buf);
    exit(1);
  } else
  {
    printf("Linked program %d: ", id);
    for (const auto &s : programShaders)
    {
      printf("%s ", s->name);
    }
    printf(".\n");
  }

#ifdef SHADER_MANAGER_AUTODELETE_SHADERS
  for (auto &shader : programShaders)
  {
    glDetachShader(id, shader->id);
    shader->free();
  }
#endif

return id;
} 

Shader *ShaderManager::getShader(const char *name, GLuint type)
{
  for (size_t i = 0; i < ShaderManager::shaders.size(); i++)
  {
    if (strcmp(ShaderManager::shaders.at(i).get()->name, name) == 0
    &&  shaders.at(i)->type == type)
    {
      ShaderManager::shaders.at(i).get()->compile();
      return shaders.at(i).get();
    }
  }

  Shader *shader = new Shader(name, type);
  ShaderManager::shaders.emplace_back(std::move(shader) );

  return shader;
}
