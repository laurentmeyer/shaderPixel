#ifndef MATERIAL_H_
# define MATERIAL_H_

# include "Shader.h"
# include <memory>

class Material
{
public:
  Material() : shader(std::make_shared<Shader>("shaders/shader.vs", "shaders/shader.fs"))
  {}

  ~Material()
  {}

  void setShader(std::shared_ptr<Shader> shader)
    {this->shader = shader;}


protected:
  std::shared_ptr<Shader> shader;

private:

};


#endif // MATERIAL_H_