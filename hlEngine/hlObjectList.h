#pragma once

#ifndef GOBJECTLIST_H
#define GOBJECTLIST_H


#include "hlModel.h"
#include "vector" 

class  ObjectList {

public:



    ObjectList() = default;

    ~ObjectList() = default;

    ObjectList(const  ObjectList&) = delete;

    ObjectList& operator=(const  ObjectList&) = delete;


    int ModelIndex = -1;

    static  ObjectList& getInstance();

    int getModelIndex() const;

    void setModelIndex(int index);




    std::vector<Model> loadedModels;
    std::vector<int> selectedModelIndices;
    std::vector<Model> displayedModels;
    std::string saveDirectory;



};

#endif // GOBJECTLIST_H