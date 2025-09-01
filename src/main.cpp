#define GLSL_VERSION 430

#include "raylib.h"
#include "vec.hpp"
#include "window.hpp"
#include "entity.hpp"
#include "log.hpp"
#include "player.hpp"
#include "space.hpp"
#include "bulletManager.hpp"
#include "baseScene.hpp"
#include "baseLevel.hpp"
#include <iostream>
#include <vector>

int main(void)
{
    Window::SetScale(3);
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
    Player::Properties properties = { false,2,3,0,0,0,1.5f * 6,0.75f * 6,3.0f,{10.0f,10.0f} };
    Player player({0.0f,0.0f}, properties, properties, nullptr);
    Vector2 playerDrawPos = { 0,0 };
    BulletManager bm(2000);
    Bullet bullet;
    bullet.canDamagePlayer = true;
    bullet.velocity = { 0.0f,0.0f };
    bullet.acceleration = { 0.0f,0.02f };
    bullet.hitboxRadius = 3.0f;
    bullet.isActive = true;
    bullet.lifetime = 60 * 20;
    bullet.pos = { Window::WidthWS()/2.0f, Window::HeightWS()/2.0f };
    bullet.rotation = 0.0f;
    bullet.UpdateFunction = [](Bullet* bullet) { bullet->PhysicsUpdateWithRotation(); };

    Texture2D testTexture2D = LoadTexture(ASSETS_PATH"textures/test32.png");
    SetTextureFilter(testTexture2D, TEXTURE_FILTER_BILINEAR);
    SetTextureWrap(testTexture2D, TEXTURE_WRAP_CLAMP);

    LevelScene level(gameBorder, screenBorder, player);
    Rectangle rect = { 0.0f,0.0f,(float)testTexture2D.height,(float)testTexture2D.width }; //w and h -size of texture
    Rectangle destRect16 = { 256.0f-64.0f,256.0f,rect.width*8,rect.height*8 };
    int frame = 0;
    while (!WindowShouldClose())
    {
        frame++;
        frame++;
        frame++;
        //level.UpdateScene();
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(testTexture2D, rect, destRect16, { destRect16.width/2.0f,destRect16.height/2.0f }, frame, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}