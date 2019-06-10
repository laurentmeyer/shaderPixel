#ifndef SQUARE_H_
# define SQUARE_H_

# include "Primitive.h"

class Square : public Primitive
{
public:
  Square() : Primitive(verticesCount, (GLfloat*)vertices, indicesCount, (GLuint*)indices)
  {}

  virtual ~Square()
  {}

protected:
  static const GLsizeiptr verticesCount;
  static const GLfloat vertices[];
  static const GLsizeiptr indicesCount;
  static const GLuint indices[];
};

const GLsizeiptr Square::verticesCount = 12;
const GLfloat Square::vertices[Square::verticesCount] = {
       0.5f,  0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f,
      -0.5f,  0.5f, 0.0f
  };

const GLsizeiptr Square::indicesCount = 6;
const GLuint Square::indices[Square::indicesCount] = {
    0, 1, 2,
    0, 2, 3
  };

#endif // SQUARE_H_