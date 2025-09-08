#include "bulletManager.hpp"
#include "baseLevel.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "draw.hpp"
#include "vec.hpp"


BulletManager::BulletManager(int bulletCount, LevelScene* scene)
	:bulletCount(bulletCount), bulletHead(0), activeBullets(0), scene(scene)
{
	Bullet baseBullet;
	baseBullet.isActive = false;
	baseBullet.canDamagePlayer = false;
	baseBullet.lifetime = 0;
	baseBullet.pos = { 0.0f,0.0f };
	baseBullet.velocity = { 0.0f,0.0f };
	baseBullet.acceleration = { 0.0f,0.0f };
	baseBullet.rotation = 0.0f;
	baseBullet.hitboxRadius = 0.0f;
	baseBullet.spriteName = SpriteName::TEST32;
	baseBullet.color = WHITE;
	baseBullet.UpdateFunction = nullptr;

	bulletList = new Bullet[bulletCount];
	activeBulletID = new int[bulletCount];
	for (int i = 0; i < bulletCount; i++)
		bulletList[i] = baseBullet;
}

BulletManager::~BulletManager()
{
	delete[] bulletList;
	delete[] activeBulletID;
}

void BulletManager::Update()
{
	// Gather active bullets
	activeBullets = 0;
	for (int i = 0; i < bulletCount; i++)
	{
		if (!bulletList[i].isActive)
			continue;

		activeBulletID[activeBullets] = i;
		activeBullets++;

		if (bulletList[i].lifetime <= 0)
		{
			bulletList[i].isActive = false;
			activeBullets--;
		}
	}
	
	//Update active bullets
	for (int i = 0; i < activeBullets; i++)
	{
		bulletList[activeBulletID[i]].Update();
	}
}

void BulletManager::DrawBullets()
{
	for (int i = 0; i < activeBullets; i++)
	{
		scene->DrawSprite(bulletList[activeBulletID[i]].spriteName, bulletList[activeBulletID[i]].pos, bulletList[activeBulletID[i]].rotation, bulletList[activeBulletID[i]].color);
	}
}

void BulletManager::DrawHitboxes(Color color)
{
	for (int i = 0; i < activeBullets; i++)
	{
		DrawCircleV(bulletList[activeBulletID[i]].pos, bulletList[activeBulletID[i]].hitboxRadius, color, scene);
	}
}

void BulletManager::InstantiateBullet(const Bullet& bullet)
{
	bulletList[bulletHead] = bullet;
	bulletHead = (bulletHead + 1) % bulletCount;
}

bool BulletManager::CollidesWithPlayer(const Player& player)
{
	for (int i = 0; i < activeBullets; i++)
	{
		if (CheckCollisionCircles(player.pos, player.GetProperties().hitboxRadius, bulletList[activeBulletID[i]].pos, bulletList[activeBulletID[i]].hitboxRadius))
			return true;
	}
	return false;
}

bool BulletManager::CollidesWithEnemy(const Enemy& enemy)
{
	for (int i = 0; i < activeBullets; i++)
	{
		if (CheckCollisionCircles(enemy.pos, enemy.GetProperties().hitboxRadius, bulletList[activeBulletID[i]].pos, bulletList[activeBulletID[i]].hitboxRadius))
			return true;
	}
	return false;
}

void BulletManager::DestroyAllBullets()
{
	for (int i = 0; i < activeBullets; i++)
	{
		bulletList[activeBulletID[i]].isActive = false;
	}
}
