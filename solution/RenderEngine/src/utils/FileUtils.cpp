#include "FileUtils.h"

#include <fstream>
#include <filesystem>

namespace FS = std::filesystem;

std::string contentPath;
std::string configPath;
std::string iconsPath;

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
	FS::path content = bin / ".." / "content/";
	FS::path config = bin / ".." / "config/";
	FS::path icons = bin / ".." / "content/engine/icons/";

	contentPath = FS::absolute(content).string();
	configPath = FS::absolute(config).string();
	iconsPath = FS::absolute(icons).string();
}

void loadContentFile(const std::string& filePath, std::string& dest)
{
	std::string absolutePath = getAbsoluteContentPath(filePath);
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
	std::string absolutePath = getAbsoluteConfigPath(filePath);
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
	std::string absolutePath = getAbsoluteContentPath(filePath);
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
		std::string iconPath;
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
			iconPath = item.path().string();
			hasIcon = false;
		}
		else
		{
			iconName = "unknown_file_icon";
		}

		if (hasIcon)
		{
			iconPath = iconsPath + iconName + ".png";
		}

		iconPaths.emplace_back(iconPath);
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

std::string getAbsoluteContentPath(const std::string& filePath)
{
	if (FS::path{ filePath }.is_absolute())
	{
		return filePath;
	}

	return (contentPath + filePath);
}

std::string getAbsoluteConfigPath(const std::string& filePath)
{
	if (FS::path{ filePath }.is_absolute())
	{
		return filePath;
	}

	return (configPath + filePath);
}

bool isDirectory(const std::string& filePath)
{
	return FS::is_directory(filePath);
}

#endif

} // namespace

} // namespace
