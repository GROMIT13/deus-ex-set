#include "baseLevel.hpp"
#include "playerS.hpp"
#include "playerP.hpp"
#include "player.hpp"
#include "draw.hpp"
//#include "log.hpp"

LevelScene::LevelScene(const Space::Border& gameBorder, const Space::Border& screenBorder, PlayerType playerType)
	:Scene(gameBorder, screenBorder),
	enemyBM(ENEMY_BM_COUNT),
	playerBM(PLAYER_BM_COUNT)
{
	
	if (playerType == PlayerType::S)
	{
		Player::Properties properties = { false,2,3,0,0,0,1.7f,0.75f,3.0f,{11.5f + 18,10.0f + 24.0f}, SpriteName::SIGMA,270 };
		Vector2 pos = { 0.0f,60.0f };
	    player = std::make_unique<PlayerS>(pos, properties, properties, this);
	}
	else if (playerType == PlayerType::P)
	{
		Player::Properties properties = { false,2,3,0,0,0,1.7f,0.75f,3.0f,{12.0f+18,12.0f+24.0f}, SpriteName::PI_SYMBOL,180 };
		Vector2 pos = { 0.0f,60.0f };
		player = std::make_unique<PlayerS>(pos, properties, properties, this);
	}
	else
	{
		Log::Error("Player of this type does not exist");
	}

	spriteManager.LoadAllSprites();
}

LevelScene::~LevelScene()
{
}

CurrentScene LevelScene::UpdateScene()
{

	////// UPDATE //////
	frameCounter++;
	player->Update();

	////// DRAWING //////
	BeginDrawing();
	// BACKGROUND //
	ClearBackground(BLACK);

	// PLAYER/ENEMIES //
	player->DrawSprite();

	// BULLETS //

	// PLAYER HITBOX //

	// UI //
	DrawUI();

	////// END DRAWING //////
	EndDrawing();
	return CurrentScene::LEVEL1_S;
}

void LevelScene::DrawUI()
{
	//Draw Frame
	DrawRectangleV({ -60.0f, 68.0f }, { 120.0f,12.0f }, BLACK, this); //border bottom
	DrawRectangleV({ -60.0f, -80.0f }, { 120.0f,12.0f }, BLACK, this); //border top
	DrawRectangleV({ -60.0f, -80.0f + 11 }, { 9.0f,138.0f }, DARKPURPLE, this); //border left
	DrawRectangleV({ 51.0f, -80.0f  + 11}, { 9.0f,138.0f }, DARKPURPLE, this); //border reigt
	
	DrawRectangleV({ -60.0f, 68.0f }, { 120.0f,1.0f }, WHITE, this); //line bottom
	DrawRectangleV({ -60.0f, -80.0f+11 }, { 120.0f,1.0f }, WHITE, this);  //line top
	DrawRectangleV({ -60.0f + 8, -80.0f + 11 }, { 1.0f,138.0f }, WHITE, this); //line left
	DrawRectangleV({ 51.0f, -80.0f + 11 }, { 1.0f,138.0f }, WHITE, this); //line reigt

	//Draw health
	DrawSprite(SpriteName::ALEPH_BIG, { -55.0f ,74.0f }, 0, WHITE);
	DrawSprite(static_cast<SpriteName>(player->GetProperties().lives + static_cast<int>(SpriteName::UNDERSCORE_0)), { -50.0f,77.0f }, 0, WHITE);
	DrawFPS(0, 0);
}

