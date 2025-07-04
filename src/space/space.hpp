#pragma once

#include "raylib.h"
#include "iostream"

class Space
{
public:
	struct Border
	{
		float left;
		float right;
		float top;
		float bottom;
	};

	Space(const Border& border)
		:border(border)
	{}
	// Convert from other space to this space
	inline Vector2 ToThisSpace(const Vector2& pos, const Space& space)
	{
		Vector2 newPos;
		newPos.x = (pos.x - space.border.left) / (space.border.right - space.border.left) * (border.right - border.left);
		newPos.y = (pos.y - space.border.bottom) / (space.border.top - space.border.bottom) * (border.top - border.bottom);
		return newPos;
	}

	Border border;
private:
};
