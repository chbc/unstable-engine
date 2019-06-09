#pragma once

#include <string>

namespace sre
{

class Log
{
public:
	static void logMessage(const std::string &message);
	static void logWarning(const std::string &message);
};

} // namespace
