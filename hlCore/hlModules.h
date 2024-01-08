#pragma once

#include "hlEngine/hlEngine.h"
#include "hlRender/hlRender.h"
#include "hlResources/hlResources.h"
#include "hlEditor/hlEditor.h"
#include "hlAnimation/hlAnimation.h"
#include "hlGame/hlGame.h"
#include "hlPhysics/hlPhysics.h"

#include "hlEngine/hlShader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <map>

#include <vector>


class CORE_API IRender {

public:

    virtual ~IRender() = default;

    virtual void startUp() = 0;
    virtual void shutDown() = 0;
    virtual void update() = 0;
    virtual void CreateWindow() = 0;
    virtual void RenderCycle() = 0;
    virtual void swap_buffers() = 0;
    virtual void close() = 0;
    virtual GLFWwindow* get_glfw_window_handle() = 0;
    virtual bool should_close() const = 0;
    virtual int get_window_attrib(int attrib) const = 0;
    virtual float getFPS() = 0;
    virtual bool ShouldClose() = 0;

};

class CORE_API IEngine {

public:

    virtual ~IEngine() = default;

    virtual void RunApplication() = 0;
    virtual void MainLoop() = 0;
    virtual void Update() = 0;
    virtual void RenderProcess() = 0;
    virtual void ShutDownApplication() = 0;
    virtual void AsyncLoadLevel() = 0;

};

class CORE_API IInput {

public:
    virtual ~IInput() = default;

    virtual void startUp() = 0;
    virtual void shutDown() = 0;
    virtual void update(GLFWwindow* window, float deltaTime) = 0;
    virtual void MouseCallback(GLFWwindow* window, double xpos, double ypos) = 0;
    virtual void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) = 0;
    virtual void ProcessInput(GLFWwindow* window, float deltaTime) = 0;
    virtual void ProcessSingleKeyPress(GLFWwindow* window, int key, int action) = 0;

};

class  CORE_API IModel{

public:

    virtual ~IModel() = default;

    virtual void  Draw(Shader shader) = 0;
    virtual void  setMeshTextures(const std::vector<Texture>& newTextures) = 0;
    virtual void SerializeModel(const std::string& filename) = 0;
    virtual void DeserializeModel(const std::string& filename, const std::string& directory) = 0;
    virtual void loadModel(string const& path) = 0;
    virtual void processNode(aiNode* node, const aiScene* scene) = 0;
    virtual void processMesh(aiMesh* mesh, const aiScene* scene) = 0;
   
};

class IEditor {
public:
    virtual void EditScene() = 0;
};