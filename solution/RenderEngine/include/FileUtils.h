#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include <string>
#include <vector>

namespace sre
{

namespace FileUtils
{
    void loadFile(const std::string& fileName, std::string &dest); // throws "file can't be found"
    void loadFile(const std::string& fileName, std::vector<std::string>& lines);
    void saveFile(const std::string& fileName, const std::string& content);
    void getFilePaths(std::string directoryPath, std::vector<std::string>& iconPaths, std::vector<std::string>& filePaths);
    std::string getFileName(const std::string& filePath);
    bool fileExists(const std::string& filePath);
}

} // namespace
#endif
