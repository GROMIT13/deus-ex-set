#pragma once

#include "raylib.h"

class Sprite
{
public:
	Sprite(const Texture2D& texture2D, const Vector2& dimensions);
	void Draw();
	~Sprite();

private:
	Texture2D texture2D;
	Rectangle sourceRect;
	Vector2 dimensions; //Dimensions specified in game units
};

Sprite::Sprite(const Texture2D& texture2D,const Vector2& dimensions)
	:texture2D(texture2D),
	 sourceRect({ 0.0f, 0.0f, (float)texture2D.height, (float)texture2D.width }),
	 dimensions(dimensions)
{
}

void Sprite::Draw()
{
	//Rectangle = { ,,, };
	DrawTexturePro(texture2D, sourceRect, destRect16, { destRect16.width / 2.0f,destRect16.height / 2.0f }, 0, WHITE);
}

Sprite::~Sprite()
{
}