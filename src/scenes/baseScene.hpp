#pragma once

#include "space.hpp"
#include "object.hpp"

class Scene
{
public:
	Scene(const Space::Border& gameBorder, const Space::Border& screenBorder);
	~Scene();

private:
	Space gameSpace;
	Space screenSpace;
};

Scene::Scene(const Space::Border& gameBorder, const Space::Border& screenBorder)
	:gameSpace(gameBorder), screenSpace(screenBorder)
{
}

Scene::~Scene()
{
}