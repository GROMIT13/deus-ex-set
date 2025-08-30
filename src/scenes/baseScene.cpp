#include "baseScene.hpp"
#include "log.hpp"

Scene::Scene(const Space::Border& gameBorder, const Space::Border& screenBorder)
	:gameSpace(gameBorder), screenSpace(screenBorder), frameCounter(0)
{
}

Scene::~Scene()
{
}

void Scene::UpdateScene()
{
	frameCounter++;
	Log::Message("Updated BaseScene");
}

Space Scene::GetGameSpace()
{
	return gameSpace;
}

Space Scene::GetScreenSpace()
{
	return screenSpace;
}
