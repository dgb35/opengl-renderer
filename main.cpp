#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/matrix.hpp>

#include "shader.h"


const char *vertexShaderSource = R"END(#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;
out vec3 vertexColor;
uniform mat4 matrix;

void main()
{
vertexColor = vColor;
gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0) * matrix;
})END";

const char *fragmentShaderSource = R"END(#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
uniform vec2 res;
void main()
{
    FragColor = vec4(vertexColor, 1.0);
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

    auto window = glfwCreateWindow(900, 900, "Application", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 900, 900);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader shader{vertexShaderSource, fragmentShaderSource};
    shader.use();

    GLfloat cube_vertices[] = {
            // front
            -1.0, -1.0,  1.0,
            1.0, -1.0,  1.0,
            1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
            // back
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0
    };

    GLfloat cube_colors[] = {
            // front colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0,
            // back colors
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 1.0
    };

    GLushort cube_elements[] = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
    };

    GLfloat line_vertices[] = {
            // front
            -1.0, -1.0,  1.0,
            1.0, -1.0,  1.0,
            1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
            // back
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0
    };

    GLfloat line_colors[] = {
            // front colors
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0,
            // back colors
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0
    };

    GLushort line_elements[] = {
        0, 1,
        2, 3,
        4, 5,
        6, 7,
        0, 3,
        1, 2,
        0, 4,
        1, 5,
        2, 6,
        3, 7,
        5, 6,
        4, 7
    };

    unsigned int cubeBuffer[3], lineBuffer[3], cubeVAO, lineVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenVertexArrays(1, &lineVAO);
    glGenBuffers(3, cubeBuffer);

    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeBuffer[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

    glBindVertexArray(lineVAO);
    glGenBuffers(3, lineBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, lineBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(line_vertices), line_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, lineBuffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(line_colors), line_colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineBuffer[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(line_elements), line_elements, GL_STATIC_DRAW);

    glm::mat4 camera = {
            0.25, 0, 0, 0,
            0, 0.25, 0, 0,
            0, 0, 0.25, 0,
            0, 0, 0, 1
    };

    glEnable(GL_CULL_FACE);

    float alpha = 0;
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        float sa = sin(alpha);
        float ca = cos(alpha);

        const glm::mat4 rotate_y = {
                1,  0,  0, 0,
                0,  sa,-ca, 0,
                0,  ca, sa, 0,
                0,  0,  0, 1
        };

        const glm::mat4 rotate_z = {
                sa, -ca, 0, 0,
                ca,  sa, 0, 0,
                0,   0,  1, 0,
                0,   0,  0, 1
        };

        const glm::mat4 rotate_x = {
                sa, 0, -ca, 0,
                0,  1,  0, 0,
                ca, 0,  sa, 0,
                0,  0,  0, 1
        };


        const glm::mat4 res = camera * rotate_x * rotate_y * rotate_z;
        auto camera_matrix = glGetUniformLocation(shader.id(), "matrix");
        glUniformMatrix4fv(camera_matrix, 1, GL_FALSE, reinterpret_cast<const GLfloat *>(&res));

        glBindVertexArray(cubeVAO);
        glDrawElements(GL_TRIANGLES, sizeof(cube_elements), GL_UNSIGNED_SHORT, nullptr);

        glBindVertexArray(lineVAO);
        glDrawElements(GL_LINES, sizeof(line_elements), GL_UNSIGNED_SHORT, nullptr);

        alpha += 0.01;

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDisableVertexAttribArray(0);
    glDeleteBuffers(3, cubeBuffer);
    glDeleteBuffers(3, lineBuffer);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lineVAO);

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