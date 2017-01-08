#include "Log.h"

#include <iostream>

namespace sre
{

void Log::logMessage(const std::string &message)
{
	std::cout << "[MESSAGE]: " << message << std::endl;
}

void Log::logWarning(const std::string &message)
{
	std::cout << "[WARNING]: " << message << std::endl;
}

} // namespace
