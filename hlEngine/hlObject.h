#pragma once

#ifndef OBJECT_H
#define OBJECT_H


#include "Common.hpp"
#include "hlEngine/hlDefines.h"
#include "hlModel.h"
#include <glm/glm.hpp>
#include <fstream>
#include "iostream"
#include <filesystem>
#include <vector>

class ENGINE_API Object {
public:

    Object();

    ~Object();

    Object(Model model);

    Object(const Object& other);

    void Draw(Camera& camera, int SCR_WIDTH, int SCR_HEIGHT);

    void AddObject(const Object& object);

    void setMeshTextures(unsigned int newTextureID);

    void setObjectName(const std::string& name);

    void setObjectID(const int& ID);

   // bool hasMeshes() const;


    void setPosition(const glm::vec3& pos);
    glm::vec3 getPosition() const;

    void setRotation(const glm::vec3& rot);
    glm::vec3 getRotation() const;

    void setScale(const glm::vec3& s);
    glm::vec3 getScale() const;

    glm::mat4 getTransform() const;

    void setHighlightColor(const glm::vec4& color);
    glm::vec4 getHighlightColor() const;

    void setTextureOffsetX(const float moveX);
    float getTextureOffsetX() const;

    void setTextureOffsetY(const float moveY);
    float getTextureOffsetY() const;

    void setTextureScale(const float scale);
    float getTextureScale() const;


    const std::string& getObjectName() const;

    const int& getObjectID() const;

    std::string getObjectInfo() const;

    glm::mat4 getModelMatrix() const;

    std::vector<Object> objects;

    Model model;

    Shader shader;

    int ObjectID;

    Object& operator=(const Object& other);




private:



    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;
    glm::vec3 BaseColor;

    std::string ObjectName;

    glm::vec4 HighlightColor;

    float TextureOffsetX;
    float TextureOffsetY;
    float TextureScale;
};

#endif SCENE_OBJECT_H


#ifndef SCENE_H
#define SCENE_H


class ENGINE_API Scene {
public:

    Scene();

    ~Scene();

    std::vector<Object> objects;

    void AddObject(const Object& object);

    void LogSceneObjectsInfo() const;

    static Scene& Instance();


};


#endif SCENE_

