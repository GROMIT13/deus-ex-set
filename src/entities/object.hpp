#pragma once

class Object
{
public:
	enum class Type : char
	{
		EMPTY = 0, //Empty object
		PLAYER,
		ENEMY,
		BULLET,
		SPRITE,
		MANAGER
	};

	Object(Object::Type ObjectType) { type = ObjectType; }
	Type GetType() const { return type; }
	virtual void Update() = 0;


private:
	Type type;
};
