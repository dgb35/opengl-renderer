#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "utilities.h"
#include "shader.h"


const char *vertexShaderSource = R"END(#version 330 core
                                        layout (location = 0) in vec3 vPos;
                                        layout (location = 1) in vec3 vColor;
                                        out vec3 vertexColor;
                                        void main()
                                        {
                                        vertexColor = vColor;
                                        gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0);
                                        })END";

const char *fragmentShaderSource = R"END(#version 330 core
                                         out vec4 FragColor;
                                         in vec3 vertexColor;
                                         uniform vec4 color;
                                         void main()
                                         {
                                         FragColor = vec4(color.x, color.y, color.y, 1.0);
                                         })END";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
    if(!glfwInit()) {
        std::cerr << "GLFW init failed!";
        return -1;
    }

    // set OpenGL version and require core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(1080, 1080, "Application", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 1080, 1080);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shader{vertexShaderSource, fragmentShaderSource};
    shader.use();

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f,

             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
             0.0f, -0.5f, 0.0f
    };

    std::vector<float> circle;
    utilities::create_circle(circle, 0, 0, 0.6, 100);

    float colors[] = {
            1.0f, 0.5f, 0.0f,
            0.5f, 1.0f, 0.0f,
            0.5f, 0.0f, 1.0f,

            1.0f, 0.5f, 0.0f,
            0.5f, 1.0f, 0.0f,
            0.5f, 0.0f, 1.0f
    };

    unsigned int VBO[2], VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * circle.size(), circle.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

//    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * circle.size(), circle.data(), GL_STATIC_DRAW);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
//    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        float redValue = cos(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shader.id(), "color");
        glUniform4f(vertexColorLocation, redValue / 2, greenValue, redValue, 1.0f);

        glUseProgram(shader.id());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, circle.size() * 3);

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDisableVertexAttribArray(0);
    glDeleteBuffers(2, VBO);
    glDeleteVertexArrays(1, &VAO);

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}