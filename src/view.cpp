#include "view.hpp"
#include "pawn.hpp"


void GLAPIENTRY MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

View::View()
{
  for (int z = -5; z < 5; z++)
  for (int x = -30; x < 30; x++)
  {
    this->drawables.push_back(new Pawn(glm::vec3(x*3,0,z*3), Color(1.0, 1.0, 1.0) ));
    //this->drawables.push_back(new Pawn(glm::vec3((x+1)*3,0,(z-1)*2), Color(0.0, 0.0, 0.0) ));
  }

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}


