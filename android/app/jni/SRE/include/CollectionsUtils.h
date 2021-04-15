#ifndef _COLLECTIONS_UTILS_H_
#define _COLLECTIONS_UTILS_H_

#include <vector>
#include <unordered_map>

namespace sre
{

namespace CollectionsUtils
{

template <typename T>
void removeIfEntityIsDestroyed(std::vector<T*>& items)
{
    typename std::vector<T*>::iterator it;

    for (it = items.begin(); it != items.end();)
    {
        if (!(*it)->getEntity()->isAlive())
        {
            it = items.erase(it);
        }
        else
            ++it;
    }
}

template <typename T1, typename T2>
void removeIfEntityIsDestroyed(std::unordered_map<T1, T2>& items)
{
    typename std::unordered_map<T1, T2>::iterator it;

    for (it = items.begin(); it != items.end();)
    {
        if (!(*it).second->isAlive())
        {
            it = items.erase(it);
        }
        else
            ++it;
    }
}

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

} // namespace CollectionsUtils

} // namespace sre

#endif
