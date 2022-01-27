#pragma once
#include <cuda_runtime.h>
#include <cstring>
#include <stdexcept>

/**
 * @date 27.01.2022
 * @author Jakub Ochnik
 * 
 * @brief A wrapper class for unified pointer 
 *         (a pointer with content shared between RAM and GPU memory).
 */

class UnifiedPtr
{
    unsigned char *ptr = nullptr;

public:
    UnifiedPtr(const size_t size);
    UnifiedPtr(unsigned char *localPtr, const size_t size);
    ~UnifiedPtr();

    unsigned char *getPtr() const;
    bool isAlloc() const;
};