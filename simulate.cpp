#include "boid.h"
#include "vector.h"
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

int main() {
    // testing
    Boid test_boid;
    test_boid.velocity.x = test_boid.max_speed;
    test_boid.velocity.y = 0;
    test_boid.print();

    // Graphics
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glewInit();

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Boids", NULL, NULL);
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

        // UPDATE & DRAW BOID (loop for flock)
        test_boid.adjustAcceleration();
        test_boid.update();
        test_boid.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}