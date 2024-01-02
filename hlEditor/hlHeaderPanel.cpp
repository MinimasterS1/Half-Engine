#include "hlHeaderPanel.h"
#include "ImGuiFileDialog.h"


#include "hlEngine/hlEngine.h"


Engine& res = Engine::GetInstance();
//Scene& my = Scene::Instance();

//ObjectList& object = ObjectList::getInstance();


HeaderPanel::HeaderPanel()
{

}

HeaderPanel::~HeaderPanel()
{

}

void HeaderPanel::DrawHeaderPanel()
{
    ImVec2 buttonSize = ImVec2(65, 25);

    int w, h;
    WindowScale(window, &w, &h);


    int panelHeight = std::max(h - 2500, 150);

    DrawPanel("Toolbar", ImVec2(0, 0), ImVec2(w, panelHeight), [&]()
        {




            if (ImGui::Button("Load", buttonSize)) {


                ImGuiFileDialog::Instance()->OpenDialog("LoadFileDlgKey", "Load File", ".lvl", ".");

            }

            if (ImGuiFileDialog::Instance()->Display("LoadFileDlgKey")) {
                // Проверяем, что пользователь подтвердил выбор файла
                if (ImGuiFileDialog::Instance()->IsOk()) {
                    std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                    std::cout << "Load file: " << filePathName << std::endl;


                    //Resources::Instance().LoadObjectPositions(filePathName);
                  /////////////  res.resources.LoadObjectPositions(filePathName);

                    ImGuiFileDialog::Instance()->Close();
                }

                // Если пользователь нажал "Отмена" в диалоге, просто закрываем его
                else {
                    ImGuiFileDialog::Instance()->Close();
                }
            }

            ImGui::SameLine();

            if (ImGui::Button("Level", buttonSize)) {
                currentTab = LEVEL;

            }

            ImGui::SameLine();
            if (ImGui::Button("Materials", buttonSize)) {
                currentTab = MATERIAL;
            }
            ImGui::SameLine();
            if (ImGui::Button("Particles", buttonSize)) {
                currentTab = PARTICLE;
            }

            if (ImGui::Button("Simulation", buttonSize)) {
                // Действия при нажатии
            }
            ImGui::SameLine();
            if (ImGui::Button("Animations", buttonSize)) {
                currentTab = ANIMATION;
            }
            if (ImGui::Button("Save", buttonSize))
            {
                if (currentTab == PARTICLE)
                {
                    ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlgKey", "Save File", ".part", ".");
                    ShowSaveFileDialog = true;
                }

                if (currentTab == LEVEL)
                {
                    ImGuiFileDialog::Instance()->OpenDialog("SaveFileDlgKey", "Save File", ".lvl", ".");

                    ShowSaveFileDialog = true;
                }

            }

            if (ShowSaveFileDialog)
            {
                // Prepare file dialog
                if (ImGuiFileDialog::Instance()->Display("SaveFileDlgKey"))
                {
                    if (ImGuiFileDialog::Instance()->IsOk())
                    {
                        std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                        std::cout << "Save file: " << filePathName << std::endl;

                        std::string chosenFileName = ImGuiFileDialog::Instance()->GetCurrentFileName();

                        editorLog.Log(Logger::LogLevel::Save, "Call Save Func", NULL);
                        /////////////////////////////// res.resources.SaveObjectPositions(chosenFileName);

                         // Создайте пустой файл в зависимости от текущего типа файла
                        if (currentFileType == FILE_PART)
                        {
                            if (filePathName.find(".part") != std::string::npos)
                            {
                                std::ofstream outputFile(filePathName, std::ios::binary);

                                if (outputFile.is_open())
                                {
                                    outputFile.close();
                                }
                                else
                                {
                                    // Обработка ошибки: не удалось создать файл
                                    // Вы можете добавить здесь код обработки ошибки по вашему усмотрению
                                }
                            }
                        }

                        else if (currentFileType == FILE_LVL)
                        {


                        }
                        else if (currentFileType == FILE_MAT)
                        {
                            // Создайте пустой файл .mat
                        }
                        // Другие условия для других типов файлов
                        // ...

                        ImGuiFileDialog::Instance()->Close();
                        ShowSaveFileDialog = false;
                    }

                    ImGuiFileDialog::Instance()->Close();
                }
            }

            ImGui::Separator();


            ImVec2 buttonSize = ImVec2(60, 24);


            if (ImGui::Button("Actor", buttonSize)) {

            }

            ImGui::SameLine();

            ImGui::Text("Light:");

            ImGui::SameLine();

            /*  if (ImGui::Button("Direct.", buttonSize)) {

                  if (DirectionalLightProperties)
                  {
                      DirectionalLightProperties = false;
                  }
                 else
                  {
                      DirectionalLightProperties = true;
                  }

              }

              */


            ImGui::SameLine();

            if (ImGui::Button("Spot ", buttonSize)) {

            }

            ImGui::SameLine();

            if (ImGui::Button("Point", buttonSize)) {

            }

            ImGui::SameLine();


            ImGui::Text("Trigger: ");

            ImGui::SameLine();

            if (ImGui::Button("Box", buttonSize)) {

            }

            ImGui::SameLine();


            if (ImGui::Button("Sphere", buttonSize)) {

            }

            ImGui::SameLine();


            if (ImGui::Button("Cylinder", buttonSize)) {

            }

            ImGui::SameLine();

            ImGui::Text("DragStep: ");

            ImGui::SameLine();

            ImGui::SetNextItemWidth(70.0f);
            static float tempDragStep = 0.03;
            if (ImGui::DragFloat("##DragStep", &tempDragStep)) {
              //  DragStep = tempDragStep;
            }

            ImGui::SameLine();

            ImGui::Text("CameraSpeed: ");

            ImGui::SameLine();


            ImGui::SetNextItemWidth(70.0f);
            static float tempCameraSpeed = 10.0f;
            if (ImGui::DragFloat("##CameraSpeed", &tempCameraSpeed)) {

                camera.SetSpeed(tempCameraSpeed);
                // camera.updateCameraVectors();


            }

            ImGui::SameLine();

            ImGui::Text("Block Volume: ");

            ImGui::SameLine();

            if (ImGui::Button("Box", buttonSize)) {

            }

            ImGui::SameLine();


            if (ImGui::Button("Sphere", buttonSize)) {

            }

            ImGui::SameLine();


            if (ImGui::Button("Cylinder", buttonSize)) {

            }

            ImGui::SameLine();



            ImGui::Text("Sound Source: ");

            ImGui::SameLine();

            if (ImGui::Button("Add ", buttonSize)) {

            }

            ImGui::SameLine();
            ImGui::Text("Gravity Zone: ");

            ImGui::SameLine();

            if (ImGui::Button(" Add ", buttonSize)) {

            }

            ImGui::SameLine();
            ImGui::Text("Window Flags: ");

            ImGui::SameLine();

            static bool checkboxValue = false;
            if (ImGui::Checkbox("##Window Flags ", &checkboxValue))
            {

            }

            ImGui::SameLine();

            if (ImGui::Button("Memory ", buttonSize))
            {

            }



        });
}

HeaderPanel::SelectedTab HeaderPanel::GetCurrentTab() const
{
    return SelectedTab();
}

void HeaderPanel::SetCurrentTab(SelectedTab tab)
{

    currentTab = tab;

}





