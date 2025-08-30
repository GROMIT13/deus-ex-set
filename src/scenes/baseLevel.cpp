#include "baseLevel.hpp"

LevelScene::LevelScene(const Space::Border& gameBorder, const Space::Border& screenBorder, const Player& player)
	:Scene(gameBorder, screenBorder),
	player(player.pos, player.GetProperties(), player.GetDefaultProperties(), this),
	enemyBM(10000),
	playerBM(1000)
{
}

LevelScene::~LevelScene()
{
}

void LevelScene::UpdateScene()
{

	////// UPDATE //////
	frameCounter++;
	player.Update();

	////// DRAWING //////
	BeginDrawing();
	// BACKGROUND //
	ClearBackground(RAYWHITE);

	// PLAYER/ENEMIES //
	player.DrawSprite();

	// BULLETS //

	// PLAYER HITBOX //

	// UI //
	DrawFPS(0, 0);

	////// END DRAWING //////
	EndDrawing();

}

