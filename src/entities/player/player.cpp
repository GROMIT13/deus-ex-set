#include "player.hpp"
#include "vec.hpp"
#include "baseLevel.hpp"
#include "window.hpp"
#include "draw.hpp"
#include "log.hpp"
#include <cmath>

// NOTE: if player does not belong to scene set Scene* to nullptr
Player::Player(const Vector2& pos, const Properties& playerProperties, const Properties& defaultPlayerProperties, LevelScene* scene)
	:Entity(pos, Object::Type::PLAYER, scene), properties(playerProperties), defaultProperties(defaultPlayerProperties)
{
}

Player::Player(const Player& player)
	:Player(player.pos, player.properties, player.defaultProperties, player.scene)
{
}

Player::~Player()
{
}

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
	if (pos.x < scene->GetGameSpace().border.left + defaultProperties.dimensions.x / 2.0f)
		pos.x = scene->GetGameSpace().border.left + defaultProperties.dimensions.x / 2.0f;
	if (pos.x > scene->GetGameSpace().border.right - defaultProperties.dimensions.x / 2.0f)
		pos.x = scene->GetGameSpace().border.right - defaultProperties.dimensions.x / 2.0f;
	if (pos.y < scene->GetGameSpace().border.bottom + defaultProperties.dimensions.y / 2.0f)
		pos.y = scene->GetGameSpace().border.bottom + defaultProperties.dimensions.y / 2.0f;
	if (pos.y > scene->GetGameSpace().border.top - defaultProperties.dimensions.y / 2.0f)
		pos.y = scene->GetGameSpace().border.top - defaultProperties.dimensions.y / 2.0f;

	Shoot();

	if (scene->CollidesWithPlayer())
	{
		scene->DestroyAllEnemyBullets();
		RemoveLife();
	}
}

void Player::DrawSprite()
{
	scene->DrawSprite(properties.spriteName, pos, properties.spriteRotation, LIGHTGRAY);
}

void Player::DrawHitbox()
{
	scene->DrawSprite(SpriteName::ALEPH, pos, 0, RED);
}

Player::Properties Player::GetProperties() const
{
	return properties;
}

Player::Properties Player::GetDefaultProperties() const 
{
	return defaultProperties;
}

void Player::AddLife()
{
	if (properties.lives <= 9)
		properties.lives++;
}

void Player::RemoveLife()
{
	if(properties.lives > 0)
		properties.lives--;
}

bool Player::IsDead()
{
	return properties.lives <= 0 ? true : false;
}
