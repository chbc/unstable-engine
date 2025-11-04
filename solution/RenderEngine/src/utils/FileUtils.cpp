#include "FileUtils.h"

#include <fstream>
#include <filesystem>

namespace FS = std::filesystem;

FS::path contentPath;
FS::path gameContentPath;
FS::path configPath;
FS::path fileIconsPath;
FS::path toolsPath;

#ifdef __ANDROID__
	#include <SDL.h>
#endif

namespace sre
{

namespace FileUtils
{

#ifdef __ANDROID__
void loadFile(const std::string& filePath, std::string& dest)
{
	SDL_RWops* file = SDL_RWFromFile(filePath.c_str(), "rb");
	if (file != nullptr)
	{
		Sint64 size = SDL_RWsize(file);
		char* res = (char*)malloc(size + 1);

		Sint64 nb_read_total = 0, nb_read = 1;

		char* buf = res;
		while (nb_read_total < size && nb_read != 0)
		{
			nb_read = SDL_RWread(file, buf, 1, (size - nb_read_total));
			nb_read_total += nb_read;
			buf += nb_read;
		}

		SDL_RWclose(file);
		res[nb_read_total] = '\0';

		dest = std::string(res);

		if (nb_read_total != size)
		{
			free(res);
		}
	}
	else
	{
		SDL_Log("[FileUtils] ERROR | %s", SDL_GetError());
	}
}
#else
void initializeStoragePaths()
{
	FS::path bin = FS::current_path();
	contentPath = FS::absolute(bin / ".." / "content/");
	gameContentPath = FS::absolute(bin / ".." / "content/game/");
	configPath = FS::absolute(bin / ".." / "config/");
	fileIconsPath = FS::absolute(bin / ".." / "content/engine/icons/fileBrowser");
	toolsPath = FS::absolute(bin / ".." / "tools/");
}

void loadContentFile(const std::string& filePath, std::string& dest)
{
	std::string absolutePath = getContentAbsolutePath(filePath);
	std::ifstream in{ absolutePath };

	if (in.is_open())
	{
		char temp[300];
		while (!in.eof())
		{
			in.getline(temp, 300);
			dest += temp;
			dest += '\n';
		}
	}
	else
	{
		throw "[FileUtils] - Error: " + filePath + " can't be found!";
	}
}

void loadConfigFile(const std::string& filePath, std::vector<std::string>& lines)
{
	std::string absolutePath = getConfigAbsolutePath(filePath);
	std::ifstream in(absolutePath);

	if (!in.is_open())
	{
		throw "[FileUtils] - Error: " + absolutePath + " can't be found!";
	}

	char temp[300];
	while (!in.eof())
	{
		in.getline(temp, 300);
		lines.push_back(temp);
	}
}

void saveContentFile(const std::string& filePath, const std::string& content)
{
	std::string absolutePath = getContentAbsolutePath(filePath);
	std::ofstream out{ absolutePath };

	if (!out.is_open())
	{
		throw "[FileUtils] - Error: " + filePath + " can't be found!";
	}

	out << content;
}

void getFileAndIconPaths(std::string directoryPath, std::vector<std::string>& iconPaths, std::vector<std::string>& filePaths)
{
	for (const auto& item : FS::directory_iterator(directoryPath))
	{
		std::string iconName;
		const auto& extension = item.path().extension();
		bool hasIcon = true;
		FS::path iconPath;
		if (item.is_directory())
		{
			iconName = "folder_icon";
		}
		else if (extension == ".scene")
		{
			iconName = "scene_icon";
		}
		else if (extension == ".mesh")
		{
			iconName = "mesh_icon";
		}
		else if (extension == ".mat")
		{
			iconName = "material_icon";
		}
		else if (extension == ".ent")
		{
			iconName = "entity_icon";
		}
		else if ((extension == ".png") || (extension == "jpg") || (extension == "jpeg"))
		{
			iconPath = item.path();
			hasIcon = false;
		}
		else
		{
			iconName = "unknown_file_icon";
		}

		if (hasIcon)
		{
			iconPath = fileIconsPath / iconName.append(".png");
		}

		std::string resultPath = getContentRelativePath(iconPath.string());

		iconPaths.emplace_back(resultPath);
		filePaths.emplace_back(item.path().string());
	}
}

std::string getFileName(const std::string& filePath)
{
	FS::path systemPath{ filePath };
	return systemPath.stem().string();
}

std::string getFileWithExtension(const std::string& filePath)
{
	FS::path systemPath{ filePath };
	return systemPath.filename().string();
}

bool fileExists(const std::string& filePath)
{
	FS::path systemPath{ filePath };
	return FS::exists(systemPath);
}

std::string getContentAbsolutePath(const std::string& filePath)
{
	if (FS::path{ filePath }.is_absolute())
	{
		return filePath;
	}

	return (contentPath / filePath).string();
}

std::string getConfigAbsolutePath(const std::string& filePath)
{
	if (FS::path{ filePath }.is_absolute())
	{
		return filePath;
	}

	return (configPath / filePath).string();
}

std::string getContentRelativePath(const std::string& filePath)
{
	return FS::proximate(FS::path{ filePath }, contentPath).string();
}

std::string getToolsAbsolutePath(const std::string& fileName)
{
	return (toolsPath / fileName).string();
}

std::string getBasePath(const std::string& filePath)
{
	FS::path resultPath{ filePath };
	return resultPath.parent_path().string();
}

bool isDirectory(const std::string& filePath)
{
	return FS::is_directory(filePath);
}

bool isPathFromGameContent(const std::string& filePath)
{
	bool result = false;
	
	std::string pathToEvaluate = "game";

	if (FS::path{ filePath }.is_absolute())
	{
		pathToEvaluate = gameContentPath.string();
	}
	
	size_t stringPosition = filePath.find(pathToEvaluate);
	result = (stringPosition == 0) || (stringPosition == 1);

	return result;
}

EAssetType getAssetType(const std::string& filePath)
{
	EAssetType result = EAssetType::NONE;

	if (isDirectory(filePath))
	{
		result = EAssetType::DIRECTORY;
	}
	else
	{
		std::string extension = FS::path{ filePath }.extension().string();
		std::transform(extension.begin(), extension.end(), extension.begin(),
			[](unsigned char c) { return std::tolower(c); }
		);

		if (extension == ".ent")
		{
			result = EAssetType::ENTITY;
		}
		else if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
		{
			result = EAssetType::TEXTURE;
		}
		else if (extension == ".hdr")
		{
			result = EAssetType::HDR_TEXTURE;
		}
		else if (extension == ".mesh")
		{
			result = EAssetType::MESH;
		}
		else if (extension == ".mat")
		{
			result = EAssetType::MATERIAL;
		}
		else if (extension == ".gui")
		{
			result = EAssetType::GUI;
		}
		else if (extension == ".scene")
		{
			result = EAssetType::SCENE;
		}
		else if (extension == ".fbx" || extension == ".obj" || extension == ".dae" || extension == ".3ds" || extension == ".glTF")
		{
			result = EAssetType::SOURCE_MODEL;
		}
	}

	return result;
}

std::string removeExtension(const std::string& filePath)
{
	FS::path systemPath{ filePath };
	return systemPath.replace_extension().string();
}

std::string replaceExtension(const std::string& filePath, const std::string& extension)
{
	FS::path systemPath{ filePath };
	return systemPath.replace_extension(extension).string();
}

void deleteFile(const std::string& filePath)
{
	if (FS::is_directory(filePath))
	{
		FS::remove_all(FS::path{ filePath });
	}
	else
	{
		FS::remove(FS::path{ filePath });
	}
}

void duplicateFile(const std::string& filePath)
{
	std::string newFilePath = filePath;
	resolveFileNameConflict(newFilePath);
	copyFile(filePath, newFilePath);
}

void copyFile(const std::string& sourceFilePath, const std::string& destinationFilePath)
{
	std::string resultDestinationPath = getContentAbsolutePath(destinationFilePath);
	FS::copy_file(FS::path{ sourceFilePath }, FS::path{ resultDestinationPath }, FS::copy_options::overwrite_existing);
}

void renameFile(const std::string& oldFilePath, const std::string& newFileName)
{
	FS::path oldPath{ oldFilePath };
	FS::path directoryPath = oldPath.parent_path();
	FS::path extension = oldPath.extension();
	FS::path newPath = directoryPath / (newFileName + extension.string());
	std::string newFilePath = newPath.string();
	resolveFileNameConflict(newFilePath);
	FS::rename(FS::path{ oldFilePath }, FS::path{ newFilePath });
}

void resolveFileNameConflict(std::string& filePath)
{
	FS::path systemPath{ filePath };
	if (FS::exists(systemPath))
	{
		std::string baseName = systemPath.stem().string();
		std::string extension = systemPath.extension().string();
		FS::path parentPath = systemPath.parent_path();
		int counter = 1;
		do
		{
			std::string newFileName;
			newFileName = baseName + "_" + std::to_string(counter) + extension;
			systemPath = parentPath / newFileName;
			counter++;
		} while (FS::exists(systemPath));
		filePath = systemPath.string();
	}
}

void createDirectoryIfNotExists(const std::string& directoryPath)
{
	FS::path systemPath{ directoryPath };
	if (!FS::exists(systemPath))
	{
		FS::create_directories(systemPath);
	}
}

#endif

} // namespace

} // namespace
