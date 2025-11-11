#include "MemoryTracker.h"

namespace ue
{

MemoryTracker& MemoryTracker::getInstance()
{
	static MemoryTracker instance;
	return instance;
}

void MemoryTracker::trackAllocation(void* pointer, size_t size, const char* file, int line)
{
    std::lock_guard<std::mutex> lock(mutex);

    if (pointer)
    {
        totalAllocated += size;
        allocationCount++;

        allocations[pointer] = { size, file, line };

        /*
        std::cout << "Alocado: " << size << " bytes em "
                  << file << ":" << line << " (Ponteiro: " << ptr << ")\n";
                  */

		this->onNew(pointer, size, file, line);
    }
}

void MemoryTracker::trackDeallocation(void* pointer)
{
    std::lock_guard<std::mutex> lock(mutex);

    if (pointer)
    {
        auto it = allocations.find(pointer);
        if (it != allocations.end())
        {
            AllocationInfo info = it->second;

			this->onDelete(pointer, info.size, info.file, info.line);

            totalAllocated -= info.size;
            allocationCount--;
            allocations.erase(it);
        }
    }
}

void MemoryTracker::getReport(std::map<void*, AllocationInfo>& resultAllocations) const
{
	resultAllocations = allocations;
}

/*
void MemoryTracker::reportLeaks()
{
    std::lock_guard<std::mutex> lock(mutex);

    std::cout << "\n--- Relatório de Vazamento de Memória ---\n";
    if (allocations.empty()) {
        std::cout << "Nenhum vazamento detectado. Memória total alocada e liberada com sucesso.\n";
    }
    else
    {
        std::cout << "VAZAMENTOS DETECTADOS! " << allocations.size() << " alocações não liberadas:\n";
        size_t totalLeaked = 0;
        for (const auto& pair : allocations)
        {
            const AllocationInfo& info = pair.second;
            std::cout << "  - Vazamento de " << info.size << " bytes em "
                << info.file << ":" << info.line
                << " (Ponteiro: " << pair.first << ")\n";
            totalLeaked += info.size;
        }
        std::cout << "Total vazado: " << totalLeaked << " bytes.\n";
    }
    std::cout << "Pico de alocação (contagem): " << allocationCount << " alocações ativas.\n";
    std::cout << "Total atual alocado: " << totalAllocated << " bytes.\n";
    std::cout << "-------------------------------------------\n";
}
*/

} // namespace

void* operator new(size_t size, const char* file, int line)
{
    void* ptr = malloc(size);
    if (ptr)
    {
        ue::MemoryTracker::getInstance().trackAllocation(ptr, size, file, line);
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
        ue::MemoryTracker::getInstance().trackAllocation(ptr, size, file, line);
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
        ue::MemoryTracker::getInstance().trackAllocation(ptr, size, "Unknown", 0);
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
        ue::MemoryTracker::getInstance().trackAllocation(ptr, size, "Unknown", 0);
    }
    else
    {
        throw std::bad_alloc();
    }

    return ptr;
}

void operator delete(void* ptr) noexcept
{
    ue::MemoryTracker::getInstance().trackDeallocation(ptr);
    free(ptr);
}

void operator delete[](void* ptr) noexcept
{
    ue::MemoryTracker::getInstance().trackDeallocation(ptr);
    free(ptr);
}

void operator delete(void* ptr, size_t size) noexcept
{
    ue::MemoryTracker::getInstance().trackDeallocation(ptr);
    free(ptr);
}

void operator delete[](void* ptr, size_t size) noexcept
{
    ue::MemoryTracker::getInstance().trackDeallocation(ptr);
    free(ptr);
}
