#pragma once

#include <functional>

namespace sre
{
	using Action = std::function<void(void*)>;
}
