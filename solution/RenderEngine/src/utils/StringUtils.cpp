#include "StringUtils.h"

namespace sre
{

namespace StringUtils
{

bool splitStringInt(const std::string& input, std::string& resultString, int& resultInt)
{
	int i = static_cast<int>(input.length()) - 1;

	while (i >= 0 && std::isdigit(static_cast<unsigned char>(input[i])))
	{
		i--;
	}

	resultString = input.substr(0, i + 1);
	std::string numericPart = input.substr(i + 1);

	if (numericPart.empty())
	{
		resultInt = 0;
	}
	else
	{
		try
		{
			resultInt = std::stoi(numericPart);
		}
		catch (...)
		{
			resultInt = 0;
		}
	}

	return (resultInt != 0);
}

} // namespace StringUtils

} // namespace sre
