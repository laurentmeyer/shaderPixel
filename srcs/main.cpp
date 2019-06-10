#define GLM_FORCE_RADIANS

#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Square.h"
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int main()
{
	Window window;

	if (!window.isInitialized())
	{
		std::cout << "Could not initialize window" << std::endl;
		return -1;
	}

  Camera camera;
  Shader shader("shaders/shader.vs", "shaders/shader.fs");
  Square square;

  while (!window.shouldClose())
  {
    window.update();
    // input
    // -----
    window.processInput();
    camera.processInput(window);
    
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    shader.setUniforms(window);
    
    shader.setMat4("modelMatrix", glm::mat4(1.0));
    shader.setMat4("viewMatrix", camera.getViewMatrix());
    shader.setMat4("projectionMatrix", glm::perspective(glm::radians(45.0), window.getAspect(), 0.1, 100.0));
    
    square.draw();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    window.swapBuffers();
    glfwPollEvents();
  }

	return 0;
}