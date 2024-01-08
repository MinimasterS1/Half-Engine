#pragma once

#ifndef STATIC_MESH_H
#define STATIC_MESH_H

#include "hlDefines.h"
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "hlShader.h"
#include <string>
#include <vector>

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
    std::vector<unsigned char> data;
};

class ENGINE_API StaticMesh {
public:
    StaticMesh();
    StaticMesh(const StaticMesh& other);
    StaticMesh(StaticMesh&& other) noexcept;
    StaticMesh& operator=(const StaticMesh& other);
    StaticMesh& operator=(StaticMesh&& other) noexcept;
    ~StaticMesh();

    StaticMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    void setMeshTextures(const std::vector<Texture>& newTextures);
    void Initialize(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader& shader);

    void setupMesh();

    unsigned int VAO;
    unsigned int VBO, EBO;
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;


   
};

#endif // MESH_H
