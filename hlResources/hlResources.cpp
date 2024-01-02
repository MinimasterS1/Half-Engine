#include "hlResources.h"

#include "Common.hpp"
#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "hlEngine/stbImage.h"

#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
    std::string filename = std::string(path);
    filename = directory + '/' + filename;
    std::cout << "Texture at path Load model: " << directory << std::endl;
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

        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

        // Добавляем таймер, чтобы функция сработала через 5 секунд
        std::thread timerThread([textureID]() {
            auto start_time = std::chrono::high_resolution_clock::now();
            auto end_time = start_time + std::chrono::seconds(5);

            while (std::chrono::high_resolution_clock::now() < end_time) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            std::cout << "Function has been executed after 5 seconds. Texture ID: " << textureID << std::endl;
            });

        timerThread.detach(); // Отсоединяем поток, чтобы он работал независимо

    }
    else
    {
        // std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
        return 0;
    }

    return textureID;
}

