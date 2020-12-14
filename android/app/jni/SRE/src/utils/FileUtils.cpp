#include "FileUtils.h"
#include <fstream>
#include <SDL.h>

namespace sre
{

namespace FileUtils
{

void loadFile(const std::string &fileName, std::string &dest)
{
	SDL_Log("XXX FileUtils | fileName = %s", fileName.c_str());

	SDL_RWops *file = SDL_RWFromFile(fileName.c_str(), "rb");
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

		SDL_Log("XXX FileUtils | total = %ld, size = %ld", nb_read_total, size);
		SDL_Log("%s",dest.c_str());

        if (nb_read_total != size)
		{
			free(res);
        }
	}
	else
	{
		SDL_Log("XXX FileUtils ERROR | %s", SDL_GetError());
	}

/* XXX
        SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
        if (rw == NULL) return NULL;

        Sint64 res_size = SDL_RWsize(rw);
        char* res = (char*)malloc(res_size + 1);

        Sint64 nb_read_total = 0, nb_read = 1;
        char* buf = res;
        while (nb_read_total < res_size && nb_read != 0) {
                nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
                nb_read_total += nb_read;
                buf += nb_read;
        }
        SDL_RWclose(rw);
        if (nb_read_total != res_size) {
                free(res);
                return NULL;
        }

        res[nb_read_total] = '\0';
*/
	/* XXX
	std::ifstream in(fileName.c_str());

	if (!in.is_open())
	{
		throw "[OpenGLAPI] - Error: " + fileName + " can't be found!";
	}

	char temp[300];
	while (!in.eof())
	{
		in.getline(temp, 300);
		dest += temp;
		dest += '\n';
	}
	*/
}

} // namespace

} // namespace
