#pragma once

#include "bullet.hpp"

class Player;

class BulletManager
{
public:
	BulletManager(int bulletCount);
	BulletManager(const BulletManager& bm) = delete;
	~BulletManager();
	void Update();
	void DrawBullets();
	void InstantiateBullet(const Bullet& bullet);
	bool CollidesWithPlayer(const Player& player);
	void DestroyAllBullets();

public:
	Bullet* bulletList;
	int* activeBulletID;
	int activeBullets;
	int bulletCount;
	int bulletHead; //Head for deciding witch bullet from list to instantiate
};
