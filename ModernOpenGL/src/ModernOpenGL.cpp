#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <sstream>


const char* APP_TITLE = "Introduction to Modern OpenGL";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const bool FULLSCREEN = false;

void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void showFPS(GLFWwindow* window);

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW failed to initialize..." << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* pWindow = NULL;

    if (FULLSCREEN) {
        GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* pVmode = glfwGetVideoMode(pMonitor);
        if (pVmode != NULL) {
            pWindow = glfwCreateWindow(pVmode->width, pVmode->height, APP_TITLE, pMonitor, NULL);
        }
    }
    else {
        pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_TITLE, NULL, NULL);
    }

    
    if (pWindow == NULL) {
        std::cerr << "Failed to create GLFW window..." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(pWindow);

    glfwSetKeyCallback(pWindow, glfw_onKey);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW failed to initialize..." << std::endl;
        return -1;
    }

    /* Main loop */
    while (!glfwWindowShouldClose(pWindow)) {
        showFPS(pWindow);
        glfwPollEvents();

        glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(pWindow);
    }

    glfwTerminate();
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