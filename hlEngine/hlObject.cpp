#include "hlObject.h"

Object::Object()
{

}

Object::~Object()
{

}

Object::Object(Model model) : model(model), Position(0.0f), Rotation(0.0f), Scale(1.0f), HighlightColor(1.0f, 1.0f, 1.0f, 1.0f),
BaseColor(0.0f, 0.0f, 1.0f), TextureOffsetX(0.0f), TextureOffsetY(0.0f), TextureScale(1.0f)
{
    shader = Shader("../Gear/x64/Debug/gamedata/Shaders/model_load_vs.vs", "../Gear/x64/Debug/gamedata/Shaders/model_load_fs.fs");

}

Object::Object(const Object& other)
{
    

}

void Object::setPosition(const glm::vec3& pos) { Position = pos; }

glm::vec3 Object::getPosition() const { { return Position; } }

void Object::setRotation(const glm::vec3& rot) { { Rotation = rot; } }

glm::vec3 Object::getRotation() const { { return Rotation; } }

void Object::setScale(const glm::vec3& s) { { Scale = s; } }

glm::vec3 Object::getScale() const { { return Scale; } }

glm::mat4 Object::getTransform() const {
    glm::mat4 transform = glm::mat4(1.0f); transform = glm::translate(transform, Position);
    transform = glm::rotate(transform, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, Scale);

    return transform;

}

void Object::AddObject(const Object& object) { objects.push_back(object); }


void Object::setObjectName(const std::string& name) { ObjectName = name; }

void Object::setObjectID(const int& ID) { ObjectID = ID; }

const std::string& Object::getObjectName() const { return ObjectName; }

const int& Object::getObjectID() const { return ObjectID; }

std::string Object::getObjectInfo() const
{
    std::string objectInfo = "Object: " + ObjectName + "\n" +
        "Position: (" + std::to_string(Position.x) + ", " +
        std::to_string(Position.y) + ", " +
        std::to_string(Position.z) + ")\n" +

        "Rotation: (" + std::to_string(Rotation.x) + ", " +
        std::to_string(Rotation.y) + ", " +
        std::to_string(Rotation.z) + ")\n" +

        "Scale: (" + std::to_string(Scale.x) + ", " +
        std::to_string(Scale.y) + ", " +
        std::to_string(Scale.z) + ")";

    return objectInfo;

}

glm::mat4 Object::getModelMatrix() const { return getTransform(); }

void Object::setMeshTextures(unsigned int newTextureID)
{
   /* if (hasMeshes())
    {
        std::vector<Texture> newTextures;
        newTextures.push_back(Texture{ newTextureID, "TextureType" });
        model.setMeshTextures(newTextures);
    }*/

}

//bool Object::hasMeshes() const { return !model.meshes.empty(); }

void Object::setHighlightColor(const glm::vec4& color) { HighlightColor = color; }

glm::vec4 Object::getHighlightColor() const { return HighlightColor; }

void Object::setTextureOffsetX(const float moveX) { TextureOffsetX = moveX; }

float Object::getTextureOffsetX() const { return TextureOffsetX; }

void Object::setTextureOffsetY(const float moveY) { TextureOffsetY = moveY; }

float Object::getTextureOffsetY() const { return TextureOffsetY; }

void Object::setTextureScale(const float scale) { TextureScale = scale; }

float Object::getTextureScale() const { return TextureScale; }


void Object::Draw(Camera& camera, int SCR_WIDTH, int SCR_HEIGHT)
{


    camera.projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 modelMat = getTransform();
    glm::mat4 transform = getTransform();

    shader.use();
    shader.setMat4("projection", camera.projection);
    shader.setMat4("view", view);
    shader.setMat4("model", modelMat);
    shader.setVec4("highlightColor", HighlightColor);
    shader.setVec3("baseColor", BaseColor);
    shader.setMat4("model", transform);
    shader.setFloat("offsetX", TextureOffsetX);
    shader.setFloat("offsetY", TextureOffsetY);
    shader.setFloat("textureScale", TextureScale);

    //  LOG.Log(Logger::LogLevel::DEBUG, "TextureOffset", getTextureOffsetX());

    model.Draw(shader);



}


Object& Object::operator=(const Object& other) {
    if (this != &other) {
        
        this->Position = other.Position;
        this->Rotation = other.Rotation;
        this->Scale = other.Scale;
        this->BaseColor = other.BaseColor;
        this->ObjectName = other.ObjectName;
        this->HighlightColor = other.HighlightColor;
        this->TextureOffsetX = other.TextureOffsetX;
        this->TextureOffsetY = other.TextureOffsetY;
        this->TextureScale = other.TextureScale;
        this->model = other.model;
        this->shader = other.shader;
        this->objects = other.objects;
    }

    return *this;
}



/// //////////////////////////////////////////////////////////////////

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::AddObject(const Object& object) { objects.push_back(object); }

void Scene::LogSceneObjectsInfo() const { for (const Object& object : objects) { std::string objectInfo = object.getObjectInfo(); engineLog.Log(Logger::LogLevel::Save, objectInfo.c_str(), NULL); } }

Scene& Scene::Instance()
{

    static Scene instance;
    return instance;

}
