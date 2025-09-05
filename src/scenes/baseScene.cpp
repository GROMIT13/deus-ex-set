#include "baseScene.hpp"
#include "log.hpp"

Scene::Scene(const Space::Border& gameBorder, const Space::Border& screenBorder)
	:gameSpace(gameBorder), screenSpace(screenBorder), frameCounter(0)
{
}

Scene::~Scene()
{
}

CurrentScene Scene::UpdateScene()
{
	frameCounter++;
	Log::Message("Updated BaseScene");
	return CurrentScene::EXIT;
}

Space Scene::GetGameSpace() const
{
	return gameSpace;
}

Space Scene::GetScreenSpace() const
{
	return screenSpace;
}

void Scene::DrawSprite(SpriteName spriteName, const Vector2& pos, float rotation, Color color) const
{
	spriteManager.DrawSprite(spriteName, pos, rotation, color, (Scene*)this);
}
