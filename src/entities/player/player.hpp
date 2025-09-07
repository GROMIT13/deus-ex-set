#pragma once

#include "raylib.h"
#include "entity.hpp"
#include "spriteManager.hpp"
#include "log.hpp"

class LevelScene;

class Player : public Entity
{
public:
	struct Properties
	{
		bool isInvincible;
		int lives;
		int bombs;
		int graze;
		long long score;
		long long hiScore;
		float speed;
		float speedSlow;
		float hitboxRadius;
		Vector2 dimensions; //defines dimensions for colision with bounds
		SpriteName spriteName;
		float spriteRotation;
	};

	Player(const Vector2& pos, const Properties& playerProperties, const Properties& defaultPlayerProperties, LevelScene* scene);
	Player(const Player& player);
	~Player() override;
	void Update() override;
	void DrawSprite();
	virtual void Shoot() { Log::Warn("DO NOT USE SHOOT METHOD ON BASE PLAYER CLASS"); }
	Properties GetProperties() const;
	Properties GetDefaultProperties() const;

private:
	const Properties defaultProperties;
	Properties properties;
};
