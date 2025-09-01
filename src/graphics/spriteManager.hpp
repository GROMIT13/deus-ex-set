#pragma once

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
	~SpriteManager();

private:
	static char textureNames[] = { "test16.png",test32.png,test64.png,test128.png,test256.png };
};

SpriteManager::SpriteManager()
{
}

void SpriteManager::LoadSprite(SpriteName spriteName)
{
}

SpriteManager::~SpriteManager()
{
}