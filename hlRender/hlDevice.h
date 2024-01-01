#pragma once

#include "Common.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


RENDER_API void MonitorScale(int* width, int* height);


void MonitorScale(int* width, int* height)
{
    {
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        if (primaryMonitor == NULL) {

            glfwTerminate();
            return;
        }

        const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

        if (mode == NULL) {

            glfwTerminate();
            return;
        }
        if (width) {
            *width = mode->width;

        }
        if (height) {
            *height = mode->height;

        }
    }

}