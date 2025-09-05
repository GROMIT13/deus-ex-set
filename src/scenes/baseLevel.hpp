#pragma once

#include "baseScene.hpp"
#include "bulletManager.hpp"
#include "playerType.hpp"

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
	void DrawUI();
private:
	std::unique_ptr<Player> player;
	//std::vector<Entity> enemies;
	BulletManager enemyBM;
	BulletManager playerBM;
};
