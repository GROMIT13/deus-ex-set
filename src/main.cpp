#include "raylib.h"
#include "vec.hpp"
#include "window.hpp"
#include "entity.hpp"
#include "log.hpp"
#include "player.hpp"
#include "colliders.hpp"
#include "space.hpp"
#include <iostream>

int main(void)
{
    Space::Border gameBorder;
    gameBorder.left   = -60.0f;
    gameBorder.right  =  60.0f;
    gameBorder.bottom = -80.0f;
    gameBorder.top    =  80.0f;
    Space::Border screenBorder;
    screenBorder.left = 0;
    screenBorder.right = 120.0f * 6; //Bottom is top since y axis in raylib is down
    screenBorder.bottom = 0.0f;
    screenBorder.top = 160.0f * 6;

    Space gameSpace(gameBorder);
    Space screenSpace(screenBorder);
    //Window::SetScale(1);
    InitWindow(Window::WidthWS(), Window::HeightWS(), "Deus Ex Set");
    SetTargetFPS(60);

    Vector2 pos = { 0,0 };
    Player::Properties properties = { false,2,3,0,0,0,1.0f,0.5f };
    Player player(pos, properties, properties);
    //CircleCollider c1({300,300-51}, 20);
    //CircleCollider c2({300,300}, 30);
    Vector2 playerDrawPos = {0,0};

    while (!WindowShouldClose())
    {
        player.Update();
        //c1.pos = player.pos;
        playerDrawPos = screenSpace.ToThisSpace(player.pos, gameSpace);
        std::cout << playerDrawPos << std::endl;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawFPS(0, 0);
        //DrawCircle(player.pos.x, player.pos.y, c1.radius, BLACK);
        DrawCircle(playerDrawPos.x, playerDrawPos.y, 10, BLACK);
        //if(c1.Intersects(c2))
        //    DrawCircle(300, 300, 30, RED);
        //else
        //    DrawCircle(300, 300, 30, GREEN);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}