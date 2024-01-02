#pragma once

#ifndef EDITOR_H
#define EDITOR_H

#include "Common.hpp"
#include "hlCore/hlLogger.h"
#include "hlRender/hlrDefines.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <functional>
#include <filesystem>

#include "iostream"

class EDITOR_API Editor {

public:

    Editor();

    Editor(GLFWwindow* window, const char* text);

    ~Editor();

    void RenderEditor();

    void RenderConsole();

    void DrawFrameBuffer();

    void setWidth(int width);

    void setHeight(int height);

    void WindowScale(GLFWwindow* window, int* width, int* height);

    void DrawPanel(const char* name, ImVec2 position, ImVec2 size, std::function<void()> contentFunc);

    int getWidth();
    int getHeight();
    int getXoffset();
    int getYoffset();

    int w, h;

    GLFWwindow* m_Window;

private:
    const char* m_Text;

    int RenderPanelWidth = 1580;
    int RenderPanelHeight = 1090;
    int Offset_X = 0;
    int Offset_Y = 150;

    bool ShowLoadFileDialog = false;
    bool ShowSaveFileDialog = false;

protected:

    Logger editorLog;

};

#endif




