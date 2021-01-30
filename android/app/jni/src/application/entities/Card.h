#pragma once

#include <Entity.h>
#include <string>
#include <glm/vec2.hpp>

namespace sre
{
	class GUIManager;
}

using namespace sre;

class Card
{
private:
	std::string entityName;
	int cardId;
	bool isRevealed;
	Entity* cover;

	const char* CARD_CHAR_PATH = "memoryGame/card_%d.png";
	const char* CARD_DESCRIPTION_PATH = "memoryGame/card_%d_description.png";
	
	const glm::vec2 CARD_EXTENT = glm::vec2(0.245f, 0.255f);
	const glm::vec2 CHAR_EXTENT = glm::vec2(0.2f, 0.2f);
	const glm::vec2 DESCRIPTION_EXTENT = glm::vec2(0.21f, 0.05f);

public:
	Card(GUIManager* guiManager, const glm::vec2& position, int arg_id, int entityId);

	void setRevealed(bool value);
	inline bool getIsRevealed() { return this->isRevealed; }
	const std::string& getEntityName();
	inline int getId() { return this->cardId; }
};
