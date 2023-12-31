﻿#include "hlResources.h"

#include "Common.hpp"
#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stbImage.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <map>

#include <string>

#include <vector>

#include <chrono>
#include <thread>

ResourceLoader::ResourceLoader() {
   
}

ResourceLoader::~ResourceLoader() {
    
}

unsigned int ResourceLoader::LoadTexture(const char* path, const std::string& directory)
{
    std::string filename = directory + '/' + path;
    std::cout << "Texture at path Load model: " << filename << std::endl;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        else
        {
            std::cerr << "Error: Unknown number of components in texture: " << nrComponents << std::endl;
            stbi_image_free(data);
            return 0;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Error: Failed to load texture at path: " << filename << std::endl;
        return 0;
    }

    return textureID;
}



