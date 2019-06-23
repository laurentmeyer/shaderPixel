#ifndef MESH_H_
# define MESH_H_

# include <memory>

class Mesh
{
public:
  Mesh()
  {};

  ~Mesh()
  {};

  enum Counts {
    FloatsPerUv = 2,
    FloatsPerVertex = 3,
    SizeTPerTriangle = 3
    };

  enum Standard {
    Square
    };

  void setVertices(size_t vertexCount, const float array[])
  {
    vertices.reset(new float[FloatsPerVertex * vertexCount]);
    memcpy(vertices.get(), array, FloatsPerVertex * vertexCount * sizeof(float));
    this->vertexCount = vertexCount;
  }

  void setTriangles(size_t trianglesCount, const unsigned int* array)
  {
    triangles.reset(new unsigned int[trianglesCount]);
    memcpy(triangles.get(), array, SizeTPerTriangle * trianglesCount * sizeof(unsigned int));
    this->trianglesCount = trianglesCount;
  }

  void setUvs(size_t vertexCount, const float* array)
  {
    if (vertexCount > this->vertexCount)
      vertexCount = this->vertexCount;
    uvs.reset(new float[FloatsPerUv * vertexCount]);
    memcpy(uvs.get(), array, FloatsPerUv * vertexCount * sizeof(float));
  }

  const float* getVertices() const
    {return vertices.get();}

  size_t getVertexCount() const
    {return vertexCount;}

  static std::shared_ptr<Mesh> getStandardMesh(Standard mesh)
  {
    if (mesh == Square)
      return getSquareMesh();
  }

private:
  size_t vertexCount = 0;
  size_t trianglesCount = 0;
  std::unique_ptr<unsigned int> triangles;
  std::unique_ptr<float[]> vertices;
  std::unique_ptr<float[]> uvs;

  static std::shared_ptr<Mesh> squareMesh;
  static const float squareVertices[];
  static const unsigned int squareIndices[];

  static std::shared_ptr<Mesh> getSquareMesh()
  {
    if (nullptr == squareMesh.get())
    {
      squareMesh = std::make_shared<Mesh>();
      squareMesh->setVertices(4, squareVertices);
      squareMesh->setTriangles(2, squareIndices);
    }
    return squareMesh;
  }

};


const float Mesh::squareVertices[] = {
       0.5f,  0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f,
      -0.5f,  0.5f, 0.0f
  };

const unsigned int Mesh::squareIndices[] = {
    0, 1, 2,
    0, 2, 3
  };


#endif // MESH_H_