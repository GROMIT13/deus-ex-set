#pragma once

#include "raylib.h"
#include <limits.h>
#include <assert.h>

// TO DO: remake the ID system so it can't run out

class Entity
{
public:
	Vector2 pos;

	Entity(float x, float y);
	Entity(const Vector2& pos);
	Entity(const Entity& entity);
	inline long long getId() { return id; }
	virtual void Update() = 0;
private:
	long long id;
	static long long idCounter;

};

Entity::Entity(float x, float y)
	:pos({x,y})
{
	static long long idCounter = 0;

	if (idCounter == LLONG_MAX)
	{
		//LOG run out of id's
		assert(false && "no more id's");
	}

	id = idCounter;
	idCounter++;
}

Entity::Entity(const Vector2& pos)
	:Entity(pos.x, pos.y)
{}

Entity::Entity(const Entity& entity)
	:Entity(entity.pos)
{}
