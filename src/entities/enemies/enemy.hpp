#pragma once
#include "raylib.h"
#include "entity.hpp"
#include "spriteManager.hpp"

class LevelScene;
struct Bullet;

class Enemy : public Entity
{
public:
	struct Properties
	{
		int lifeTime;
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
		void (*UpdateFunction)(Enemy*);
		void (*ShootFunction)(Enemy*);
	};
	Enemy(const Vector2& pos, LevelScene* scene, Properties properties);
	~Enemy();
	void Update() override;
	Enemy::Properties GetProperties() const;
	void DealDamage(float damage);
	void LookAtPlayer(float angleoffset);
	void Move(const Vector2 vec2);
	void Shoot();
	void InstantiateBullet(const Bullet& bullet);
	void InstantiateBulletCircleWall(const Bullet& bullet, int count);
	void InstantiateBulletCircle(const Bullet& bullet, int count);
	bool CanAttack(int frames);
	Vector2 VectorAtPlayer();
	float AimAtPlayer();

	Properties properties;
private:
};
