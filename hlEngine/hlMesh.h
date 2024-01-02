#pragma once

#ifndef MESH_H
#define MESH_H

#include "Common.hpp"
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

class ENGINE_API Mesh {
public:
    Mesh();
    Mesh(const Mesh& other);
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(const Mesh& other);
    Mesh& operator=(Mesh&& other) noexcept;
    ~Mesh();

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    void setMeshTextures(const std::vector<Texture>& newTextures);
    void Initialize(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader& shader);

private:
    void setupMesh();

    unsigned int VAO;
    unsigned int VBO, EBO;
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
};

#endif // MESH_H
