#ifndef MESH_H_
# define MESH_H_

# include "glm/glm.hpp"
# include <vector>

class Mesh
{
public:
  Mesh()
  {};

  ~Mesh()
  {};

private:
  std::vector<glm::vec3> vertices = {};
  std::vector<glm::ivec3> triangles = {};
  std::vector<glm::vec2> uvs = {};
};

#endif // MESH_H_