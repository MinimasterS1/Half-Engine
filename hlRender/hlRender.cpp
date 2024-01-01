#include "hlRender.h"
#include "hlDevice.h"

#include "hlCore/hlMemory.h"


Render::Render()
{

}

Render::~Render()
{

}

void Render::startUp()
{
    CreateWindow();

}

void Render::shutDown()
{
    glfwMakeContextCurrent(window);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Render::update()
{
    glfwPollEvents();
}

void Render::framebuffer_size_callback_static(GLFWwindow* window, int width, int height)
{
    {
        Render* render = static_cast<Render*>(glfwGetWindowUserPointer(window));
        if (render)
        {
            render->framebuffer_size_callback(window, width, height);
        }
    }
}

void Render::CreateWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    MonitorScale(&SCR_WIDTH, &SCR_HEIGHT);
    window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT, "Engine", NULL, NULL);
    if (window == NULL)
    {
        RenderLog.Log(Logger::LogLevel::Error, "Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    glfwSetWindowPos(window, 0, 25);
    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);

    input = new Input(camera);
    input->startUp();

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
        static_cast<Render*>(glfwGetWindowUserPointer(window))->input->MouseCallback(window, x, y);
        });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        static_cast<Render*>(glfwGetWindowUserPointer(window))->input->ScrollCallback(window, xoffset, yoffset);
        });

    glfwSetFramebufferSizeCallback(window, Render::framebuffer_size_callback_static);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        RenderLog.Log(Logger::LogLevel::Error, "Failed to initialize GLAD");
        return;
    }

    glEnable(GL_DEPTH_TEST);


}

void Render::RenderCycle()
{
    float currentFrame = glfwGetTime();
    DeltaTime = currentFrame - LastFrame;
    LastFrame = currentFrame;
    FPS = 1.0f / DeltaTime;

    input->update(window, DeltaTime);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


    glfwSwapBuffers(window);
   return;
}

void Render::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Render::GL_Check(const char* label)
{
    {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            const char* errorStr;
            switch (err) {
            case GL_INVALID_ENUM: errorStr = "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE: errorStr = "GL_INVALID_VALUE"; break;
            case GL_INVALID_OPERATION: errorStr = "GL_INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY: errorStr = "GL_OUT_OF_MEMORY"; break;
            default: errorStr = "Unknown Error"; break;
            }

            double errorDouble = static_cast<double>(err);

            std::string errorMessage = "OpenGL Error [" + std::string(label) + "]: " + errorStr;

            RenderLog.Log(Logger::LogLevel::Error, errorMessage, errorDouble);
            std::cerr << errorMessage << std::endl;
        }
    }
}

float Render::getFPS()
{
    
    return FPS;
    
}

bool Render::ShouldClose()
{

    return glfwWindowShouldClose(window);

}

bool fileExists(const std::string& filename)
{
    std::ifstream file(filename);
    return file.good();
}

