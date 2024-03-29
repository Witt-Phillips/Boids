#include "boid.h"
#include "flock.h"
#include "vector.h"
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

int main() {
    //Flock test_flock = Flock(FLOCK_SIZE);
    WorldState test_state = WorldState(FLOCK_SIZE, 0);

    // Graphics
    GLFWwindow* window;

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

    glfwMakeContextCurrent(window);

    // Draw loop
    while (!glfwWindowShouldClose(window))
    {   
        glClear(GL_COLOR_BUFFER_BIT);
        cout << "Got to one timestep!" << endl;
        test_state.timestep();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}