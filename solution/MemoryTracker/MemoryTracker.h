#pragma once

#include <map>
#include <mutex>
#include <new> // std::bad_alloc

template <typename T>
struct UntrackedAllocator
{
    UntrackedAllocator() noexcept = default;

    template <typename U>
    UntrackedAllocator(const UntrackedAllocator<U>&) noexcept {}

    using value_type = T;

    T* allocate(size_t n)
    {
        return (T*)std::malloc(n * sizeof(T));
    }

    void deallocate(T* p, size_t n)
    {
        std::free(p);
    }

    template <typename U>
    struct rebind
    {
        using other = UntrackedAllocator<U>;
    };

    bool operator==(const UntrackedAllocator&) const { return true; }
    bool operator!=(const UntrackedAllocator&) const { return false; }
};

struct AllocationInfo
{
    size_t size{ 0 };
    const char* file{ nullptr };
    int line{ 0 };
	void* pointer{ nullptr };
};

using MapPair = std::pair<void* const, AllocationInfo>;

namespace ue
{

class MemoryTracker
{
private:
    std::mutex mutex;
    std::map<void*, AllocationInfo, std::less<void*>, UntrackedAllocator<MapPair>> allocations;
    size_t allocationCount{ 0 };
    size_t totalAllocated{ 0 };
    void (*onNew)(void* ptr, size_t size, const char* file, int line) { nullptr };
    void (*onDelete)(void* ptr, size_t size, const char* file, int line) { nullptr };
    bool initialized{ false };

	static const size_t MAX_PRE_INIT_ALLOCATIONS = 10240;
	AllocationInfo preInitAllocations[MAX_PRE_INIT_ALLOCATIONS];
    size_t preInitIndex{ 0 };

public:
    MemoryTracker& operator=(const MemoryTracker&) = delete;

    void initialize();
    void trackAllocation(void* pointer, size_t size, const char* file, int line);
    void trackDeallocation(void* pointer);
	inline size_t getAllocationCount() { return allocationCount; }
	inline size_t getTotalAllocated() { return totalAllocated; }
    void getReport(std::map<void*, AllocationInfo, std::less<void*>, UntrackedAllocator<MapPair>>& resultAllocations);
	void reportLeaks();
};

} // namespace

extern ue::MemoryTracker& GetMemoryTracker();

// new com arquivo e linha
void* operator new(size_t size, const char* file, int line);
void* operator new[](size_t size, const char* file, int line);
void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;
void operator delete(void* ptr, size_t size) noexcept;
void operator delete[](void* ptr, size_t size) noexcept;
