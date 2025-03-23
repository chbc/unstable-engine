#include "FileUtils.h"

#include <fstream>
#include <filesystem>

namespace FS = std::filesystem;

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
void loadFile(const std::string& filePath, std::string& dest)
{
	std::ifstream in{ filePath };

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

void loadFile(const std::string& filePath, std::vector<std::string>& lines)
{
	std::ifstream in(filePath.c_str());

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

void saveFile(const std::string& filePath, const std::string& content)
{
	std::ofstream out{ filePath };

	if (!out.is_open())
	{
		throw "[FileUtils] - Error: " + filePath + " can't be found!";
	}

	out << content;
}

void getFileAndIconPaths(std::string directoryPath, std::vector<std::string>& iconPaths, std::vector<std::string>& filePaths)
{
	const char* ICONS_FOLDER = "../content/engine/icons/";

	for (const auto& item : std::filesystem::directory_iterator(directoryPath))
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
			iconPath = ICONS_FOLDER + iconName + ".png";
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
#endif

} // namespace

} // namespace
