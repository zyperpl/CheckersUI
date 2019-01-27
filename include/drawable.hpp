#pragma once

#include <GL/glew.h>
#include <memory>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

class Window;
class View;

#include "model.hpp"

class Drawable
{
  public:
    virtual void draw(glm::mat4 projection, glm::mat4 view) {};
    
    inline glm::mat4 getMatrix() {
      glm::mat4 translationMatrix = glm::translate(glm::mat4(1), position);
      glm::mat4 rotationMatrix = glm::toMat4(glm::quat(rotation));
      glm::mat4 scaleMatrix = glm::scale(scale);

      return translationMatrix * rotationMatrix * scaleMatrix;
    };
    inline GLuint getShaderProgram() { return this->program; }
    inline Model *getModel() { return this->model.get(); }

  protected:
    std::unique_ptr<Model> model;
    GLuint program;

    glm::vec3 position, rotation, scale{1.0f,1.0f,1.0f};

    friend class Window;
    friend class View;

};
