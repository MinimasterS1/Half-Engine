#include "hlEngine.h"


Engine::Engine()
{

}

Engine::~Engine()
{

}


Engine& Engine::GetInstance()
{
    static Engine instance; // Создается только один раз
    return instance;
}

void Engine::RunApplication()
{
    gRenderManager.startUp();
    gInputManager = new Input(camera);

    // resources.PreloadResources();

     //resources.LoadLevel();

    MainLoop();
}

void Engine::MainLoop()
{

   while (!gRenderManager.ShouldClose()) {

      Update();

       RenderProcess();
  }

}

void Engine::Update()
{
    gRenderManager.update();
}

void Engine::RenderProcess()
{
    gRenderManager.RenderCycle();
}


void Engine::ShutDownApplication()
{
    gRenderManager.shutDown();
   delete gInputManager;
    gInputManager = nullptr;
}

void Engine::AsyncLoadLevel()
{

}



