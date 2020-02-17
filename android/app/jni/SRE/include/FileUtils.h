#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include <string>

namespace sre
{

namespace FileUtils
{
    void loadFile(const std::string &fileName, std::string &dest); // throws "file can't be found"
}

} // namespace
#endif
