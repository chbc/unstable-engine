#pragma once

#include "IScene.h"
#include "application/entities/Card.h"

#include <memory_aliases.h>

class GameScene : public IScene
{
private:
	VECTOR_UPTR<Card> cards;

	Card* currentSelectedCard;
	Card* previousSelectedCard;

	bool showingSelectedCards;
	int showingCadsTime;

	class Entity* endGameRestart;
	class Entity* endGameBack;

	const int MAX_SHOW_CARDS_TIME = 1500;

public:
	void onInit(SceneManager* sceneManager, GUIManager* guiManager) override;
	void onUpdate(unsigned int elapsedTime) override;
	void onButtonPress(GUIButtonComponent* guiButton, const std::string& entityName) override;

private:
	void setupCards(GUIManager* guiManager);
	void setupEndGameButtons(GUIManager* guiManager);
	void processSelectedCard(Card* card);
	void onCardsMatch();
};
