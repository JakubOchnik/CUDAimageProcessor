#pragma once
#include <cuda_runtime.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

/**
 * @date 27.01.2022
 * @author Jakub Ochnik
 * 
 * @brief A wrapper class for unified pointer 
 *         (a pointer with content shared between RAM and GPU memory).
 */

class UnifiedPtr
{
    unsigned char *ptr{nullptr};
    size_t dataSize{};

    void safeFree();

public:
    UnifiedPtr();
    UnifiedPtr(const size_t size);
    UnifiedPtr(unsigned char *localPtr, const size_t size);

    UnifiedPtr(UnifiedPtr &&src);
    UnifiedPtr(UnifiedPtr &src);
    UnifiedPtr &operator=(const UnifiedPtr &other);
    UnifiedPtr &operator=(UnifiedPtr &&other);
    ~UnifiedPtr();

    void forcePrefetch(int device = -1);

    unsigned char *getPtr() const;
    size_t size() const;
    bool isAlloc() const;
};