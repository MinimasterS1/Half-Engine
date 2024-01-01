#pragma once

#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include "Common.hpp"
#include <map>
#include <vector>
#include <numeric>
#include <algorithm>
#include <memory>

#include <iostream>


class CORE_API MemoryPool {
public:

    MemoryPool();

    ~MemoryPool();

    MemoryPool(size_t initialSize, size_t maxSize);

    void* allocate(size_t size, size_t alignment = alignof(std::max_align_t));

    void deallocate(void* ptr, size_t size, size_t alignment = alignof(std::max_align_t));


private:

    size_t align(size_t size, size_t alignment);
    void allocateBlock(size_t size);

    size_t max_size;
    size_t total_size = 0;
    std::map<size_t, std::vector<void*>> free_blocks;
    std::vector<std::vector<char>> blocks;
};

#endif