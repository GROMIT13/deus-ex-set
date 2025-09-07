#pragma once
#include "raylib.h"
#include "entity.hpp"
#include "spriteManager.hpp"

class LevelScene;

class Enemy : public Entity
{
public:
	struct Properties
	{
		int spawnFrame;
		int attackCounter; //Time when enemy shoots
		int numOfAttacks; //How many times enemy attacks
		float hitboxRadius;
		float health;
		float rotation;
		float tempValA;
		float tempValB;
		Vector2 tempPosA;
		Vector2 tempPosB;
		SpriteName spriteName;
		Color color;
	};
	Enemy(const Vector2& pos, LevelScene* scene, Properties properties);
	~Enemy();
	void Update() override;
	Enemy::Properties GetProperties() const;
	void DealDamage(float damage);

private:
	Properties properties;
};
