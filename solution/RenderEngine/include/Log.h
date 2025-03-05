#pragma once

#include <string>
#include "core_defines.h"

namespace sre
{

class SRE_API Log
{
public:
	static void LogMessage(const std::string& message);
	static void LogWarning(const std::string& message);
	static void showMessageBox(const std::string& title, const std::string& message);
	static void showErrorMessageBox(const std::string& title, const std::string& message);
};

} // namespace
