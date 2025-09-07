#pragma once

#include "bullet.hpp"

class Player;
class LevelScene;

class BulletManager
{
public:
	BulletManager(int bulletCount, LevelScene* scene);
	BulletManager(const BulletManager& bm) = delete;
	~BulletManager();
	void Update();
	void DrawBullets();
	void DrawHitboxes(Color color);
	void InstantiateBullet(const Bullet& bullet);
	bool CollidesWithPlayer(const Player& player);
	void DestroyAllBullets();

public:
	LevelScene* scene;
	Bullet* bulletList;
	int* activeBulletID;
	int activeBullets;
	int bulletCount;
	int bulletHead; //Head for deciding witch bullet from list to instantiate
};
