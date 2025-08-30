#pragma once

#include "baseScene.hpp"
#include "bulletManager.hpp"
#include "player.hpp"

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
