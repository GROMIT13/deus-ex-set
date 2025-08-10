#define GLSL_VERSION 430
//#define FPS 60

#include "raylib.h"
#include "vec.hpp"
#include "window.hpp"
#include "entity.hpp"
#include "log.hpp"
#include "player.hpp"
#include "space.hpp"
#include "bulletManager.hpp"
#include <iostream>
#include <vector>

int main(void)
{
    Space::Border gameBorder;
    gameBorder.left   = -60.0f;
    gameBorder.right  =  60.0f;
    gameBorder.bottom = -80.0f;
    gameBorder.top    =  80.0f;
    Space::Border screenBorder;
    screenBorder.left = 0;
    screenBorder.right = 120.0f * Window::Scale(); 
    screenBorder.bottom = 0.0f;                   //Bottom is top since y axis in raylib is down
    screenBorder.top = 160.0f * Window::Scale();

    Space gameSpace(gameBorder);
    Space screenSpace(screenBorder);

    InitWindow(Window::WidthWS(), Window::HeightWS(), "Deus Ex Set");
    InitAudioDevice();
    SetTargetFPS(FPS);

    Vector2 pos = { Window::WidthWS()*0.5f ,Window::HeightWS()*0.75f };
    Player::Properties properties = { false,2,3,0,0,0,1.5f * 6,0.75f*6,1.0f };
    Player player(pos, properties, properties);
    Vector2 playerDrawPos = { 0,0 };
    BulletManager bm(2000);
    Bullet bullet;
    bullet.canDamagePlayer = true;
    bullet.velocity = { 0.0f,0.0f };
    bullet.acceleration = { 0.0f,0.02f };
    bullet.hitboxRadius = 5.0f;
    bullet.isActive = true;
    bullet.lifetime = 60 * 20;
    bullet.pos = { Window::WidthWS()/2.0f, Window::HeightWS()/2.0f };
    bullet.rotation = 0.0f;
    bullet.UpdateFunction = [](Bullet* bullet) { bullet->PhysicsUpdateWithRotation(); };

    bool HasDied = false;
    bool playSound = false;
    Texture2D deadTexture2D = LoadTexture(ASSETS_PATH"textures/dead.png");
    Sound explosion = LoadSound(ASSETS_PATH"audio/deltarune-explosion.mp3");


    while (!WindowShouldClose())
    {
        // UPDATE //
        player.Update();
        playerDrawPos = screenSpace.ToThisSpace(player.pos, gameSpace);
        bullet.velocity = { ((rand()%100)/20.0f - 2.5f)/1.0f, ((rand() % 100) / 25.0f - 4.0f)/1.0f};
        //bullet.velocity = { ((rand()%100)/50.0f-1.0f)/20.0f, ((rand() % 100) / 50.0f-1.0f)/20.0f};
        bm.InstantiateBullet(bullet);
        bm.Update();
        if (bm.CollidesWithPlayer(player))
        {
            bm.DestroyAllBullets();
            Log::Message("PlayerHit - You Dubmbass");
            HasDied = true;
            playSound = true;
        }

        if (playSound)
        {
            playSound = false;
            PlaySound(explosion);
        }

        // DRAW //

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(player.pos.x, player.pos.y, 30, 30, BLACK);
            DrawCircle(player.pos.x + 15, player.pos.y + 15, 10, MAROON);
            DrawCircle(player.pos.x + 15, player.pos.y + 15, 6, RED);
            bm.DrawBullets();
            if (HasDied)
            {
                DrawTexture(deadTexture2D, 0, 0, WHITE);
            }
            DrawFPS(0, 0);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}