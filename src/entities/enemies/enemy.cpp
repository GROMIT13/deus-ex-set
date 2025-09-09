#include "enemy.hpp"
#include "baseLevel.hpp"
#include "log.hpp"
#include "vec.hpp"
#include "bullet.hpp"
#include "math.h"

Enemy::Enemy(const Vector2& pos, LevelScene* scene, Properties properties)
	:Entity(pos, Object::Type::ENEMY, scene),properties(properties)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (properties.UpdateFunction)
	{
		properties.UpdateFunction(this);
		properties.lifeTime--;
	}
	else
	{
		Log::Error("enemy Updatefunction is not initialized");
	}
}

Enemy::Properties Enemy::GetProperties() const
{
	return properties;
}

void Enemy::DealDamage(float damage)
{
	properties.health -= damage;
}

void Enemy::LookAtPlayer(float angleoffset)
{
	properties.rotation = scene->AimAtPlayer(pos) + angleoffset;
}

void Enemy::Move(const Vector2 vec2)
{
	pos = pos + vec2;
}

void Enemy::Shoot()
{
	if (properties.ShootFunction)
	{
		properties.ShootFunction(this);
	}
	else
	{
		Log::Error("enemy ShootFunction is not initialized");
	}

}

void Enemy::InstantiateBullet(const Bullet& bullet)
{
	scene->EnemyShootTheBullet(bullet);
}

void Enemy::InstantiateBulletCircleWall(const Bullet& bullet, int count)
{
	float vecLength = sqrt(bullet.velocity.x * bullet.velocity.x + bullet.velocity.y * bullet.velocity.y);
	float phi = atan2(bullet.velocity.y, bullet.velocity.x);
	float theta = 2.0f * PI;
	Bullet bulletInstance = bullet;

	for (int i = 0; i < count; i++)
	{
		bulletInstance.velocity = vecLength * Vector2{ cosf((phi + float(theta * i)) / ((float)count)),sinf((phi + float(theta * i)) / ((float)count)) };
		InstantiateBullet(bulletInstance);
	}
}

void Enemy::InstantiateBulletCircle(const Bullet& bullet, int count)
{
	Bullet bulletInstance = bullet;
	for (int i = 0; i < count; i++)
	{
		bulletInstance.velocity = { cosf(((float)(i)) * 2.0f * PI / ((float)(count))), sinf(((float)(i)) * 2.0f * PI / ((float)(count))) };
		bulletInstance.rotation = (((float)(i)) * 2.0f * PI / ((float)(count))) * 57.2958f;
		InstantiateBullet(bulletInstance);
	}
}

bool Enemy::CanAttack(int frames)
{
	if (frames <= properties.attackCounter)
	{
		properties.attackCounter = 0;
		return true;
	}
	else
	{
		properties.attackCounter++;
		return false;
	}
}

Vector2 Enemy::VectorAtPlayer()
{
	return scene->VectorAtPlayer(pos);
}

float Enemy::AimAtPlayer()
{
	return scene->AimAtPlayer(pos);
}

