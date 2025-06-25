#include "raylib.h"
#include "vec.hpp"
#include "window.h"
#include <iostream>
#include <functional>

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (450)

#define WINDOW_TITLE "Window title"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    Texture2D texture = LoadTexture(ASSETS_PATH"test.png"); // Check README.md for how this works
    
    std::cout << Window::Height() << std::endl;
    std::cout << Window::HeightWS() << std::endl;
    std::cout << Window::Scale() << std::endl;
    std::cout << Window::Width() << std::endl;
    std::cout << Window::WidthWS() << std::endl;
    std::cout << std::endl;
    Window::SetScale(3);
    std::cout << Window::Height() << std::endl;
    std::cout << Window::HeightWS() << std::endl;
    std::cout << Window::Scale() << std::endl;
    std::cout << Window::Width() << std::endl;
    std::cout << Window::WidthWS() << std::endl;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
        const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;
        DrawFPS(0, 0);
        DrawTexture(texture, texture_x, texture_y, WHITE);

        const char* text = "OMG! IT WORKS!";
        const Vector2 text_size = MeasureTextEx(GetFontDefault(), text, 20, 1);
        DrawText(text, SCREEN_WIDTH / 2 - text_size.x / 2, texture_y + texture.height + text_size.y + 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}