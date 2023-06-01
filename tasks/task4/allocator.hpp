#pragma once

struct Chunk {
    Chunk* next;
};

class PoolAllocator {
public:
    PoolAllocator(size_t chunksPerBlock) : chunksPerBlock_(chunksPerBlock), alloc_(nullptr) { }

    void* allocate(size_t size) {
        if (alloc_ == nullptr) {
            alloc_ = allocateBlock(size);
        }
        Chunk* FreeMemory = alloc_; 
        alloc_ = alloc_->next;
        return FreeMemory;
    }

    void deallocate(void* chunk, size_t size) {
        reinterpret_cast<Chunk*>(chunk)->next = alloc_;
        alloc_ = reinterpret_cast<Chunk*>(chunk);
    }

private:
    size_t chunksPerBlock_;
    Chunk* alloc_;

private:
    Chunk* allocateBlock(size_t chunkSize) {
        Chunk* BlockBeginning = reinterpret_cast<Chunk*>(malloc(chunkSize * chunksPerBlock_));
        Chunk* tmp = BlockBeginning;
        for (size_t i = 0; i < chunksPerBlock_ - 1; i++) {
            tmp->next = reinterpret_cast<Chunk*>(reinterpret_cast<char*>(tmp) + chunkSize);
            tmp = tmp->next;
        }
        tmp->next = nullptr;
        return BlockBeginning;
    }
};
