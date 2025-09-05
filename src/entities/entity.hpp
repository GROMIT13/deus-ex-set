#pragma once

#include "raylib.h"
#include "object.hpp"

class LevelScene;

// TO DO: remake the ID system so it can't run out
class Entity : public Object
{
public:
	Vector2 pos;

	Entity(float x, float y, Object::Type ObjectType, LevelScene* scene);
	Entity(const Vector2& pos, Object::Type ObjectType, LevelScene* scene);
	Entity(const Entity& entity);
	~Entity() override {}
	inline long long getId() { return id; }
	LevelScene* GetScene() const;
private:
	long long id;
	static long long idCounter;

protected:
	LevelScene* scene;
};
