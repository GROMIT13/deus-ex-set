#define GLSL_VERSION 430

#include "raylib.h"
#include "vec.hpp"
#include "window.hpp"
#include "entity.hpp"
#include "log.hpp"
#include "playerS.hpp"
#include "space.hpp"
#include "bulletManager.hpp"
#include "baseScene.hpp"
#include "baseLevel.hpp"
#include "menu.hpp"
#include "currentScene.hpp"
#include "spriteManager.hpp"
#include <iostream>
#include <vector>

int main(void)
{
    Window::SetScale(1);

    InitWindow(Window::WidthWS(), Window::HeightWS(), "Deus Ex Set");
    SetWindowIcon(LoadImage(ASSETS_PATH"textures/aleph_big.png"));
    InitAudioDevice();
    SetTargetFPS(FPS);

    Window::SetScale(GetMaxWindowScale());
    SetWindowSize(Window::WidthWS(), Window::HeightWS());
    SetWindowPositionCenter();


    /* BulletManager bm(2000);
    Bullet bullet;
    bullet.canDamagePlayer = true;
    bullet.velocity = { 0.0f,0.0f };
    bullet.acceleration = { 0.0f,0.02f };
    bullet.hitboxRadius = 3.0f;
    bullet.isActive = true;
    bullet.lifetime = 60 * 20;
    bullet.pos = { Window::WidthWS()/2.0f, Window::HeightWS()/2.0f };
    bullet.rotation = 0.0f;
    bullet.UpdateFunction = [](Bullet* bullet) { bullet->PhysicsUpdateWithRotation(); };*/

    Space::Border gameBorder;
    gameBorder.left = -60.0f;
    gameBorder.right = 60.0f;
    gameBorder.bottom = -80.0f;
    gameBorder.top = 80.0f;
    Space::Border screenBorder;
    screenBorder.left = 0;
    screenBorder.right = 120.0f * Window::Scale();
    screenBorder.bottom = 0.0f;                   //Bottom is top since y axis in raylib is down
    screenBorder.top = 160.0f * Window::Scale();

    Space gameSpace(gameBorder);
    Space screenSpace(screenBorder);

    //LevelScene level(gameBorder, screenBorder, PlayerType::S);
    MenuScene menu(gameBorder, screenBorder);

    CurrentScene currentScene = CurrentScene::MENU;

    while (!WindowShouldClose() && currentScene != CurrentScene::EXIT)
    {
        switch (currentScene)
        {
        case CurrentScene::MENU: currentScene = menu.UpdateScene(); break;
        case CurrentScene::LEVEL1_S: std::cout << "loaded level1 S" << std::endl; break;
        case CurrentScene::LEVEL1_P: std::cout << "loaded level1 P" << std::endl; break;
        case CurrentScene::EXIT: std::cout << "Quitting..." << std::endl; break;
        default:
            break;
        }
        
        //level.UpdateScene();
    }

    CloseWindow();

    return 0;
}