#ifndef TRANSFORM_H_
# define TRANSFORM_H_

# include "glm/glm.hpp"
# include "glm/gtc/quaternion.hpp"
# include "glm/gtc/matrix_transform.hpp"
# include "glm/gtx/string_cast.hpp"
# include "glm/gtx/quaternion.hpp"

class Transform
{
  public:
  Transform(const glm::vec3& position = glm::vec3(), const glm::quat& orientation = glm::quat()) :
    position(position),
    orientation(orientation)
  {}

  virtual ~Transform()
  {}


  const glm::vec3& getPosition() const
    {return position;}

  const glm::quat& getOrientation() const {return orientation;}

  std::string toString() const
    {return std::string("Position:" + glm::to_string(position)
                      + " Orientation:" + glm::to_string(glm::degrees(glm::eulerAngles(orientation))));}

  glm::mat4 getMatrix() const
    {return glm::translate(glm::mat4(1.0), -position) * glm::mat4_cast(orientation);}

  void setPosition(const glm::vec3& position)
    {this->position = position;}

  void setOrientation(const glm::quat& quat)
    {orientation = quat;}

  void setOrientation(const glm::vec3& eulerAngles)
    {setOrientation(glm::quat(eulerAngles));}
    

protected:
  glm::vec3 position;
  glm::quat orientation;
  
};

#endif //TRANSFORM_H_