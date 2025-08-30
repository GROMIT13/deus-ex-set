#pragma once

//#include <vector>
#include "space.hpp"
//#include "object.hpp"
//#include "player.hpp"
//#include "entity.hpp"

// Base Scene
class Scene
{
public:
	Scene(const Space::Border& gameBorder, const Space::Border& screenBorder);
	~Scene();
	void UpdateScene();
	Space GetGameSpace();
	Space GetScreenSpace();

protected:
	int frameCounter;
	Space gameSpace;
	Space screenSpace;
};
