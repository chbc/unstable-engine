#include "FileUtils.h"

#include <fstream>
#include <filesystem>

namespace FS = std::filesystem;

FS::path contentPath;
FS::path gameContentPath;
FS::path configPath;
FS::path iconsPath;

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
	iconsPath = FS::absolute(bin / ".." / "content/engine/icons/");
}

void loadContentFile(const std::string& filePath, std::string& dest)
{
	std::string absolutePath = getContentAbsolutePath(filePath);
	std::ifstream in{ absolutePath };

	if (!in.is_open())
	{
		throw "[FileUtils] - Error: " + filePath + " can't be found!";
	}

	char temp[300];
	while (!in.eof())
	{
		in.getline(temp, 300);
		dest += temp;
		dest += '\n';
	}
}

void loadConfigFile(const std::string& filePath, std::vector<std::string>& lines)
{
	std::string absolutePath = getConfigAbsolutePath(filePath);
	std::ifstream in(absolutePath);

	if (!in.is_open())
	{
		throw "[FileUtils] - Error: " + filePath + " can't be found!";
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
			iconPath = iconsPath / iconName.append(".png");
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
	
	int stringPosition = filePath.find(pathToEvaluate);
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
		if (extension == ".png" || extension == ".jpg" || extension == ".jpeg")
		{
			result = EAssetType::TEXTURE;
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
	}

	return result;
}

#endif

} // namespace

} // namespace
