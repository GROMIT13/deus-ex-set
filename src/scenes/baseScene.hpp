#pragma once

#include "space.hpp"
#include "spriteManager.hpp"
#include "currentScene.hpp"

// Base Scene
class Scene
{
public:
	Scene(const Space::Border& gameBorder, const Space::Border& screenBorder);
	~Scene();
	virtual CurrentScene UpdateScene();
	Space GetGameSpace() const;
	Space GetScreenSpace() const;
	void DrawSprite(SpriteName spriteName, const Vector2& pos, float rotation, Color color) const;

protected:
	int frameCounter;
	Space gameSpace;
	Space screenSpace;
	SpriteManager spriteManager;
};
