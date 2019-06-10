#ifndef PRIMITIVE_H_
# define PRIMITIVE_H_

# include "Transform.h"
# include "Window.h"


class Primitive
{
public:
  Primitive(GLsizeiptr verticesCount, GLfloat* vertices, GLsizeiptr indicesCount, GLuint* indices) :
  verticesCount(verticesCount),
  vertices(vertices),
  indicesCount(indicesCount),
  indices(indices)
  {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat), (void*)0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

  }

  virtual ~Primitive()
  {}

  virtual void draw()
  {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
  }

protected:
  Transform transform;
  glm::vec3 scale;
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  const GLsizeiptr verticesCount;
  const GLfloat* vertices;
  const GLsizeiptr indicesCount;
  const GLuint* indices;
};

#endif // PRIMITIVE_H_