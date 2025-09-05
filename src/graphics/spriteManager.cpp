#include "spriteManager.hpp"
#include "log.hpp"
#include "baseScene.hpp"


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

void SpriteManager::LoadAllSprites()
{
	for (int i = 0; i < static_cast<int>(SpriteName::LAST); i++)
	{
		LoadSprite(static_cast<SpriteName>(i));
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

//NOTE: pos is in pixels
void SpriteManager::DrawSprite(SpriteName spriteName, const Vector2& pos, float rotation, Color color) const
{
	try
	{
		sprites.at(spriteName).Draw(pos, rotation, color);
	}
	catch (const std::out_of_range)
	{
		Log::Error(TextFormat("sprite with texture %s wasn't loaded so it can't be drawn", GetSpriteFileName(spriteName)));
	}
}

//NOTE: pos is in gameSpace units
void SpriteManager::DrawSprite(SpriteName spriteName, const Vector2& pos, float rotation, Color color, Scene* scene) const
{
	try
	{
		sprites.at(spriteName).Draw(pos, rotation, color, scene);
	}
	catch (const std::out_of_range)
	{
		Log::Error(TextFormat("sprite with texture %s wasn't loaded so it can't be drawn", GetSpriteFileName(spriteName)));
	}
}

const char* SpriteManager::GetSpriteFileName(SpriteName spriteName) const
{
	try
	{
		return spriteNames.at(spriteName);
	}
	catch (const std::exception&)
	{
		Log::Error(TextFormat("file for SpriteName with number %i does not exist, initialize spriteName", spriteName));
		return "NULL";
	}
}

SpriteManager::~SpriteManager()
{

}
