#pragma once

#include "baseScene.hpp"
#include "bulletManager.hpp"
#include "playerType.hpp"
#include "currentScene.hpp"
#include "bullet.hpp"
#include "enemy.hpp"


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
	void DrawHitboxes();
	void DrawEnemies();
	void UpdateEnemies();
	void DrawUI();
	float AimAtPlayer(const Vector2& pos);
private:
	std::unique_ptr<Player> player;
	std::vector<Enemy> enemies;
	BulletManager enemyBM;
	BulletManager playerBM;
	CurrentScene currentScene;
};
