#include "bulletManager.hpp"
#include "player.hpp"
#include "vec.hpp"


BulletManager::BulletManager(int bulletCount)
	:bulletCount(bulletCount), bulletHead(0), activeBullets(0)
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
	baseBullet.hitboxRadius = 0.0f;

	bulletList = new Bullet[bulletCount];
	activeBulletID = new int[bulletCount];
	for (int i = 0; i < bulletCount; i++)
		bulletList[i] = baseBullet;
}

BulletManager::~BulletManager()
{
	delete[] bulletList;
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

inline void BulletManager::DrawBullets()
{
	for (int i = 0; i < activeBullets; i++)
	{
		Rectangle rect1 = { bulletList[activeBulletID[i]].pos.x, bulletList[activeBulletID[i]].pos.y, 20.0f,20.0f };
		Rectangle rect2 = { bulletList[activeBulletID[i]].pos.x, bulletList[activeBulletID[i]].pos.y, 16.0f,16.0f };
		Vector2 origin1 = { rect1.width/2.0f, rect1.height / 2.0f };
		Vector2 origin2 = { rect2.width/2.0f, rect2.height / 2.0f };
		DrawRectanglePro(rect1, origin1, bulletList[activeBulletID[i]].rotation, DARKBLUE);
		DrawRectanglePro(rect2, origin2, bulletList[activeBulletID[i]].rotation, BLUE);
		//DrawCircle(bulletList[activeBulletID[i]].pos.x, bulletList[activeBulletID[i]].pos.y, 3, DARKPURPLE);
	}
}

inline void BulletManager::InstantiateBullet(const Bullet& bullet)
{
	bulletList[bulletHead] = bullet;
	bulletHead = (bulletHead + 1) % bulletCount;
}

inline bool BulletManager::CollidesWithPlayer(const Player& player)
{
	for (int i = 0; i < activeBullets; i++)
	{
		Vector2 funnyOffset = { 15.0, 15.0 };
		if (CheckCollisionCircles(player.pos + funnyOffset, 5.0f, bulletList[activeBulletID[i]].pos, bulletList[activeBulletID[i]].hitboxRadius))
			return true;
	}
	return false;
}

inline void BulletManager::DestroyAllBullets()
{
	for (int i = 0; i < activeBullets; i++)
	{
		bulletList[activeBulletID[i]].isActive = false;
	}
}
