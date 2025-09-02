#pragma once
#include "raylib.h"
#include "sprite.hpp"
#include <unordered_map>

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

SpriteManager::SpriteManager()
{

}

void SpriteManager::LoadSprite(SpriteName spriteName)
{
	try
	{	
		auto hasBeenLoaded = sprites.try_emplace(spriteName, spriteNames.at(spriteName));

		if (!hasBeenLoaded.second)
			Log::Warn(TextFormat("sprite with texture %s is already loaded", spriteNames.at(spriteName)));
	}
	catch (const std::out_of_range)
	{
		Log::Error(TextFormat("file for SpriteName with number %i doesn't exist, initialize spriteName", spriteName));
	}
}

void SpriteManager::UnloadSprite(SpriteName spriteName)
{
	try
	{
		size_t erasedCount = sprites.erase(spriteName);
		if (erasedCount == 0)
			Log::Warn(TextFormat("sprite with texture %s wasn't loaded so it can't be unloaded", spriteNames.at(spriteName)));
	}
	catch (const std::out_of_range)
	{
		Log::Error(TextFormat("file for SpriteName with number %i does not exist, initialize spriteName", spriteName));
	}
}

SpriteManager::~SpriteManager()
{

}
