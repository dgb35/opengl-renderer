#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include <numbers>
#include <random>

constexpr int triangles_count = 100;

GLbyte get_rand() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> distribution(0, 256);

    return distribution(engine);
}

void DrawCircle(float x, float y, float radius, float red, float green, float blue)
{
    float current_pos = 0;
    float sector = 2 * std::numbers::pi / triangles_count;

    for(size_t i = 0; i < triangles_count; ++i)
    {
        glColor3f(red, green, blue);
        glBegin(GL_TRIANGLES);
        glVertex2d(x, y);
        glVertex2d(cos(current_pos) * radius + x, sin(current_pos) * radius + y);
        glVertex2d(cos(current_pos + sector) * radius + x, sin(current_pos + sector) * radius + y);
        glEnd();

        current_pos += sector;
    }

}

void DrawCircle(float x, float y, float radius)
{
    DrawCircle(x, y, radius, 1, 1, 1);
}

int main() {
    if(!glfwInit()) {
        std::cerr << "GLFW init failed!";
        return -1;
    }

    auto window = glfwCreateWindow(1080, 1080, "Application", nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScaled(0.1, 0.1, 1);

    float angle = 0;
    float moon_angle = 0;

    while (!glfwWindowShouldClose(window)) {
        angle += 1;
        moon_angle += 3;

        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);

        DrawCircle(0, 0, 0.5, 1, 1, 0);

        {
            glPushMatrix();
            glRotated(angle, 0, 0, 1);
            glTranslated(0, 5, 0);
            DrawCircle(0, 0, 0.3, 0, 0, 0.6);
            {
                glPushMatrix();
                glRotated(moon_angle, 0, 0, 1);
                glTranslated(0, 1.5, 0);
                DrawCircle(0, 0, 0.15, 0.5, 0.5, 0.5);
                glPopMatrix();
            }
            glPopMatrix();
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}