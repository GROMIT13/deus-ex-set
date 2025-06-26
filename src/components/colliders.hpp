#pragma once 

#include "raylib.h"

class CircleCollider
{
public:
	float radius;
	Vector2 pos;
	CircleCollider(const Vector2& pos, float radius);
	~CircleCollider();
	bool Intersects(const CircleCollider& circleCollider);

private:

};

CircleCollider::CircleCollider(const Vector2& pos, float radius)
	:pos(pos), radius(radius)
{
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::Intersects(const CircleCollider& circleCollider)
{
	float r = radius + circleCollider.radius;
	Vector2 dPos = circleCollider.pos - pos;
	return r * r > dPos.x * dPos.x + dPos.y * dPos.y;
}
