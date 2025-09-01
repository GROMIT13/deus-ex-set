#pragma once

#include "raylib.h"
#include "baseScene.hpp"
#include "Window.hpp"

void DrawCircleV(Vector2 center, float radius, Color color, Scene* scene)
{
	Vector2 drawPos = scene->GetScreenSpace().ToThisSpace(center, scene->GetGameSpace());
	DrawCircleV(drawPos, radius * Window::Scale(), color);
}

void DrawTexturePro()
{

}