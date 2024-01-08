#pragma once

#ifndef RENDER_H
#define RENDER_H


#include "Common.hpp"
#include "hlEngine/hlInput.h"
#include "hlEngine/hlDefines.h"
#include "hlrDefines.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "hlEditor/hlEditor.h"

#include <fstream>
#include <iostream>


extern float LastX;
extern float LastY;
extern bool FirstMouse;


bool fileExists(const std::string& filename);

class RENDER_API Render

{
public:

    Render(); 

    ~Render();

    void startUp();

    void shutDown();

    void update();

    static void framebuffer_size_callback_static(GLFWwindow* window, int width, int height);

    void CreateRenderWindow();

    void RenderCycle();

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    void GL_Check(const char* label);

    void swap_buffers() { glfwSwapBuffers(window); }

    void close() { glfwSetWindowShouldClose(window, 1); }

    GLFWwindow* get_glfw_window_handle() { return window; };

    bool should_close() const { return !!glfwWindowShouldClose(window); }

    int get_window_attrib(int attrib) const { return glfwGetWindowAttrib(window, attrib); }


    float getFPS();

    bool ShouldClose();

    bool IsDrawLogo = false;

    Input* input;

   std::unique_ptr<Editor> EditorUI;

private:

    float FPS;
    float DeltaTime;
    float LastFrame;


};

#define GL_CHECK(stmt) do { \
        stmt; \
        CheckOpenGLError(#stmt, __FILE__, __LINE__); \
    } while (0)


#endif
