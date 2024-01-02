#include "build_config.h"

#include"hlEngine/hlEngine.h"

 class Engine& engine = Engine::GetInstance();

int main(int argc, const char* argv[])
{


    engine.RunApplication();
   
    return 0;
}