#include "enemy.hpp"
#include "baseLevel.hpp"
#include "log.hpp"
#include "vec.hpp"
#include "bullet.hpp"

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

//Move by vector in one "second"
void Enemy::Move(const Vector2 vec2)
{
	pos = pos + (vec2 * (1.0f/60.0f));
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

void Enemy::InstantiateBullet()
{
	Bullet baseBullet;
	baseBullet.isActive = true;
	baseBullet.canDamagePlayer = true;
	baseBullet.lifetime = 100;
	baseBullet.pos = pos;
	baseBullet.velocity = { 0.0f,1.0f};
	baseBullet.acceleration = { 0.0f,0.0f };
	baseBullet.rotation = 0.0f;
	baseBullet.hitboxRadius = 1.0f;
	baseBullet.spriteName = SpriteName::TEST32;
	baseBullet.color = WHITE;
	baseBullet.UpdateFunction = [](Bullet* bullet) { bullet->PhysicsUpdate(); };
	scene->EnemyShootTheBullet(baseBullet);
}

