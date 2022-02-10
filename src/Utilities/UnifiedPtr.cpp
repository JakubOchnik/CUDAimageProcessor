#include <Utilities/UnifiedPtr.hpp>

UnifiedPtr::UnifiedPtr()
{
}

UnifiedPtr::UnifiedPtr(const size_t size) : dataSize(size * sizeof(char))
{
    cudaError_t error = cudaMallocManaged(&ptr, size * sizeof(char));
    if (error != cudaSuccess)
    {
        ptr = nullptr;
        dataSize = 0;
        throw std::bad_alloc();
    }
}

UnifiedPtr::UnifiedPtr(unsigned char *localPtr, const size_t size) : dataSize(size * sizeof(char))
{
    cudaError_t error = cudaMallocManaged(&ptr, size * sizeof(char));
    if (error != cudaSuccess)
    {
        ptr = nullptr;
        dataSize = 0;
        throw std::bad_alloc();
    }
    std::memcpy(ptr, localPtr, size);
}

UnifiedPtr::UnifiedPtr(UnifiedPtr &&other) : ptr{other.getPtr()}, dataSize{other.size()}
{
    safeFree();

    ptr = other.getPtr();
    dataSize = other.size();
    other.dataSize = 0;
    other.ptr = nullptr;
}

UnifiedPtr::UnifiedPtr(UnifiedPtr &other)
{
    // Memory was allocated, but has a different size -
    // worst case, it needs to be reallocated (free - malloc - copy).
    if (isAlloc() && dataSize != other.size())
    {
        safeFree();
    }
    // Allocate memory if the size doesn't match (memory not allocated or freed in prev step).
    if (dataSize != other.size())
    {
        cudaError_t error = cudaMallocManaged(&ptr, other.size() * sizeof(char));
        if (error != cudaSuccess)
        {
            ptr = nullptr;
            dataSize = 0;
            throw std::bad_alloc();
        }
    }
    // Copy the original content.
    dataSize = other.size();
    std::memcpy(ptr, other.getPtr(), dataSize);
}

UnifiedPtr &UnifiedPtr::operator=(const UnifiedPtr &other)
{
    // Memory was allocated, but has a different size -
    // worst case, it needs to be reallocated (free - malloc - copy).
    if (isAlloc() && dataSize != other.size())
    {
        safeFree();
    }
    // Allocate memory if the size doesn't match (memory not allocated or freed in prev step).
    if (dataSize != other.size())
    {
        cudaError_t error = cudaMallocManaged(&ptr, other.size() * sizeof(char));
        if (error != cudaSuccess)
        {
            ptr = nullptr;
            dataSize = 0;
            throw std::bad_alloc();
        }
    }
    // Copy the original content.
    dataSize = other.size();
    std::memcpy(ptr, other.getPtr(), dataSize);
    return *this;
}

UnifiedPtr &UnifiedPtr::operator=(UnifiedPtr &&other)
{
    safeFree();

    dataSize = other.size();
    ptr = other.getPtr();

    other.dataSize = 0;
    other.ptr = nullptr;
    return *this;
}

void UnifiedPtr::forcePrefetch(int device)
{
    if (!isAlloc())
    {
        return;
    }
    if (device == -1)
    {
        cudaGetDevice(&device);
    }
    cudaMemPrefetchAsync(ptr, dataSize * sizeof(char), device, NULL);
}

UnifiedPtr::~UnifiedPtr()
{
    if (isAlloc())
    {
        safeFree();
    }
}

unsigned char *UnifiedPtr::getPtr() const
{
    return ptr;
}

size_t UnifiedPtr::size() const
{
    return dataSize;
}

bool UnifiedPtr::isAlloc() const
{
    return dataSize != 0 || ptr != nullptr;
}

void UnifiedPtr::safeFree()
{
    if (isAlloc())
    {
        cudaFree(ptr);
    }
}
