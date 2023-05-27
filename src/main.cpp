#include <glad/gl.h>

#include <GLFW/glfw3.h>
#include <glm/matrix.hpp>

#include <filesystem>
#include <iostream>

#include "index_buffer.h"
#include "shader.h"
#include "vertex_array.h"
#include "vertex_buffer.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW init failed!";
        return -1;
    }
    {// GLFW scope
        // set OpenGL version and require core profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        auto window = glfwCreateWindow(900, 900, "Application", nullptr, nullptr);
        glfwMakeContextCurrent(window);

        if (!gladLoadGL(glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        glViewport(0, 0, 900, 900);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        const char *shadersDir = "../shaders";
        std::string vertexShaderSource = (std::filesystem::current_path() / shadersDir / "vertex_shader.glsl").string();
        std::string fragmentShaderSource = (std::filesystem::current_path() / shadersDir / "fragment_shader.glsl").string();

        ShaderProgram shader(vertexShaderSource, fragmentShaderSource);
        shader.use();

        GLfloat cube_vertices[] = {
                // front
                -1.0, -1.0, 1.0,
                1.0, -1.0, 1.0,
                1.0, 1.0, 1.0,
                -1.0, 1.0, 1.0,
                // back
                -1.0, -1.0, -1.0,
                1.0, -1.0, -1.0,
                1.0, 1.0, -1.0,
                -1.0, 1.0, -1.0};

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
                1.0, 1.0, 1.0};

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
                6, 7, 3};

        GLfloat line_vertices[] = {
                // front
                -1.0, -1.0, 1.0,
                1.0, -1.0, 1.0,
                1.0, 1.0, 1.0,
                -1.0, 1.0, 1.0,
                // back
                -1.0, -1.0, -1.0,
                1.0, -1.0, -1.0,
                1.0, 1.0, -1.0,
                -1.0, 1.0, -1.0};

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
                0.0, 0.0, 0.0};

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
                4, 7};.

        VertexArray cubeArray;
        VertexArray lineArray;

        VertexBufferLayout generic_vertex_layout;
        generic_vertex_layout.push<float>(3);
        generic_vertex_layout.setAttribIndex(0);

        VertexBufferLayout generic_color_layout;
        generic_color_layout.push<float>(3);
        generic_color_layout.setAttribIndex(1);

        // cube
        cubeArray.bind();

        VertexBuffer cube_vertices_buffer(cube_vertices, sizeof(cube_vertices));
        VertexBuffer cube_colors_buffer(cube_colors, sizeof(cube_colors));
        IndexBuffer cube_elements_buffer(cube_elements, sizeof(cube_elements));

        cubeArray.add_buffer(cube_vertices_buffer, generic_vertex_layout);
        cubeArray.add_buffer(cube_colors_buffer, generic_color_layout);
        cubeArray.add_buffer(cube_elements_buffer, generic_vertex_layout);

        // lines
        lineArray.bind();

        VertexBuffer line_vertices_buffer(line_vertices, sizeof(line_vertices));
        VertexBuffer line_colors_buffer(line_colors, sizeof(line_colors));
        IndexBuffer line_elements_buffer(line_elements, sizeof(line_elements));

        lineArray.add_buffer(line_vertices_buffer, generic_vertex_layout);
        lineArray.add_buffer(line_colors_buffer, generic_color_layout);
        lineArray.add_buffer(line_elements_buffer, generic_vertex_layout);

        // rendering
        glm::mat4 camera = {
                0.25, 0, 0, 0,
                0, 0.25, 0, 0,
                0, 0, 0.25, 0,
                0, 0, 0, 1};

        glEnable(GL_CULL_FACE);

        float alpha = 0;
        while (!glfwWindowShouldClose(window)) {
            glClearColor(0, 0, 0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);

            float sa = sin(alpha);
            float ca = cos(alpha);

            const glm::mat4 rotate_y = {
                    1, 0, 0, 0,
                    0, sa, -ca, 0,
                    0, ca, sa, 0,
                    0, 0, 0, 1};

            const glm::mat4 rotate_z = {
                    sa, -ca, 0, 0,
                    ca, sa, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1};

            const glm::mat4 rotate_x = {
                    sa, 0, -ca, 0,
                    0, 1, 0, 0,
                    ca, 0, sa, 0,
                    0, 0, 0, 1};


            const glm::mat4 res = camera * rotate_x * rotate_y * rotate_z;
            auto camera_matrix = glGetUniformLocation(shader.id(), "matrix");
            glUniformMatrix4fv(camera_matrix, 1, GL_FALSE, reinterpret_cast<const GLfloat *>(&res));

            cubeArray.bind();
            glDrawElements(GL_TRIANGLES, sizeof(cube_elements), GL_UNSIGNED_SHORT, nullptr);

            lineArray.bind();
            glDrawElements(GL_LINES, sizeof(line_elements), GL_UNSIGNED_SHORT, nullptr);

            alpha += 0.01;

            processInput(window);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }// GLFW scope end
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}