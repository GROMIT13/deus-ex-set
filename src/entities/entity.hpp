#pragma once

#include "raylib.h"
#include <limits.h>
#include <assert.h>
#include "log.hpp"
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

Entity::Entity(float x, float y, Object::Type ObjectType)
	:pos({x,y}), Object(ObjectType)
{
	static long long idCounter = 0;

	if (idCounter == LLONG_MAX)
	{
		Log::Error("no more entity id's");
		assert(false);
	}

	id = idCounter;
	idCounter++;
}

Entity::Entity(const Vector2& pos, Object::Type ObjectType)
	:Entity(pos.x, pos.y, ObjectType)
{}

Entity::Entity(const Entity& entity)
	:Entity(entity.pos,entity.GetType())
{}
