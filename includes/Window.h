#ifndef WINDOW_H_
# define WINDOW_H_

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "glm/glm.hpp"
# include <string>
# include <algorithm>
# include <list>

class Window
{
public:
  Window() : width(800), height(600), name("ShaderPixel")
  {
    init();
    Window::windows.push_front(this);
  }

  ~Window()
  {
    Window* w(Window::findWindow(window));
    if (w)
      Window::windows.remove(w);
    glfwTerminate();
  }

  void init(bool polygonMode = false) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if (window) {
      glfwMakeContextCurrent(window);
      glewInit();
      glViewport(0, 0, width, height);
      glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    }
    if (polygonMode)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  void update()
  {
    updateDeltaTime();
    updateMouse();
  }

  double getDeltaTime() const
    {return deltaTime;}

  bool isInitialized() const
    {return nullptr != window;}

  bool shouldClose() const
    {return glfwWindowShouldClose(window);}

  void processInput() const
  {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
  }

  void getSize(int *width, int *height) const
    {glfwGetWindowSize(window, width, height);}

  double getAspect() const
  {
    int width;
    int height;
    getSize(&width, &height);
    return (double)width / (double)height;
  }

  void swapBuffers() const
    {glfwSwapBuffers(window);}

  int getKey(int key) const
    {return glfwGetKey(window, key);}

  const GLFWwindow* getWindow() const
    {return window;}

  const glm::dvec2& getMouse() const
    {return mouse;}

  glm::dvec2 getNormalizedMouse() const
  {
    glm::vec2 res(mouse);
    res.x = res.x / width * 2.0 - 1.0;
    res.y = res.y / height * 2.0 - 1.0;
    return res;
  }

  private:

  void updateMouse()
    {glfwGetCursorPos(window, &mouse.x, &mouse.y);}

  void updateDeltaTime()
  {
    double current = glfwGetTime();
    deltaTime = current - previousTime;
    previousTime = current;
  }

  static Window* findWindow(GLFWwindow* window)
  {
    std::list<Window*>::iterator it;
    for (it = windows.begin(); it != windows.end(); it++)
      if (*it && (*it)->getWindow() == window)
        return *it;
    return nullptr;
  }

  static Window* popWindow(GLFWwindow* window)
  {
    std::list<Window*>::iterator it;
    for (it = windows.begin(); it != windows.end(); it++)
      if (*it && (*it)->getWindow() == window)
        return *it;
    return nullptr;
  }

  /* GLFW CALLBACKS */
  static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
  {
    (void)window;
    glViewport(0, 0, width, height);
  }

  GLFWwindow* window;
  int width;
  int height;
  std::string name;
  double previousTime = 0.0;
  double deltaTime;
  glm::dvec2 mouse;
  glm::dvec2 previousMouse;
  static std::list<Window*> windows;

};

std::list<Window*> Window::windows = {};

#endif //WINDOW_H_