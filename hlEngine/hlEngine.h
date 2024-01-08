#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include "Common.hpp"
#include "hlDefines.h"
#include "hlInput.h"
#include "hlRender/hlRender.h"


class ENGINE_API Engine
{
public:

    static Engine& GetInstance();

    void RunApplication();

    void MainLoop();

    void Update();

    void RenderProcess();

    void ShutDownApplication();

    void AsyncLoadLevel();


    Render gRenderManager;
   
    Input* gInputManager = nullptr;

private:

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    Engine();

    ~Engine();


};


#endif 