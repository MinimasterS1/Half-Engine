#pragma once

#ifndef RDEFINES_H
#define RDEFINES_H

#include "Common.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "hlCore/hlLogger.h"

extern GLFWwindow* window;

extern GLFWwindow* m_window;

extern Logger RenderLog;

extern int SCR_WIDTH, SCR_HEIGHT;

extern bool EditorMode;




#endif 