#include "entity.hpp"
#include "log.hpp"
#include "baseLevel.hpp"
#include <limits.h>
#include <assert.h>

long long Entity::idCounter = 0;

Entity::Entity(float x, float y, Object::Type ObjectType, LevelScene* scene)
	:pos({ x,y }), Object(ObjectType), scene(scene)
{
	if (idCounter == LLONG_MAX)
	{
		Log::Error("no more entity id's");
		assert(false);
	}

	id = idCounter;
	idCounter++;
}

Entity::Entity(const Vector2& pos, Object::Type ObjectType, LevelScene* scene)
	:Entity(pos.x, pos.y, ObjectType, scene)
{
}

Entity::Entity(const Entity& entity)
	:Entity(entity.pos, entity.GetType(), entity.GetScene())
{
}

LevelScene* Entity::GetScene() const
{
	return scene;
}
