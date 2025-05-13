#pragma once

#include <string>
#include <vector>

namespace sre
{

enum class EAssetType
{
    NONE,
    DIRECTORY,
    TEXTURE,
    MESH,
    MATERIAL,
    GUI,
    SCENE
};

namespace FileUtils
{
    void initializeStoragePaths();
    void loadContentFile(const std::string& filePath, std::string &dest); // throws "file can't be found"
    void loadConfigFile(const std::string& filePath, std::vector<std::string>& lines);
    void saveContentFile(const std::string& filePath, const std::string& content);
    void getFileAndIconPaths(std::string directoryPath, std::vector<std::string>& iconPaths, std::vector<std::string>& filePaths);
    std::string getFileName(const std::string& filePath);
    bool fileExists(const std::string& filePath);
	std::string getContentAbsolutePath(const std::string& filePath);
    std::string getConfigAbsolutePath(const std::string& filePath);
    std::string getContentRelativePath(const std::string& filePath);
	bool isDirectory(const std::string& filePath);
    bool isPathFromGameContent(const std::string& filePath);
	EAssetType getAssetType(const std::string& filePath);
}

} // namespace
