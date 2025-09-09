#include "bullet.hpp"
#include "vec.hpp"
#include "log.hpp"
#include "math.h"

void Bullet::Update()
{
	if (UpdateFunction)
	{
		UpdateFunction(this);
	}
	else
	{
		Log::Error("Bullet UpdateFunction was not initialized");
	}

}

void Bullet::PhysicsUpdate()
{
	velocity = velocity + acceleration;
	pos = pos + velocity;
	lifetime--;
}

void Bullet::PhysicsUpdateWithRotation()
{
	velocity = velocity + acceleration;
	pos = pos + velocity;
	rotation = atan2f(velocity.y * 10, velocity.x * 10) * 57.2958f;
	lifetime--;
}
