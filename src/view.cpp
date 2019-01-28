#include "view.hpp"
#include "pawn.hpp"
#include "board.hpp"

#define WHITE_COLOR Color( 1.0,  1.0,  0.9)
#define BLACK_COLOR Color(0.10, 0.10, 0.16)

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
  board = new Board(BOARD_SIZE_W, BOARD_SIZE_H);
  this->drawables.push_back(board);

  boardMap = new Pawn**[BOARD_SIZE_W];
  for (int i = 0; i < BOARD_SIZE_W; i++)
  {
    boardMap[i] = new Pawn*[BOARD_SIZE_H];
  }

  for (int z = -BOARD_SIZE_H/2; z < BOARD_SIZE_H/2; z++)
  for (int x = -BOARD_SIZE_W/2; x < BOARD_SIZE_W/2; x++)
  {
    int xx = x+BOARD_SIZE_W/2;
    int zz = z+BOARD_SIZE_H/2;

    printf("%2d;%2d\n", xx, zz);
    boardMap[xx][zz] = nullptr;

    if ((z+x)%2 != 0 && (z < -1 || z >= 1))
    {
      Color c = z > 0 ? WHITE_COLOR : BLACK_COLOR;
      Pawn *p = new Pawn(glm::vec3((0.5+x)*2,0,(0.5+z)*2), c );
      boardMap[xx][zz] = p;
      this->drawables.push_back(p);
    }
  }

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(MessageCallback, 0);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_MULTISAMPLE);
}


glm::vec2 View::cast(glm::vec2 mousePosition, glm::vec2 screenSize)
{
  glm::vec4 mouseWorldPositionStart(
      (mousePosition.x/screenSize.x - 0.5f)*2.0f,
      -(mousePosition.y/screenSize.y - 0.5f)*2.0f,
      -1.0f, 1.0f);

  glm::vec4 mouseWorldPositionEnd(
      (mousePosition.x/screenSize.x - 0.5f)*2.0f,
      -(mousePosition.y/screenSize.y - 0.5f)*2.0f,
      0.0f, 1.0f);

  mouseWorldPositionStart = glm::inverse(getProjection()*getView()) * mouseWorldPositionStart;
  mouseWorldPositionStart /= mouseWorldPositionStart.w;
  mouseWorldPositionEnd = glm::inverse(getProjection()* getView()) * mouseWorldPositionEnd;
  mouseWorldPositionEnd /= mouseWorldPositionEnd.w;

  glm::vec3 pos = glm::vec3(mouseWorldPositionStart);
  glm::vec3 dir = glm::normalize(mouseWorldPositionEnd-mouseWorldPositionStart);

  int cx = -1, cz = -1;

  float l = 100.0f;
  const float STEP = 0.1f;
  while (l > 0)
  {
    l -= STEP;

    pos += dir*STEP;

    if (pos.y < 0)
    {
      board->selected = {pos.x,pos.z};
      printf("%f %f -> ", pos.x, pos.z);

      //drawables[1]->position = pos;
      //printf("%6.2f %6.2f %6.2f\n", pos.x, pos.y, pos.z);
      cx = round((ceil(pos.x)+10)/20*10)-1;
      cz = round((ceil(pos.z)+10)/20*10)-1;

      printf("%d %d\n", cx, cz);
      break;
    }
  }

  return {cx,cz};
}

Pawn *View::getPawn(glm::vec2 boardCoord)
{
  int cx = boardCoord.x;
  int cz = boardCoord.y;

  return getPawn(cx,cz);
}

Pawn *View::getPawn(int x, int y)
{
  int cx = x;
  int cz = y;

  if (cx >= 0 && cx < BOARD_SIZE_W
  &&  cz >= 0 && cz < BOARD_SIZE_H)
  {
    return boardMap[cx][cz];
  }
  return nullptr;
}


void View::movePawn(glm::vec2 oldCoord, glm::vec2 newCoord)
{
  int ox = oldCoord.x;
  int oz = oldCoord.y;

  int nx = newCoord.x;
  int nz = newCoord.y;

  if (ox >= 0 && ox < BOARD_SIZE_W && oz >= 0 && oz < BOARD_SIZE_H
  &&  nx >= 0 && nx < BOARD_SIZE_W && nz >= 0 && nz < BOARD_SIZE_H)
  {
    Pawn *p = boardMap[ox][oz];
    if (p != nullptr)
    {
      boardMap[nx][nz] = p;
      p->setTargetPosition({(nx-5+0.5)*2,0,(nz-5+0.5)*2});
    }
    boardMap[ox][oz] = nullptr;
  }

}


void View::update(float dt)
{
  for (int x = 0; x < BOARD_SIZE_W; x++)
  for (int z = 0; z < BOARD_SIZE_H; z++)
  {
    if (Pawn *p = boardMap[x][z])
    {
      p->update(dt);
    }
  }
}

View::~View()
{
  for (int i = 0; i < BOARD_SIZE_W; i++)
  {
    delete[] boardMap[i];
  }
  delete[] board;
}
