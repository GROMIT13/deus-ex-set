#include "playerS.hpp"
#include "log.hpp"
#include "baseLevel.hpp"
#include "vec.hpp"

PlayerS::PlayerS(const Vector2& pos, const Properties& playerProperties, const Properties& defaultPlayerProperties, LevelScene* scene)
	:Player(pos, playerProperties, defaultPlayerProperties, scene)
{
}

PlayerS::~PlayerS()
{
}

void PlayerS::Shoot()
{
	static int shoot = 3;
	shoot++;
	if (shoot >= 3)
		shoot = 3;

	if (IsKeyDown(KEY_Z) && shoot == 3)
	{
		shoot -= 3;

		Bullet leftBullet;
		leftBullet.isActive = true;
		leftBullet.canDamagePlayer = false;
		leftBullet.lifetime = 25;
		leftBullet.pos = pos + Vector2{ -3.5f, -2.5f };
		leftBullet.velocity = { -0.6f,-8.0f };
		leftBullet.acceleration = { 0.0f,0.0f };
		leftBullet.rotation = -25.0f;
		leftBullet.hitboxRadius = 3.0f;
		leftBullet.spriteName = SpriteName::INTEGRAL;
		leftBullet.UpdateFunction = [](Bullet* bullet) { bullet->PhysicsUpdate(); };
		leftBullet.color = { 255,255,255,127 };

		Bullet rightBullet;
		rightBullet.isActive = true;
		rightBullet.canDamagePlayer = false;
		rightBullet.lifetime = 25;
		rightBullet.pos = pos + Vector2{ 3.5f, -2.5f };
		rightBullet.velocity = { 0.6f,-8.0f };
		rightBullet.acceleration = { 0.0f,0.0f };
		rightBullet.rotation = 25.0f;
		rightBullet.hitboxRadius = 3.0f;
		rightBullet.spriteName = SpriteName::INTEGRAL_MIRROR;
		rightBullet.UpdateFunction = [](Bullet* bullet) { bullet->PhysicsUpdate(); };
		rightBullet.color = { 255,255,255,127 };

		if (IsKeyDown(KEY_LEFT_SHIFT))
		{
			rightBullet.velocity = rightBullet.velocity + Vector2{ -0.5f,0.0f };
			leftBullet.velocity = leftBullet.velocity + Vector2{ 0.5f,0.0f };
		}

		scene->PlayerShootTheBullet(rightBullet);
		scene->PlayerShootTheBullet(leftBullet);
		
	}
}
