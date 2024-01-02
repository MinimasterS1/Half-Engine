#pragma once

#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include "Common.hpp"
#include <string>
#include <vector>



class  RESOURCES_API ResourceLoader {
public:
    ResourceLoader();
    ~ResourceLoader();


    unsigned int LoadTexture(const char* path, const std::string& directory);

   

private:
   
}; 

#endif