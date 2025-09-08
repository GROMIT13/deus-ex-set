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
	LoadEnemies();
}

LevelScene::~LevelScene()
{
}

CurrentScene LevelScene::UpdateScene()
{
	frameCounter++;

	//Quit Scene button
	if (IsKeyPressed(KEY_Q))
		currentScene = CurrentScene::MENU;

	if ((IsLevelCompleted() || player->IsDead()) && IsKeyPressed(KEY_Z))
	{
		return CurrentScene::MENU;
	}

	////// UPDATE //////
	if (!IsLevelCompleted() && !player->IsDead())
	{
		SpawnEnemies();
		player->Update();
		playerBM.Update();
		enemyBM.Update();
		UpdateEnemies();
	}

	////// DRAW //////
	DrawScene();

	return currentScene;
}

void LevelScene::PlayerShootTheBullet(const Bullet& bullet)
{
	playerBM.InstantiateBullet(bullet);
}

void LevelScene::EnemyShootTheBullet(const Bullet& bullet)
{
	enemyBM.InstantiateBullet(bullet);
}

void LevelScene::DrawHitboxes()
{
	//Bullet Hitbox
	playerBM.DrawHitboxes({ 0, 121, 241, 63 });
	enemyBM.DrawHitboxes({ 230, 41, 55, 127 });
	//Enemy Hitbox
	for (const Enemy& enemy : enemies)
	{
		DrawCircleV(enemy.pos, enemy.GetProperties().hitboxRadius, { 135, 60, 190, 191 }, this);
	}
	//Player Hitbox
	DrawCircleV(player->pos, player->GetProperties().hitboxRadius, { 0, 228, 48, 191 }, this);
}

void LevelScene::DrawEnemies()
{
	for (const Enemy& enemy : enemies)
	{
		DrawSprite(enemy.GetProperties().spriteName, enemy.pos, enemy.GetProperties().rotation, enemy.GetProperties().color);
	}
}

void LevelScene::DrawScene()
{
	////// DEATH SCREEN //////
	if (player->IsDead())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawSprite(SpriteName::GAME_OVER_TEXT, { 0.0f,-60.0f }, 0, WHITE);
		//TO DO: draw deathscreen
		EndDrawing();
		return;
	}

	if (IsLevelCompleted())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawSprite(SpriteName::STAGE_TEXT, { 0.0f,-60.0f }, 0, WHITE);
		DrawSprite(SpriteName::COMPLETED_TEXT, { 0.0f,-46.0f }, 0, WHITE);
		//TO DO: draw deathscreen
		EndDrawing();
		return;
	}

	////// LEVEL DRAWING //////
	BeginDrawing();

	// BACKGROUND //
	ClearBackground(BLACK);

	// PLAYER/ENEMIES //
	player->DrawSprite();
	DrawEnemies();

	// BULLETS //
	playerBM.DrawBullets();
	enemyBM.DrawBullets();

	// PLAYER HITBOX //
	player->DrawHitbox();

	// UI //
	DrawUI();

	// DEBUG //
	//DrawHitboxes();

	////// END DRAWING //////
	EndDrawing();
}

