#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"


int main(void)
{
    if (!glfwInit())
    {
        std::cout << "GLFW Init Failed\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Setup", nullptr, nullptr);
    if (!window)
    {
        std::cout << "Window creation failed\n";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD initialization failed\n";
        return -1;
    }

    float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, 1.0f, 0.0f,// 1
         0.5f,  0.5f, 1.0f, 1.0f,// 2
         -0.5f, 0.5f, 0.0f, 1.0f  // 3
    };

    unsigned int indices[] = 
    {
        0,1,2,
        2,3,0
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
    

    VertexArray va;
    VertexBuffer vb(vertices, 4 * 4 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb,layout);

    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.5f, 1.5f, -1.0f, 1.0f); // left, right , bottom , top

    Shader shader("C:/Users/mp01/Documents/openglDemo/ge/gameEngine/res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    shader.SetUniformMat4f("u_MVP", proj);
    Texture texture("C:/Users/mp01/Documents/openglDemo/ge/gameEngine/im.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    float  r = 0.0f;
    float inc = 0.05f;
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        renderer.Draw(va, ib, shader);

        if (r > 1.0f)
            inc = -0.05f;
        else if (r < 0.0f)
            inc = 0.05f;
        r += inc;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}