#ifndef CAMERA_H_
# define CAMERA_H_

# include "Transform.h"
# include "glm/glm.hpp"

class Camera : public Transform
{
  public:
  
  Camera()
  {}

  ~Camera() override
  {}

  void processInput(const Window& window)
  {
    // update orientation based on mouse
    const glm::vec2 mouse(window.getNormalizedMouse());
    float rotationX = -glm::clamp(mouse.y, -1.0f, 1.0f) * glm::radians(90.0);
    float rotationY = -mouse.x * glm::radians(360.0);
    setOrientation(glm::vec3(rotationX, rotationY, 0.0));

    // update position based on keyboard and gaze direction
    const double deltaTime = window.getDeltaTime();
    glm::vec4 direction(0.0);
    if (window.getKey(GLFW_KEY_W) == GLFW_PRESS)
      direction.z += deltaTime * metersPerSecond;
    if (window.getKey(GLFW_KEY_S) == GLFW_PRESS)
      direction.z -= deltaTime * metersPerSecond;
    if (window.getKey(GLFW_KEY_A) == GLFW_PRESS)
      direction.x += deltaTime * metersPerSecond;
    if (window.getKey(GLFW_KEY_D) == GLFW_PRESS)
      direction.x -= deltaTime * metersPerSecond;
    if (glm::vec4(0.) != direction)
    {
      direction = glm::rotate(orientation, direction);
      setPosition(position + glm::vec3(direction));    
    }

  }

  glm::mat4 getViewMatrix() const
  {
    glm::mat4 cameraMatrix(getMatrix());
    return glm::inverse(cameraMatrix);
  }

  private:

  const double metersPerSecond = 5.0;
  const double radiansPerPixel = glm::radians(0.1);

};

#endif