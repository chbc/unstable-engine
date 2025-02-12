#ifndef _LOG_H_
#define _LOG_H_

#include <string>
#include "core_defines.h"

namespace sre
{

class SRE_API Log
{
public:
	static void LogMessage(const std::string& message);
	static void LogWarning(const std::string& message);
};

} // namespace

#endif
