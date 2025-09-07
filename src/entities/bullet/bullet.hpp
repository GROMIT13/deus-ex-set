#pragma once

#include <functional>
#include "raylib.h"
#include "spriteManager.hpp"

struct Bullet
{
	bool isActive;
	bool canDamagePlayer;
	int lifetime;
	Vector2 pos;
	Vector2 velocity;
	Vector2 acceleration;
	float rotation;
	float hitboxRadius;
	void(*UpdateFunction)(Bullet*);
	SpriteName spriteName;
	Color color;
	//std::function<void(Bullet*)> UpdateFunction;

	void Update();

	//Update function with phisics
	//Adds set velocity and acceleration
	void PhysicsUpdate();

	void PhysicsUpdateWithRotation();
};
