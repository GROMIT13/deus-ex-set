#include "enemy.hpp"
#include "baseScene.hpp"

Enemy::Enemy(const Vector2& pos, LevelScene* scene, Properties properties)
	:Entity(pos, Object::Type::ENEMY, scene),properties(properties)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
}

Enemy::Properties Enemy::GetProperties() const
{
	return properties;
}

void Enemy::DealDamage(float damage)
{
	properties.health -= damage;
}
