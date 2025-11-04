#pragma once

#include <string>

namespace sre
{

class InputTextHandler
{
private:
	std::string itemToRename;

public:
	bool isRenaming(const std::string& itemName) const;
	bool inputText(std::string& itemName);
	void setItemToRename(const std::string& itemName);
};

} // namespace
