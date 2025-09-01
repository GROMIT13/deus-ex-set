#pragma once

#include "baseScene.hpp"
#include "bulletManager.hpp"
#include "player.hpp"

#define ENEMY_BM_COUNT 10000
#define PLAYER_BM_COUNT 1000

// Level Base Scene
class LevelScene : public Scene
{
public:
	LevelScene(const Space::Border& gameBorder, const Space::Border& screenBorder, const Player& player);
	~LevelScene();
	void UpdateScene();
private:
	Player player;
	//std::vector<Entity> enemies;
	BulletManager enemyBM;
	BulletManager playerBM;

};
