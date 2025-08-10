#pragma once

#include "raylib.h"
#include "entity.hpp"
#include "window.hpp"
#include <cmath>

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
	};

	Player(const Vector2& pos, const Properties& playerProperties, const Properties& defaultPlayerProperties);
	//Player(const Player& player) = delete;
	void Update();

private:
	const Properties defaultProperties;
	Properties properties;
};

Player::Player(const Vector2& pos, const Properties& playerProperties, const Properties& defaultPlayerProperties)
	:Entity(pos,Object::Type::PLAYER), properties(playerProperties), defaultProperties(defaultPlayerProperties)
{}

void Player::Update()
{
	//TO DO: add instant turns (example: player moves left -> player preses right key [while pressing left key] -> player moves right [both keys pressed]) 
	float speed = IsKeyDown(KEY_LEFT_SHIFT) ? properties.speedSlow : properties.speed;

	//Set direction
	Vector2 dir = { 0,0 };
	if (IsKeyDown(KEY_LEFT))
		dir.x -= 1.0f;
	if (IsKeyDown(KEY_RIGHT))
		dir.x += 1.0f;
	if (IsKeyDown(KEY_UP))
		dir.y -= 1.0f;
	if (IsKeyDown(KEY_DOWN))
		dir.y += 1.0f;

	//Normalize speed
	if (fabs(dir.x) + fabs(dir.y) > 1.5f)
		speed /= 1.4142135f;

	//Move
	pos = pos + dir * speed;

	//Check for bounds
	/*if (pos.x < -60.0f)
		pos.x = -60.0f;
	if (pos.x >  60.0f)
		pos.x =  60.0f;
	if (pos.y < -80.0f)
		pos.y = -80.0f;
	if (pos.y >  80.0f)
		pos.y =  80.0f;*/

	if (pos.x < 0.0f)
		pos.x = 0.0f;
	if (pos.x > 12*60.0f - 30)
		pos.x = 12*60.0f - 30;
	if (pos.y < 0.0f)
		pos.y = 0.0f;
	if (pos.y > 12*80.0f - 30)
		pos.y = 12*80.0f - 30;

}
