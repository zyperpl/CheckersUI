#include "model.hpp"
#include "glm/glm.hpp"
  
#define vert_add(a,b,c) { m->vertices.push_back(a); m->vertices.push_back(b); m->vertices.push_back(c); }
#define norm_add(a,b,c) { m->normals.push_back(a);  m->normals.push_back(b);  m->normals.push_back(c); }

Model::Model()
{}

void Model::generateVertexBuffer()
{
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
  
  glGenBuffers(1, &normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
}

void Model::draw()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0,(void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,0,(void*)0);
    
    glDrawArrays(GL_TRIANGLES, 0, vertices.size()); 
  }
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
}
 
Model *Model::generatePawn(uint32_t sides, double shrink)
{
  Model *m = new Model();

  /*
  static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
  };
  for (const auto &v : g_vertex_buffer_data) { m->vertices.push_back(v); };
  */

  const int SIDES = sides;
  const double ANGLE = 2*M_PI/SIDES;
  const double SHRINK = shrink;

  for (int i = 0; i < SIDES; ++i)
  {
    int i2 = (i+1)%SIDES;
    
    vert_add(cos(ANGLE*i),  0.0f, sin(ANGLE*i));  // left-down
    vert_add(cos(ANGLE*i)/SHRINK,  1.0f, sin(ANGLE*i)/SHRINK);  // left-up
    vert_add(cos(ANGLE*i2), 0.0f, sin(ANGLE*i2)); // right-down
                                             
    vert_add(cos(ANGLE*i2)/SHRINK, 1.0f, sin(ANGLE*i2)/SHRINK); // right-up
    vert_add(cos(ANGLE*i)/SHRINK,  1.0f, sin(ANGLE*i)/SHRINK);  // left-up
    vert_add(cos(ANGLE*i2), 0.0f, sin(ANGLE*i2)); // right-down
                                             
    vert_add(0.0f, 1.3f, 0.0f);                    
    vert_add(cos(ANGLE*i2)/SHRINK, 1.0f, sin(ANGLE*i2)/SHRINK); // right-up
    vert_add(cos(ANGLE*i)/SHRINK,  1.0f, sin(ANGLE*i)/SHRINK);  // left-up


    norm_add(cos(ANGLE*i+M_PI/2), 0.0f, sin(ANGLE*i+M_PI/2));
    norm_add(cos(ANGLE*i+M_PI/2), 0.0f, sin(ANGLE*i+M_PI/2));
    norm_add(cos(ANGLE*i+M_PI/2), 0.0f, sin(ANGLE*i+M_PI/2));

    norm_add(cos(ANGLE*i+M_PI/2), 0.0f, sin(ANGLE*i+M_PI/2));
    norm_add(cos(ANGLE*i+M_PI/2), 0.0f, sin(ANGLE*i+M_PI/2));
    norm_add(cos(ANGLE*i+M_PI/2), 0.0f, sin(ANGLE*i+M_PI/2));

    norm_add(0.0f, 1.0f, 0.0f);
    norm_add(cos(ANGLE*i+M_PI/2), 0.46f, sin(ANGLE*i+M_PI/2));
    norm_add(cos(ANGLE*i+M_PI/2), 0.46f, sin(ANGLE*i+M_PI/2));
  }

  
  m->generateVertexBuffer();
  return m;
}


Model *Model::generatePlane(float width, float height)
{
  Model *m = new Model();

  vert_add(-width/2, 0, -height/2); // left-down
  vert_add(-width/2, 0,  height/2); // left-up
  vert_add( width/2, 0,  height/2); // right-up
  
  vert_add(-width/2, 0, -height/2); // left-down
  vert_add( width/2, 0, -height/2); // right-down
  vert_add( width/2, 0,  height/2); // right-up

  norm_add(0.0f, 1.0f, 0.0f);
  norm_add(0.0f, 1.0f, 0.0f);
  norm_add(0.0f, 1.0f, 0.0f);
  norm_add(0.0f, 1.0f, 0.0f);
  norm_add(0.0f, 1.0f, 0.0f);
  norm_add(0.0f, 1.0f, 0.0f);

  for (const auto &v : m->vertices) printf("%f ", v);

  m->generateVertexBuffer();

  return m;
}
