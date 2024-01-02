#include "hlRender.h"
#include "hlDevice.h"

#include "hlCore/hlMemory.h"

#include "hlEngine/hlShader.h"
#include "hlEngine/hlModel.h"

Shader testShader;
Model testModel;


bool firstMouse = true;

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


    stbi_set_flip_vertically_on_load(true);

   
   
    testShader = Shader("C:/Half Engine/Engine/Shaders/model.vs", "C:/Half Engine/Engine/Shaders/model.fs");
    testModel = Model("C:/Half Engine/Engine/gamedata/terrain.obj");
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
   
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  
    testShader.use();

   camera.projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    
    testShader.setMat4("projection", camera.projection);
    testShader.setMat4("view", view);

    GL_Check("no");


    // Рендеринг загруженной модели
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // смещаем вниз чтобы быть в центре сцены
   model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// объект слишком большой для нашей сцены, поэтому немного уменьшим его
    testShader.setMat4("model", model);
    testModel.Draw(testShader);

   // GLint numTriangles;
   // glGetProgramiv(testShader.GetShaderID(), GL_GEOMETRY_VERTICES_OUT, &numTriangles);
   
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLE);

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

