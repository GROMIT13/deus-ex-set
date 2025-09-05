#include "draw.hpp"
#include "baseScene.hpp"
#include "Window.hpp"
#include "vec.hpp"

void DrawCircleV(Vector2 center, float radius, Color color, Scene* scene)
{
	Vector2 drawPos = scene->GetScreenSpace().ToThisSpace(center, scene->GetGameSpace());
	DrawCircleV(drawPos, radius * Window::Scale(), color);
}

void DrawRectangleV(Vector2 position, Vector2 size, Color color, Scene* scene)
{
	Vector2 drawPos = scene->GetScreenSpace().ToThisSpace(position, scene->GetGameSpace());
	Vector2 drawSize = size * (float)Window::Scale();
	DrawRectangleV(drawPos, drawSize, color);
}
