#pragma once

#include <string>
#include <vector>

namespace sre
{

namespace FileUtils
{
    void loadFile(const std::string& filePath, std::string &dest); // throws "file can't be found"
    void loadFile(const std::string& filePath, std::vector<std::string>& lines);
    void saveFile(const std::string& filePath, const std::string& content);
    void getFileAndIconPaths(std::string directoryPath, std::vector<std::string>& iconPaths, std::vector<std::string>& filePaths);
    std::string getFileName(const std::string& filePath);
    bool fileExists(const std::string& filePath);
}

} // namespace
