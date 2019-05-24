#define GLM_FORCE_RADIANS

// #include "project.h"
#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// GLfloat vertices[] = {
//      0.0,  0.0, 0.0, 0.0,
//      1.0,  0.0, 0.0, 0.0,
//      0.0,  1.0, 0.0, 0.0,
//     -1.0,  0.0, 0.0, 0.0,
//      0.0, -1.0, 0.0, 0.0
// };
 float vertices[] = {
        // positions       
         1.5f,  1.5f, 1.0f,
         0.5f, -0.5f, 1.0f,
        -0.5f, -0.5f, 1.0f, 
        -0.5f,  0.5f, 1.0f
    };

GLuint indices[] = {
    0, 1, 2,
    0, 2, 3
    // ,0, 3, 4,
    // 0, 4, 1
};


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

  GLuint VAO;
  GLuint VBO;
  GLuint EBO; // element buffer object
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(float), (void*)0);

  glEnableVertexAttribArray(0);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  //glBindVertexArray(0);


  // shader.setMat4("projectionMatrix", glm::perspective(60.0, window.getAspect(), 0.1, 100.0));

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
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    window.swapBuffers();
    glfwPollEvents();
  }

	return 0;
}