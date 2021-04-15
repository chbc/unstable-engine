#include "Log.h"
#include "SingletonsManager.h"
#include "MultimediaManager.h"

namespace sre
{

void Log::LogMessage(const std::string& message)
{
	SingletonsManager::getInstance()->get<MultimediaManager>()->logMessage(message);
}

void Log::LogWarning(const std::string& message)
{
	SingletonsManager::getInstance()->get<MultimediaManager>()->logWarning(message);
}

} // namespace
