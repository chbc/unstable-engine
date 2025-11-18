#include "MemoryTracker.h"

#include <iostream>

namespace ue
{

void MemoryTracker::initialize()
{
    for (size_t i = 0; i < preInitIndex; ++i)
    {
        const AllocationInfo& info = preInitAllocations[i];

        if (info.pointer)
        {
            allocations.emplace(info.pointer, info);
            totalAllocated += info.size;
			allocationCount++;
        }
	}

	preInitIndex = 0;
    initialized = true;
}

void MemoryTracker::trackAllocation(void* pointer, size_t size, const char* file, int line)
{
    AllocationInfo allocInfo{ size, file, line, pointer };

    if (initialized)
    {
        std::lock_guard<std::mutex> lock(mutex);

        allocations.emplace(pointer, allocInfo);

        totalAllocated += size;
        allocationCount++;

        if (onNew)
        {
            onNew(pointer, size, file, line);
        }
    }
    else if (preInitIndex < MAX_PRE_INIT_ALLOCATIONS)
    {
        /*
        std::cout << "[MemoryTracker] Allocation " << preInitIndex << " | at: "
			<< file << ":" << line << " (" << size << " bytes)\n";
        */
        preInitAllocations[preInitIndex] = allocInfo;
        preInitIndex++;
	}
    else
    {
		throw "[MemoryTracker] Pre-initialization allocation limit exceeded!";
    }
}

void MemoryTracker::trackDeallocation(void* pointer)
{
    if (initialized)
    {
        std::lock_guard<std::mutex> lock(mutex);

        if (pointer && (allocations.count(pointer) > 0))
        {
            AllocationInfo& info = allocations[pointer];

            if (onDelete)
            {
                onDelete(pointer, info.size, info.file, info.line);
            }

            totalAllocated -= info.size;
            allocationCount--;
            allocations.erase(pointer);
        }
    }
    else
    {
        for (size_t i = 0; i < preInitIndex; ++i)
        {
            if (preInitAllocations[i].pointer == pointer)
            {
                preInitAllocations[i].pointer = nullptr;
            }
        }
    }
}

void MemoryTracker::getReport(std::map<void*, AllocationInfo, std::less<void*>, UntrackedAllocator<MapPair>>& resultAllocations)
{
	resultAllocations = allocations;
}

void MemoryTracker::reportLeaks()
{
    std::lock_guard<std::mutex> lock(mutex);
    std::cout << "\n--- Memory Leak Report ---\n";
    if (allocations.empty()) {
        std::cout << "No leaks detected. All allocated memory was successfully freed.\n";
    }
    else
    {
        std::cout << "LEAKS DETECTED! " << allocations.size() << " unfreed allocations:\n";
        /*
        size_t totalLeaked = 0;
        for (const auto& pair : allocations)
        {
            const AllocationInfo& info = pair.second;
            std::cout << "  - Leak of " << info.size << " bytes at "
                << info.file << ":" << info.line
                << " (Pointer: " << pair.first << ")\n";
            totalLeaked += info.size;
        }
        std::cout << "Total leaked: " << totalLeaked << " bytes.\n";
        */
    }

    std::cout << "Peak allocation (count): " << allocationCount << " active allocations.\n";
    std::cout << "Current total allocated: " << totalAllocated << " bytes.\n";
	std::cout << "-------------------------------------------\n";
}

} // namespace

ue::MemoryTracker& GetMemoryTracker()
{
    static ue::MemoryTracker instance;
    return instance;
}

void* operator new(size_t size, const char* file, int line)
{
    void* ptr = malloc(size);
    if (ptr)
    {
        GetMemoryTracker().trackAllocation(ptr, size, file, line);
    }
    else
    {
        throw std::bad_alloc();
    }

    return ptr;
}

void* operator new[](size_t size, const char* file, int line)
{
    void* ptr = malloc(size);
    if (ptr)
    {
        GetMemoryTracker().trackAllocation(ptr, size, file, line);
    }
    else
    {
        throw std::bad_alloc();
    }

    return ptr;
}

void* operator new(size_t size)
{
    void* ptr = malloc(size);
    if (ptr)
    {
        GetMemoryTracker().trackAllocation(ptr, size, "Unknown", 0);
    }
    else
    {
        throw std::bad_alloc();
    }
    return ptr;
}

void* operator new[](size_t size)
{
    void* ptr = malloc(size);

    if (ptr)
    {
        GetMemoryTracker().trackAllocation(ptr, size, "Unknown", 0);
    }
    else
    {
        throw std::bad_alloc();
    }

    return ptr;
}

void operator delete(void* ptr) noexcept
{
    GetMemoryTracker().trackDeallocation(ptr);
    free(ptr);
}

void operator delete[](void* ptr) noexcept
{
    GetMemoryTracker().trackDeallocation(ptr);
    free(ptr);
}

void operator delete(void* ptr, size_t size) noexcept
{
    GetMemoryTracker().trackDeallocation(ptr);
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept
{
    GetMemoryTracker().trackDeallocation(ptr);
    free(ptr);
}
