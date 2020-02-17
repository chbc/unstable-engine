#include "FileUtils.h"
#include <fstream>

namespace sre
{

namespace FileUtils
{

void loadFile(const std::string &fileName, std::string &dest)
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
		dest += temp;
		dest += '\n';
	}
}

} // namespace

} // namespace
