#include "hlInput.h"


Input::Input(Camera& cam) : camera(cam), FirstMouse(true)

{

    for (int i = 0; i <= GLFW_KEY_LAST; i++) {
        previousKeyState[i] = GLFW_RELEASE;
    }
}

Input::~Input() {}

void Input::startUp() {




}

void Input::shutDown() {


}

void Input::update(GLFWwindow* window, float deltaTime) {

    ProcessInput(window, deltaTime);
}

void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos)

{

    if (FirstMouse) {
        Last_X = xpos;
        Last_Y = ypos;
        FirstMouse = false;
    }


}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{


}

void Input::ProcessSingleKeyPress(GLFWwindow* window, int key, int action)
{

}

void Input::ProcessInput(GLFWwindow* window, float deltaTime)
{

    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }


}
