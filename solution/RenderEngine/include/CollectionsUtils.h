#pragma once

#include <vector>
#include <unordered_map>

namespace sre
{

namespace CollectionsUtils
{

template <typename T>
void removeIfRendererIsEmpty(std::vector<T>& items)
{
    typename std::vector<T>::iterator it;

    for (it = items.begin(); it != items.end();)
    {
        if ((*it)->isEmpty())
        {
            it = items.erase(it);
        }
        else
            ++it;
    }
}

template <typename MapType>
void removeIfRendererIsEmpty(MapType& renderers)
{
    for (auto it = renderers.begin(); it != renderers.end(); )
    {
        if (it->second->isEmpty())
            it = renderers.erase(it);
        else
            ++it;
    }
}

} // namespace CollectionsUtils

} // namespace sre
