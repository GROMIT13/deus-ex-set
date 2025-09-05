#pragma once 
#include "baseScene.hpp"
#include "currentScene.hpp"

class MenuScene : public Scene
{
public:
	enum MenuSelection
	{
		START,
		QUIT,
	};
	enum PlayerSelection
	{
		S_PLAYER,
		P_PLAYER,
	};

	MenuScene(const Space::Border& gameBorder, const Space::Border& screenBorder);
	~MenuScene();
	CurrentScene UpdateScene();
	void DrawMenuSelection(Vector2 pos);
	void DrawPlayerSelection(Vector2 pos);
	void Select();
private:
	MenuSelection menuSelection = MenuSelection::START;
	PlayerSelection playerSelection = PlayerSelection::S_PLAYER;
	bool menuSelectionConfirmed = false;
	CurrentScene currentScene = CurrentScene::MENU;
};
