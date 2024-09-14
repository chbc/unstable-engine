#include "FileUtils.h"
#include <fstream>

#ifdef __ANDROID__
	#include <SDL.h>
#endif

namespace sre
{

namespace FileUtils
{

#ifdef __ANDROID__
void loadFile(const std::string& fileName, std::string& dest)
{
	SDL_RWops* file = SDL_RWFromFile(fileName.c_str(), "rb");
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
		SDL_Log("XXX FileUtils ERROR | %s", SDL_GetError());
	}
}
#else
void loadFile(const std::string& fileName, std::string& dest)
{
	std::ifstream in{ fileName };

	if (!in.is_open())
	{
		throw "[FileUtils] - Error: " + fileName + " can't be found!";
	}

	char temp[300];
	while (!in.eof())
	{
		in.getline(temp, 300);
		dest += temp;
		dest += '\n';
	}
}

void loadFile(const std::string& fileName, std::vector<std::string>& lines)
{
	std::ifstream in(fileName.c_str());

	if (!in.is_open())
	{
		throw "[OpenGLAPI] - Error: " + fileName + " can't be found!";
	}

	char temp[300];
	while (!in.eof())
	{
		in.getline(temp, 300);
		lines.push_back(temp);
	}
}

void saveFile(const std::string& fileName, const std::string& content)
{
	std::ofstream out{ fileName };

	if (!out.is_open())
	{
		throw "[FileUtils] - Error: " + fileName + " can't be found!";
	}

	out << content;
}
#endif

} // namespace

} // namespace
