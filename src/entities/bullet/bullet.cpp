#include "bullet.hpp"
#include "vec.hpp"

void Bullet::Update()
{
	if (UpdateFunction)
		UpdateFunction(this);
}

void Bullet::PhysicsUpdate()
{
	velocity = velocity + acceleration;
	pos = pos + velocity;
}

void Bullet::PhysicsUpdateWithRotation()
{
	velocity = velocity + acceleration;
	pos = pos + velocity;
	rotation = atan2f(velocity.y * 10, velocity.x * 10) * 57.2958f;
}
