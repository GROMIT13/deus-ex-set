#pragma once
#include "raylib.h"
#include "sprite.hpp"
#include <unordered_map>

class Scene;

enum class SpriteName
{
	TEST16 = 0,
	TEST32,
	TEST64,
	TEST128,
	TEST256,
};

class SpriteManager
{
public:
	SpriteManager();
	void LoadSprite(SpriteName spriteName);
	void UnloadSprite(SpriteName spriteName);
	void DrawSprite(SpriteName spriteName, const Vector2& pos, float rotation, Color color);
	void DrawSprite(SpriteName spriteName, const Vector2& pos, float rotation, Color color, Scene* scene);
	const char* GetSpriteFileName(SpriteName spriteName);
	~SpriteManager();

private:
	std::unordered_map<SpriteName, Sprite> sprites;
	std::unordered_map<SpriteName, const char*> spriteNames = {
		   {SpriteName::TEST16, "test16.png"},
		   {SpriteName::TEST32, "test32.png"},
		   {SpriteName::TEST64, "test64.png"},
		   {SpriteName::TEST128, "test128.png"},
		   {SpriteName::TEST256, "test256.png"}
	};
};
