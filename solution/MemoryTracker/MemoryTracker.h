#pragma once

#include <map>
#include <mutex>
#include <new> // std::bad_alloc

namespace ue
{

struct AllocationInfo
{
    size_t size{ 0 };
    const char* file{ nullptr };
    int line{ 0 };
};

class MemoryTracker
{
private:
    std::mutex mutex;
    std::map<void*, AllocationInfo> allocations;
    size_t allocationCount{ 0 };
    size_t totalAllocated{ 0 };
    void (*onNew)(void* ptr, size_t size, const char* file, int line) { nullptr };
    void (*onDelete)(void* ptr, size_t size, const char* file, int line) { nullptr };

private:
    MemoryTracker() = default;

public:
    MemoryTracker(const MemoryTracker&) = delete;
    MemoryTracker& operator=(const MemoryTracker&) = delete;

    static MemoryTracker& getInstance();
    void trackAllocation(void* pointer, size_t size, const char* file, int line);
    void trackDeallocation(void* pointer);
	inline size_t getAllocationCount() const { return allocationCount; }
	inline size_t getTotalAllocated() const { return totalAllocated; }
	void getReport(std::map<void*, AllocationInfo>& resultAllocations) const;
};

} // namespace

// new com arquivo e linha
void* operator new(size_t size, const char* file, int line);
void* operator new[](size_t size, const char* file, int line);
void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;
void operator delete(void* ptr, size_t size) noexcept;
void operator delete[](void* ptr, size_t size) noexcept;

#define new new(__FILE__, __LINE__)
