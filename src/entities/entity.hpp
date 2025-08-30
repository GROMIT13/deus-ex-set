#pragma once

#include "raylib.h"
#include "object.hpp"

// TO DO: remake the ID system so it can't run out
class Entity : public Object
{
public:
	Vector2 pos;

	Entity(float x, float y, Object::Type ObjectType);
	Entity(const Vector2& pos, Object::Type ObjectType);
	Entity(const Entity& entity);
	inline long long getId() { return id; }
private:
	long long id;
	static long long idCounter;

};
