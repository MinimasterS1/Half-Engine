#pragma once

#ifndef MODEL_H
#define MODEL_H

#include "Common.hpp"
#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stbImage.h"

#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <map>

#include <vector>

#include "hlMesh.h"
#include "hlShader.h"

using namespace std;



class ENGINE_API Model {
public:
    Model();
    ~Model();
    Model(string const& path, bool gamma = false);
    Model(const Model& other);
    Model& operator=(const Model& other);
    void Draw(Shader shader);
    void setMeshTextures(const std::vector<Texture>& newTextures);
   // void SerializeModel(const std::string& filename);
  //  void DeserializeModel(const std::string& filename, const std::string& directory);
    void loadModel(string const& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

    // Add other necessary member functions if required.

private:
    void copyModelData(const Model& other);
    void clearModelData();

    std::vector<Mesh> meshes;
    std::vector<Texture> textures_loaded;
    std::string directory;
    bool gammaCorrection;
};



#endif