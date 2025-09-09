#pragma once

#include "baseScene.hpp"
#include "bulletManager.hpp"
#include "playerType.hpp"
#include "currentScene.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include <vector>
#include <memory>

#define ENEMY_BM_COUNT 10000
#define PLAYER_BM_COUNT 1000

class Player;
 
// Level Base Scene
class LevelScene : public Scene
{
public:
	LevelScene(const Space::Border& gameBorder, const Space::Border& screenBorder, PlayerType playerType);
	~LevelScene();
	CurrentScene UpdateScene();
	void PlayerShootTheBullet(const Bullet& bullet);
	void EnemyShootTheBullet(const Bullet& bullet);
	void DrawHitboxes();
	void DrawEnemies();
	void DrawScene();
	void UpdateEnemies();
	void DrawUI();
	float AimAtPlayer(const Vector2& pos);
	Vector2 VectorAtPlayer(const Vector2& pos);
	//Check if bullets/enemies collide
	bool CollidesWithPlayer();
	void DestroyAllEnemyBullets();
	bool IsLevelCompleted();
	void SpawnEnemies();
	void LoadEnemies();
private:
	std::unique_ptr<Player> player;
	std::vector<Enemy> enemies; //Enemies on screen
	std::vector<Enemy> enemyList; //list of all enemies on level that will be spawned
	BulletManager enemyBM;
	BulletManager playerBM;
	CurrentScene currentScene;
};
