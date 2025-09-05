#include "menu.hpp"
#include "vec.hpp"

MenuScene::MenuScene(const Space::Border& gameBorder, const Space::Border& screenBorder)
	:Scene(gameBorder,screenBorder)
{
	spriteManager.LoadAllSprites();
}

MenuScene::~MenuScene()
{
}

CurrentScene MenuScene::UpdateScene()
{

	//static int frame = 0;
	//frame++;

	/*if ((frame % 2) == 0)
	{
		menuSelection = MenuSelection::START;
	}
	else
	{
		menuSelection = MenuSelection::QUIT;
	}*/
	Select();
	//Draw//
	BeginDrawing();
	ClearBackground(BLACK);
	DrawSprite(SpriteName::TITLE_TEXT, { 0.0f,-60.0f }, 0, WHITE);
	DrawSprite(SpriteName::MENU_SELECT_TEXT, { 0.0f,-6.0f }, 0, WHITE);
	DrawSprite(SpriteName::PLAYER_SELECT_TEXT, { 0.0f,6.0f }, 0, WHITE);
	DrawMenuSelection({ -20.0f,-6.0f });
	DrawPlayerSelection({ -15.5f, 6.0f });
	EndDrawing();
	return currentScene;
}

void MenuScene::DrawMenuSelection(Vector2 pos)
{
	if (menuSelection == MenuSelection::START && !menuSelectionConfirmed)
	{
		DrawSprite(SpriteName::START_TEXT, pos, 0, RED);
		return;
	}

	if (menuSelection == MenuSelection::START && menuSelectionConfirmed)
	{
		DrawSprite(SpriteName::START_TEXT, pos, 0, GRAY);
		return;
	}

	if (menuSelection == MenuSelection::QUIT && !menuSelectionConfirmed)
	{
		Vector2 offset = { 0.2f, 0.6f };
		DrawSprite(SpriteName::QUIT_TEXT, pos + offset, 0, RED);
		return;
	}

	if (menuSelection == MenuSelection::QUIT && menuSelectionConfirmed)
	{
		Vector2 offset = { 0.2f, 0.6f };
		DrawSprite(SpriteName::QUIT_TEXT, pos + offset, 0, GRAY);
		return;
	}

}

void MenuScene::DrawPlayerSelection(Vector2 pos)
{
	if (playerSelection == PlayerSelection::P_PLAYER && menuSelectionConfirmed)
	{
		DrawSprite(SpriteName::PI_SMALL_SYMBOL, pos, 0, RED);
		return;
	}

	if (playerSelection == PlayerSelection::P_PLAYER && !menuSelectionConfirmed)
	{
		DrawSprite(SpriteName::PI_SMALL_SYMBOL, pos, 0, GRAY);
		return;
	}

	if (playerSelection == PlayerSelection::S_PLAYER && menuSelectionConfirmed)
	{
		DrawSprite(SpriteName::SIGMA_SMALL, pos, 0, RED);
		return;
	}

	if (playerSelection == PlayerSelection::S_PLAYER && !menuSelectionConfirmed)
	{
		DrawSprite(SpriteName::SIGMA_SMALL, pos, 0, GRAY);
		return;
	}
}

void MenuScene::Select()
{
	if (!menuSelectionConfirmed)
	{
		if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT))
		{
			if (menuSelection == MenuSelection::QUIT)
				menuSelection = MenuSelection::START;
			else if (menuSelection == MenuSelection::START)
				menuSelection = MenuScene::QUIT;
			return;

		}

		if (IsKeyPressed(KEY_Z) && menuSelection == MenuSelection::QUIT)
		{
			currentScene = CurrentScene::EXIT;
			return;
		}

		if (IsKeyPressed(KEY_Z) && menuSelection == MenuSelection::START)
		{
			menuSelectionConfirmed = true;
			return;
		}
	}

	if (menuSelectionConfirmed)
	{
		if (IsKeyPressed(KEY_X))
		{
			menuSelectionConfirmed = false;
			return;
		}

		if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT))
		{
			if (playerSelection == PlayerSelection::P_PLAYER)
				playerSelection = PlayerSelection::S_PLAYER;
			else if (playerSelection == PlayerSelection::S_PLAYER)
				playerSelection = PlayerSelection::P_PLAYER;
			return;
		}

		if (IsKeyPressed(KEY_Z) && playerSelection == PlayerSelection::P_PLAYER)
		{
			currentScene = CurrentScene::LEVEL1_P;
			return;
		}

		if (IsKeyPressed(KEY_Z) && playerSelection == PlayerSelection::S_PLAYER)
		{
			currentScene = CurrentScene::LEVEL1_S;
			return;
		}
	}
}
