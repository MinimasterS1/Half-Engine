#pragma once

#ifndef INPUT_H
#define INPUT_H

#include "Common.hpp"
#include "hlDefines.h"
 #include <glfw/glfw3.h> 

class  ENGINE_API  Input{
public:



    Input(Camera& camera);

    ~Input();

    void startUp();

    void shutDown();

    void update(GLFWwindow* window, float deltaTime);

    void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    void ProcessInput(GLFWwindow* window, float deltaTime);
     
    void ProcessSingleKeyPress(GLFWwindow* window, int key, int action);


    float Lerp(float a, float b, float t) {

        t = glm::clamp(t, 0.0f, 1.0f);


        return a + t * (b - a);
    }

private:

    Camera& camera;

    float Last_X, Last_Y;
    bool FirstMouse;

    int previousKeyState[GLFW_KEY_LAST + 1];
    bool keyQPressed = false;

};

#endif