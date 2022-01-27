#include <Utilities/UnifiedPtr.hpp>

UnifiedPtr::UnifiedPtr(const size_t size)
{
    cudaError_t error = cudaMallocManaged(&ptr, size * sizeof(char));
    if(error != cudaSuccess)
    {
        throw std::bad_alloc();
    }
}

UnifiedPtr::UnifiedPtr(unsigned char *localPtr, const size_t size)
{
    cudaError_t error = cudaMallocManaged(&ptr, size * sizeof(char));
    if(error != cudaSuccess)
    {
        throw std::bad_alloc();
    }
    std::memcpy(ptr, localPtr, size);
}

UnifiedPtr::~UnifiedPtr()
{
    cudaFree(ptr);
}

unsigned char *UnifiedPtr::getPtr() const
{
    return ptr;
}

bool UnifiedPtr::isAlloc() const
{
    return ptr != nullptr;
}
