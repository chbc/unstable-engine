#include "Atlas.h"
#include <fstream>



#include <iostream>

namespace sre
{

Atlas::Atlas(Texture *texture)
{
	this->texture = texture;
}

const Rect *Atlas::getItem(char id)
{
	return this->uvs[id].get();
}

void Atlas::loadUVs(const std::string &fontFileName)
{
	std::string line;
	std::ifstream file(fontFileName);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			this->parse(line);
		}
		file.close();
	}
	else
		throw "Couldn't find file: " + fontFileName;
}

void Atlas::parse(const std::string &input)
{
	const std::string PATTERN("char id=");
	const std::string substr = input.substr(0, PATTERN.length());

	if (std::strcmp(substr.c_str(), PATTERN.c_str()) == 0)
	{
		char *context = nullptr;
		char *line = const_cast<char *>(input.c_str());

		/* ### ARRUMAR UM DELIMITADOR
		char *token = strtok_s(line, "\t", &context);

		while (token != nullptr)
		{
			token = strtok_s(nullptr, "\t", &context);
		}
		*/
	}
}

} // namespace

/*
char str[] ="- This, a sample string.";
char * pch;

pch = strtok (str," ,.-");

while (pch != NULL)
{
	printf ("%s\n",pch);
	pch = strtok (NULL, " ,.-");
}

*/
