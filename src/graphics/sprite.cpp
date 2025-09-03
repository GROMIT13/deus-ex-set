#include "sprite.hpp"
#include "window.hpp"
#include "log.hpp"
#include "baseScene.hpp"


Sprite::Sprite(const char* file)
	:Sprite(file, TEXTURE_FILTER_BILINEAR, TEXTURE_WRAP_CLAMP)
{

}

Sprite::Sprite(const char* file, TextureFilter filter, TextureWrap wrap)
{
	texture2D = LoadTexture(TextFormat("%s%s%s", ASSETS_PATH, "textures/", file));
	SetTextureFilter(texture2D, filter);
	SetTextureWrap(texture2D, wrap);

	sourceRect = { 0.0f, 0.0f, (float)texture2D.width, (float)texture2D.height };
	dimensions = { (float)(texture2D.width / 6.0f), (float)(texture2D.height / 6.0f) };
}

void Sprite::Draw(const Vector2& pos, float rotation, Color color)
{
	Rectangle destRect = { pos.x,pos.y,dimensions.x * Window::Scale(), dimensions.y * Window::Scale() };
	DrawTexturePro(texture2D, sourceRect, destRect, { destRect.width / 2.0f, destRect.height / 2.0f }, rotation, color);
}

void Sprite::Draw(const Vector2& pos, float rotation, Color color, Scene* scene)
{
	Vector2 drawPos = scene->GetScreenSpace().ToThisSpace(pos, scene->GetGameSpace());
	Draw(drawPos, rotation, color);
}

Sprite::~Sprite()
{
	UnloadTexture(texture2D);
}