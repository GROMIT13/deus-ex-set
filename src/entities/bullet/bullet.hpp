#pragma once

#include <functional>
#include "vec.hpp"

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

	void Update()
	{
		if(UpdateFunction)
			UpdateFunction(this);
	}

	//Update function with phisics
	//Adds set velocity and acceleration
	void PhysicsUpdate()
	{
		velocity = velocity + acceleration;
		pos = pos + velocity;
	}
	
	void PhysicsUpdateWithRotation()
	{
		velocity = velocity + acceleration;
		pos = pos + velocity;
		rotation = atan2f(velocity.y*10, velocity.x*10) * 57.2958f;
	}

};

