#pragma once

#include "raylib.h"

class Scene;

class Sprite
{
public:
	Sprite(const char* file);
	Sprite(const char* file, TextureFilter filter, TextureWrap wrap);
	void Draw(const Vector2& pos, float rotation, Color color);
	void Draw(const Vector2& pos, float rotation, Color color, Scene* scene);
	~Sprite();

private:
	Texture2D texture2D;
	Rectangle sourceRect;
	Vector2 dimensions; //Dimensions specified in game units
};