void LevelScene::UpdateEnemies()
{
	for (std::vector<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end();)
	{
		//Check Health
		if (enemy->GetProperties().health <= 0.0f || enemy->GetProperties().lifeTime <= 0)
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
		enemy->Update();
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
	return atan2f(player->pos.y - pos.y,player->pos.x - pos.x) * 57.29578f;
}

//Normalised vector directed at player
Vector2 LevelScene::VectorAtPlayer(const Vector2& pos)
{
	float angle = atan2f(player->pos.y - pos.y, player->pos.x - pos.x);
	return Vector2{ cosf(angle),sinf(angle) };
}

bool LevelScene::CollidesWithPlayer()
{
	return enemyBM.CollidesWithPlayer(*player);
}

void LevelScene::DestroyAllEnemyBullets()
{
	enemyBM.DestroyAllBullets();
}

bool LevelScene::IsLevelCompleted()
{
	if(player->IsDead())
		return false;

	if (frameCounter >= 60 * 29)
		return true;

	return false;

}

void LevelScene::SpawnEnemies()
{
	for (const Enemy& enemy : enemyList)
	{
		if (enemy.GetProperties().spawnFrame == frameCounter)
		{
			enemies.push_back(enemy);
		}
	}
}

void LevelScene::LoadEnemies()
{

	//Sum Enemy
	Enemy::Properties eProp1;
	eProp1.lifeTime = 360;
	eProp1.hitboxRadius = 4.0f;
	eProp1.spawnFrame = 60;
	eProp1.attackCounter = 0;
	eProp1.numOfAttacks = 10;
	eProp1.health = 140.0f;
	eProp1.rotation = 90;
	eProp1.tempValA = 0.0f;
	eProp1.tempValB = 0.0f;
	eProp1.tempPosA = { 0.0f,0.0f };
	eProp1.tempPosB = { 0.0f,0.0f };
	eProp1.spriteName = SpriteName::BIG_SUM;
	eProp1.color = WHITE;
	eProp1.ShootFunction = [](Enemy* enemy)
		{
			Bullet baseBullet;
			baseBullet.isActive = true;
			baseBullet.canDamagePlayer = true;
			baseBullet.lifetime = 60 * 8;
			baseBullet.pos = enemy->pos;
			baseBullet.velocity = enemy->VectorAtPlayer();
			baseBullet.acceleration = { 0.0f,0.0f };
			baseBullet.rotation = enemy->AimAtPlayer();
			baseBullet.hitboxRadius = 1.0f;
			baseBullet.spriteName = SpriteName::INCLUSION;
			baseBullet.color = WHITE;
			baseBullet.UpdateFunction = [](Bullet* bullet) { bullet->PhysicsUpdate(); };

			if (enemy->CanAttack(2))
			{
				enemy->properties.tempValA += 0.2;
				if(enemy->properties.tempValA >= 3)
					enemy->properties.tempValA = 0;
				Bullet instanceBullet = baseBullet;
				instanceBullet.velocity = instanceBullet.velocity + instanceBullet.velocity * enemy->properties.tempValA;

				enemy->InstantiateBullet(instanceBullet);
			}
		};
	eProp1.UpdateFunction = [](Enemy* enemy) { enemy->LookAtPlayer(0); enemy->Move(Vector2{ 0.0f,0.0f }); enemy->Shoot(); };


	//Delta Enemy
	Enemy::Properties eProp;
	eProp.lifeTime = 130;
	eProp.hitboxRadius = 4.0f;
	eProp.spawnFrame = 60;
	eProp.attackCounter = 0;
	eProp.numOfAttacks = 10;
	eProp.health = 10.0f;
	eProp.rotation = 90;
	eProp.tempValA = 0.0f;
	eProp.tempValB = 0.0f;
	eProp.tempPosA = { 0.0f,0.0f };
	eProp.tempPosB = { 0.0f,0.0f };
	eProp.spriteName = SpriteName::DELTA;
	eProp.color = WHITE;
	eProp.ShootFunction = [](Enemy* enemy)
		{
			Bullet baseBullet;
			baseBullet.isActive = true;
			baseBullet.canDamagePlayer = true;
			baseBullet.lifetime = 60*4;
			baseBullet.pos = enemy->pos;
			baseBullet.velocity = enemy->VectorAtPlayer();
			baseBullet.acceleration = { 0.0f,0.0f };
			baseBullet.rotation = enemy->AimAtPlayer();
			baseBullet.hitboxRadius = 1.0f;
			baseBullet.spriteName = SpriteName::HERMIT;
			baseBullet.color = WHITE;
			baseBullet.UpdateFunction = [](Bullet* bullet) { bullet->PhysicsUpdate(); };

			if (enemy->CanAttack(30))
				enemy->InstantiateBulletCircleWall(baseBullet,10);
		};
	eProp.UpdateFunction = [](Enemy* enemy) { enemy->LookAtPlayer(0); enemy->Move(Vector2{ 1.0f,0.0f }); enemy->Shoot(); };


	enemyList.emplace_back(Vector2{ -60.0f,-10.0f }, this, eProp);
	enemyList.emplace_back(Vector2{ -65.0f,-10.0f }, this, eProp);
	enemyList.emplace_back(Vector2{ -70.0f,-10.0f }, this, eProp);
	enemyList.emplace_back(Vector2{ -75.0f,-10.0f }, this, eProp);

	eProp.spawnFrame = 60 * 3;
	eProp.UpdateFunction = [](Enemy* enemy) { enemy->LookAtPlayer(0); enemy->Move(Vector2{ -1.0f,0.0f }); enemy->Shoot(); };

	enemyList.emplace_back(Vector2{ 60.0f,-10.0f }, this, eProp);
	enemyList.emplace_back(Vector2{ 65.0f,-10.0f }, this, eProp);
	enemyList.emplace_back(Vector2{ 70.0f,-10.0f }, this, eProp);
	enemyList.emplace_back(Vector2{ 75.0f,-10.0f }, this, eProp);

	eProp.spawnFrame = 60 * 5;

	enemyList.emplace_back(Vector2{ 60.0f,-10.0f }, this, eProp);
	enemyList.emplace_back(Vector2{ 65.0f,-10.0f }, this, eProp);
	enemyList.emplace_back(Vector2{ 70.0f,-10.0f }, this, eProp);
	enemyList.emplace_back(Vector2{ 75.0f,-10.0f }, this, eProp);

	eProp.UpdateFunction = [](Enemy* enemy) { enemy->LookAtPlayer(0); enemy->Move(Vector2{ 1.0f,0.0f }); enemy->Shoot(); };

	enemyList.emplace_back(Vector2{ -60.0f,-10.0f }, this, eProp);
	enemyList.emplace_back(Vector2{ -65.0f,-10.0f }, this, eProp);
	enemyList.emplace_back(Vector2{ -70.0f,-10.0f }, this, eProp);
	enemyList.emplace_back(Vector2{ -75.0f,-10.0f }, this, eProp);


	eProp1.spawnFrame = 60 * 7;
	eProp1.UpdateFunction = [](Enemy* enemy) { enemy->LookAtPlayer(0); enemy->Move(Vector2{ 0.0f,0.2f }); enemy->Shoot(); };
	enemyList.emplace_back(Vector2{   0.0f,-80.0f }, this, eProp1);

	eProp1.spawnFrame = 60 * 10;
	enemyList.emplace_back(Vector2{ 40.0f,-80.0f }, this, eProp1);
	enemyList.emplace_back(Vector2{ -40.0f,-80.0f }, this, eProp1);
	

	//For All Enemy
	Enemy::Properties eProp2;
	eProp2.lifeTime = 130;
	eProp2.hitboxRadius = 4.0f;
	eProp2.spawnFrame = 60;
	eProp2.attackCounter = 0;
	eProp2.numOfAttacks = 10;
	eProp2.health = 50.0f;
	eProp2.rotation = 90;
	eProp2.tempValA = 0.0f;
	eProp2.tempValB = 0.0f;
	eProp2.tempPosA = { 0.0f,0.0f };
	eProp2.tempPosB = { 0.0f,0.0f };
	eProp2.spriteName = SpriteName::FOR_ALL;
	eProp2.color = WHITE;
	eProp2.ShootFunction = [](Enemy* enemy)
		{
			Bullet baseBullet;
			baseBullet.isActive = true;
			baseBullet.canDamagePlayer = true;
			baseBullet.lifetime = 60 * 4;
			baseBullet.pos = enemy->pos;
			baseBullet.velocity = enemy->VectorAtPlayer();
			baseBullet.acceleration = { 0.0f,0.0f };
			baseBullet.rotation = enemy->AimAtPlayer();
			baseBullet.hitboxRadius = 1.0f;
			baseBullet.spriteName = SpriteName::AND;
			baseBullet.color = WHITE;
			baseBullet.UpdateFunction = [](Bullet* bullet) { bullet->PhysicsUpdate(); };

			if (enemy->CanAttack(2))
				enemy->InstantiateBulletCircle(baseBullet, 50);
		};
	eProp2.UpdateFunction = [](Enemy* enemy) { enemy->Move(Vector2{ 0.0f,0.0f }); enemy->Shoot(); };

	eProp2.spawnFrame = 60 *16;
	enemyList.emplace_back(Vector2{   0.0f,-60.0f }, this, eProp2);
	eProp2.spawnFrame = 60 *19;
	enemyList.emplace_back(Vector2{  40.0f,-60.0f }, this, eProp2);
	enemyList.emplace_back(Vector2{ -40.0f,-60.0f }, this, eProp2);
	eProp2.spawnFrame = 60 * 24;
	eProp2.lifeTime = 100;
	eProp2.ShootFunction = [](Enemy* enemy)
		{
			Bullet baseBullet;
			baseBullet.isActive = true;
			baseBullet.canDamagePlayer = true;
			baseBullet.lifetime = 60 * 4;
			baseBullet.pos = enemy->pos;
			baseBullet.velocity = enemy->VectorAtPlayer();
			baseBullet.acceleration = { 0.0f,0.0f };
			baseBullet.rotation = enemy->AimAtPlayer();
			baseBullet.hitboxRadius = 1.0f;
			baseBullet.spriteName = SpriteName::AND;
			baseBullet.color = WHITE;
			baseBullet.UpdateFunction = [](Bullet* bullet) { bullet->PhysicsUpdate(); };

			if (enemy->CanAttack(2))
				enemy->InstantiateBulletCircle(baseBullet, 30);
		};

	enemyList.emplace_back(Vector2{ 40.0f,-60.0f }, this, eProp2);
	enemyList.emplace_back(Vector2{ -40.0f,-60.0f }, this, eProp2);
	enemyList.emplace_back(Vector2{ -40.0f, 60.0f }, this, eProp2);
	enemyList.emplace_back(Vector2{  40.0f, 60.0f }, this, eProp2);

}

