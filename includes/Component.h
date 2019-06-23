#ifndef COMPONENT_H_
# define COMPONENT_H_

# include "Mesh.h"
# include "Material.h"
# include <memory>

class Renderer
{
public:


};

class Component
{
public:
  Component() :
  material(std::make_shared<Material>()),
  mesh(Mesh::getStandardMesh(Mesh::Standard::Square))
  {}

  virtual ~Component()
  {}

  void setMesh(std::shared_ptr<Mesh> mesh)
    {this->mesh= mesh;}

  void setMaterial(std::shared_ptr<Material> material)
    {this->material = material;}

  void draw() const
    {}


protected:
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Material> material;
};


#endif // COMPONENT_H_