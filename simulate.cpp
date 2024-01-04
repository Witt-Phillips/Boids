#include "boid.h"
#include "vector.h"
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

int main() {
    /* Vector2 testVec = Vector2(3, 4);
    testVec.print();
    testVec.norm();
    testVec.print(); */

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glewInit();

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    std::cout << glGetString(GL_VERSION) << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // DRAW BASIC BOID
        /* for (const Boid& boid : boids) {
            glPushMatrix(); // Save the current transformation matrix

            // Translate to boid's position
            glTranslatef(boid.position.x, boid.position.y, 0);

            // Rotate according to boid's direction
            float angle = atan2(boid.direction.y, boid.direction.x) * 180.0 / M_PI;
            glRotatef(angle, 0, 0, 1);

            // Draw the triangle representing the boid
            glBegin(GL_TRIANGLES);
                glColor3f(1.0, 1.0, 1.0); // Set the color of the triangle
                glVertex2f(0.0, 0.5); // Top vertex
                glVertex2f(-0.25, -0.5); // Bottom left vertex
                glVertex2f(0.25, -0.5); // Bottom right vertex
            glEnd();

            glPopMatrix(); // Restore the previous transformation matrix
        } */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}