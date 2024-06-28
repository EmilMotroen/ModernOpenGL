#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <sstream>


const char* APP_TITLE = "Introduction to Modern OpenGL";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
GLFWwindow* window = NULL;

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void showFPS(GLFWwindow* window);
bool initOpenGL();

int main() {
    if (!initOpenGL()) {
        std::cerr << "GLFW failed to initialize..." << std::endl;
        return -1;
    }

    /* Main loop */
    while (!glfwWindowShouldClose(window)) {
        showFPS(window);
        glfwPollEvents();

        
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

bool initOpenGL() {
    if (!glfwInit()) {
        std::cerr << "GLFW failed to initialize..." << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_TITLE, NULL, NULL);


    if (window == NULL) {
        std::cerr << "Failed to create GLFW window..." << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, glfw_onKey);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW failed to initialize..." << std::endl;
        return false;
    }

    glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
    return true;
}

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void showFPS(GLFWwindow* window) {
    static double previousSeconds = 0.0;
    static int frameCount = 0;
    double elapsedSeconds;
    double currentSeconds = glfwGetTime();  // Returns the number of seconds since GLFW started

    elapsedSeconds = currentSeconds - previousSeconds;

    // Limit text update 4 times per second
    if (elapsedSeconds > 0.25) {
        previousSeconds = currentSeconds;
        double fps = (double)frameCount / elapsedSeconds;
        double msPerFrame = 1000.0 / fps;

        std::ostringstream outs;
        outs.precision(3);
        outs << std::fixed 
            << APP_TITLE << "     " 
            << "FPS: " << fps << "     " 
            << "Frame Time: " << msPerFrame << " (ms)";

        glfwSetWindowTitle(window, outs.str().c_str());

        frameCount = 0;

    }

    frameCount++;
}