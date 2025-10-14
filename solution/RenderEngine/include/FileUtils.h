#pragma once

#include <string>
#include <vector>

namespace sre
{

enum class EAssetType
{
    NONE,
    ENTITY,
    DIRECTORY,
    TEXTURE,
	HDR_TEXTURE,
    MESH,
    MATERIAL,
    GUI,
    SCENE,
    SOURCE_MODEL
};

namespace FileUtils
{
    void initializeStoragePaths();
    void loadContentFile(const std::string& filePath, std::string &dest); // throws "file can't be found"
    void loadConfigFile(const std::string& filePath, std::vector<std::string>& lines);
    void saveContentFile(const std::string& filePath, const std::string& content);
    void getFileAndIconPaths(std::string directoryPath, std::vector<std::string>& iconPaths, std::vector<std::string>& filePaths);
    std::string getFileName(const std::string& filePath);
	std::string getFileWithExtension(const std::string& filePath);
    bool fileExists(const std::string& filePath);
	std::string getContentAbsolutePath(const std::string& filePath);
    std::string getConfigAbsolutePath(const std::string& filePath);
    std::string getContentRelativePath(const std::string& filePath);
	std::string getToolsAbsolutePath(const std::string& fileName);
	std::string getBasePath(const std::string& filePath);
	bool isDirectory(const std::string& filePath);
    bool isPathFromGameContent(const std::string& filePath);
	EAssetType getAssetType(const std::string& filePath);
    std::string removeExtension(const std::string& filePath);
    std::string replaceExtension(const std::string& filePath, const std::string& extension);
	void deleteFile(const std::string& filePath);
    void duplicateFile(const std::string& filePath);
	void copyFile(const std::string& sourceFilePath, const std::string& destinationFilePath);
	void resolveFileNameConflict(std::string& filePath);
	void createDirectoryIfNotExists(const std::string& directoryPath);
}

} // namespace
