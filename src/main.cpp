#include "raylib.h"
#include "vec.hpp"
#include "window.h"
#include "entity.hpp"
#include "log.hpp"
#include "player.hpp"
#include "colliders.hpp"
#include <iostream>
//#include <functional>

int main(void)
{
    Window::SetScale(1);
    InitWindow(Window::WidthWS(), Window::HeightWS(), "Deus Ex Set");
    SetTargetFPS(60);

    Vector2 pos = { 0,0 };
    Player::Properties properties = { false,2,3,0,0,0,1.0f,0.5f };
    Player player(pos, properties, properties);
    CircleCollider c1({300,300-51}, 20);
    CircleCollider c2({300,300}, 30);

    while (!WindowShouldClose())
    {
        player.Update();
        c1.pos = player.pos;
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawFPS(0, 0);
        DrawCircle(player.pos.x, player.pos.y, c1.radius, BLACK);
        if(c1.Intersects(c2))
            DrawCircle(300, 300, 30, RED);
        else
            DrawCircle(300, 300, 30, GREEN);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}