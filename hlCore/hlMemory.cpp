#include "hlMemory.h"



MemoryPool::MemoryPool()
{

}

MemoryPool::~MemoryPool()
{

}

MemoryPool::MemoryPool(size_t initialSize, size_t maxSize) : max_size(maxSize)
{
    allocateBlock(initialSize);
}

void* MemoryPool::allocate(size_t size, size_t alignment)
{

    size = align(size, alignment);

    auto it = free_blocks.lower_bound(size);
    if (it != free_blocks.end()) {
        void* ptr = it->second.back();
        it->second.pop_back();
        if (it->second.empty()) {
            free_blocks.erase(it);
        }

        MemoryLog.Log(Logger::LogLevel::Info, "Memory Use", size);
        return ptr;
    }

    if (total_size + size <= max_size) {
        allocateBlock(size);
        auto last = --free_blocks.lower_bound(size);
        void* ptr = last->second.back();
        last->second.pop_back();
        if (last->second.empty()) {
            free_blocks.erase(last);
        }
        return ptr;
    }

    return nullptr;

}

void MemoryPool::deallocate(void* ptr, size_t size, size_t alignment)
{

    size = align(size, alignment);
    free_blocks[size].push_back(ptr);

    MemoryLog.Log(Logger::LogLevel::Info, "Memory Free", size);
}

size_t MemoryPool::align(size_t size, size_t alignment)
{

    return (size + alignment - 1) & ~(alignment - 1);

}

void MemoryPool::allocateBlock(size_t size)
{

    std::vector<char> new_block(size);
    blocks.push_back(std::move(new_block));
    free_blocks[size].push_back(blocks.back().data());
    total_size += size;

}
