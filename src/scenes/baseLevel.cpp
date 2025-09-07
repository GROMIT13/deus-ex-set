#include "baseLevel.hpp"
#include "playerS.hpp"
#include "playerP.hpp"
#include "player.hpp"
#include "draw.hpp"
#include "vec.hpp"

LevelScene::LevelScene(const Space::Border& gameBorder, const Space::Border& screenBorder, PlayerType playerType)
	:Scene(gameBorder, screenBorder),
	enemyBM(ENEMY_BM_COUNT, this),
	playerBM(PLAYER_BM_COUNT, this)
{
	
	if (playerType == PlayerType::S)
	{
		Player::Properties properties = { false,2,3,0,0,0,1.2f,0.60f,1.0f,{11.5f + 18,10.0f + 24.0f}, SpriteName::SIGMA,270 };
		Vector2 pos = { 0.0f,60.0f };
	    player = std::make_unique<PlayerS>(pos, properties, properties, this);
		currentScene = CurrentScene::LEVEL1_S;
	}
	else if (playerType == PlayerType::P)
	{
		Player::Properties properties = { false,2,3,0,0,0,1.8f,0.75f,1.0f,{12.0f+18,12.0f+24.0f}, SpriteName::PI_SYMBOL,180 };
		Vector2 pos = { 0.0f,60.0f };
		player = std::make_unique<PlayerP>(pos, properties, properties, this);
		currentScene = CurrentScene::LEVEL1_P;
	}
	else
	{
		currentScene = CurrentScene::EXIT;
		Log::Error("Player of this type does not exist");
	}

	spriteManager.LoadAllSprites();

	Enemy::Properties eProp;
	eProp.hitboxRadius = 4.0f;
	eProp.spawnFrame = 60;
	eProp.attackCounter = 120;
	eProp.numOfAttacks = 10;
	eProp.health = 20.0f;
	eProp.rotation = 90;
	eProp.tempValA = 0.0f;
	eProp.tempValB = 0.0f;
	eProp.tempPosA = { 0.0f,0.0f };
	eProp.tempPosB = { 0.0f,0.0f };
	eProp.spriteName = SpriteName::DELTA;
	eProp.color = WHITE;

	enemies.emplace_back(Vector2{ 0.0f,0.0f }, this, eProp);
	enemies.emplace_back(Vector2{ 5.0f,0.0f }, this, eProp);
	enemies.emplace_back(Vector2{ 10.0f,0.0f }, this, eProp);
	enemies.emplace_back(Vector2{ 15.0f,0.0f }, this, eProp);

}

LevelScene::~LevelScene()
{
}

CurrentScene LevelScene::UpdateScene()
{

	////// UPDATE //////
	frameCounter++;
	player->Update();
	playerBM.Update();
	UpdateEnemies();

	//Quit Scene button
	if (IsKeyPressed(KEY_Q))
		currentScene = CurrentScene::MENU;

	////// DRAWING //////
	BeginDrawing();
	// BACKGROUND //
	ClearBackground(BLACK);

	// PLAYER/ENEMIES //
	player->DrawSprite();
	DrawEnemies();

	// BULLETS //
	playerBM.DrawBullets();

	// PLAYER HITBOX //
	player->DrawHitbox();

	// UI //
	DrawUI();

	// DEBUG //
	DrawHitboxes();

	////// END DRAWING //////
	EndDrawing();
	return currentScene;
}

void LevelScene::PlayerShootTheBullet(const Bullet& bullet)
{
	playerBM.InstantiateBullet(bullet);
}

void LevelScene::DrawHitboxes()
{
	playerBM.DrawHitboxes({ 0, 121, 241, 63 });
	DrawCircleV(player->pos, player->GetProperties().hitboxRadius, { 0, 228, 48, 191 }, this);
	for (const Enemy& enemy : enemies)
	{
		DrawCircleV(enemy.pos, enemy.GetProperties().hitboxRadius, { 135, 60, 190, 191 }, this);
	}
}

void LevelScene::DrawEnemies()
{
	for (const Enemy& enemy : enemies)
	{
		DrawSprite(enemy.GetProperties().spriteName, enemy.pos, enemy.GetProperties().rotation, enemy.GetProperties().color);
	}
}

void LevelScene::UpdateEnemies()
{
	for (std::vector<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end();)
	{
		//Check Health
		if (enemy->GetProperties().health <= 0.0f)
		{
			enemy = enemies.erase(enemy);
			continue;
		}
		//DealDamage
		if (playerBM.CollidesWithEnemy(*enemy))
		{
			//TO DO: Replace with player damage
			enemy->DealDamage(2);
		}

		enemy++;
	}
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

float LevelScene::AimAtPlayer(const Vector2& pos)
{
	return atan2f(pos.y - player->pos.y, pos.x - player->pos.x) * 57.29578f;
}

