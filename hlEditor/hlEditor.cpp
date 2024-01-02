#include "hlEditor.h"

#include "hlCore/hlMemory.h"

#include "hlHeaderPanel.h"
#include "hlEditorConsole.h"
#include "hlBrowser.h"

#include "hlEngine/hlEngine.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>


MemoryPool ConsoleMemory(800, 1024);
MemoryPool EditorMemo(800, 1024);
MemoryPool BrowserMemory(800, 1024);

HeaderPanel* headerPanel = new HeaderPanel();
Console* console = new Console;
ContentBrowser* browser = new ContentBrowser;
//ParticleUI* particles = nullptr;

Engine& displayData = Engine::GetInstance();

Editor::Editor()
{

}

Editor::Editor(GLFWwindow* window, const char* text)
{
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontGlobalScale = 1.0f;

    // ImFont* myFont = io.Fonts->AddFontFromFileTTF("../Gear/x64/Debug/gamedata/Fonts/Univers.ttf", 18.0f);

   // if (myFont == nullptr) { LOG.Log(Logger::LogLevel::Error, "Error set Font ", NULL); }


    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.08f, 0.69f, 0.63f, 1.0f));  //text color
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(50, 50, 50, 255)); // buttons color
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.05f, 0.05f, 0.05f, 1.0f)); //window color
    ImVec4 inactiveTitleBg = ImGui::GetStyleColorVec4(ImGuiCol_TitleBg);
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, inactiveTitleBg);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.0f;
    style.FrameRounding = 2.0f;

    bool allInitialized = true;

    if (allInitialized) {


        HeaderPanel* headerPanel = new(EditorMemo.allocate(sizeof(HeaderPanel))) HeaderPanel();

        Console* console = new(ConsoleMemory.allocate(sizeof(Console))) Console();

        ContentBrowser* contentBrowser = new(BrowserMemory.allocate(sizeof(ContentBrowser))) ContentBrowser();

        //console = new Console();
       // browser = new ContentBrowser();
       // particles = new ParticleUI();
    }

}
Editor::~Editor()
{
    //ContentBrowser->~ContentBrowser(); // Вызовите деструктор (если это необходимо)


    ImGui_ImplOpenGL3_Shutdown();

    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

}

void Editor::RenderEditor()
{
    // WindowScale(m_Window, &w, &h);

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (EditorMode)
    {

        if (headerPanel->GetCurrentTab() == HeaderPanel::LEVEL)
        {
            editorLog.Log(Logger::LogLevel::Info, "Go");


        }

        if (headerPanel->GetCurrentTab() == HeaderPanel::PARTICLE)
        {
            headerPanel->DrawHeaderPanel();
            console->DrawConsole();
            // browser->DrawBrowser();


           // particles->DrawEmitterSettings();

            // BrowserMemory.deallocate(headerPanel, sizeof(ContentBrowser));

        }
        DrawFrameBuffer();
        headerPanel->DrawHeaderPanel();
        console->DrawConsole();
        browser->DrawBrowser();
        browser->DrawSceneObjects();
        browser->DrawProperties();
    }

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void Editor::RenderConsole()
{
    // WindowScale(m_Window, &w, &h);

    ImVec2 windowSize = ImGui::GetIO().DisplaySize;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::DrawFrameBuffer()
{
    int w, h;
    WindowScale(window, &w, &h);



    ImGui::SetNextWindowPos(ImVec2(w / 7, 150));

    ImGui::SetNextWindowSize(ImVec2(w - (w / 3.5), h - 200));

    ImGuiStyle& default_style = ImGui::GetStyle();
    ImVec4 default_window_bg = default_style.Colors[ImGuiCol_WindowBg];

    ImGuiStyle& style = ImGui::GetStyle();

    style.Colors[ImGuiCol_WindowBg].w = 0.0f;

    ImGui::Begin("Background Window", nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);


    ImGui::Text("FPS: %.1f", displayData.gRenderManager.getFPS());



    // ImGui::Text("Time: %.1f", VideoManager::GetSimTime());



    ImGui::Text("Polys: %.1f", "0");


    ImGui::Text("Vertex: %.1f", "0");

    ImGui::End();

    style.Colors[ImGuiCol_WindowBg] = default_window_bg;


}

void Editor::WindowScale(GLFWwindow* window, int* width, int* height)
{
    {

        {
            if (window == NULL) {

                editorLog.Log(Logger::LogLevel::Info, "now window", NULL);
                return;

            }

            glfwGetWindowSize(window, width, height);

            if (width && height) {

                w = *width;
                h = *height;

                // LOG.Log(Logger::LogLevel::INFO, "Scale", *width);

            }

        }
    }
}

void Editor::DrawPanel(const char* name, ImVec2 position, ImVec2 size, std::function<void()> contentFunc)
{
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;

    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);

    if (ImGui::Begin(name, nullptr, flags))
    {
        contentFunc();
        ImGui::End();
    }

}

int Editor::getWidth()
{
    return RenderPanelWidth;
}

int Editor::getHeight()
{
    return RenderPanelHeight;
}

int Editor::getYoffset()
{
    return 0;
}

void Editor::setWidth(int width)
{
    RenderPanelWidth = width;
}

void Editor::setHeight(int height)
{
    RenderPanelHeight = height;
}

int Editor::getXoffset()
{
    return Offset_Y;
}

