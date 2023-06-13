#pragma warning(default : 4244)

#include "raylib.h"
#include "GVLib.h"

#include<string>
#include<iostream>
#include "RaylibTest.h"


//// all the states the program can be in 
//enum class ApplicationStates
//{
//    Startup,
//    Loading,
//    Menu,
//    Running,
//    Paused,
//    GameOver,
//    Quitting
//};


int main(void)
{
    const float screenWidth = 1600.0f;
    const float screenHeight = 900.0f;
    

    InitWindow(screenWidth, screenHeight, "Ball Movement");

    //Set the position of the character, as well as the radius(this a collision so to speak)
    Vector2 CharPos{ screenWidth / 2, screenHeight / 2 };
    const float Char_radius = 10;

    //Load the texture of the map and scale to the dimensions of the screen
    Texture2D forestMap = LoadTexture("Forestmap.png");
    Vector2 texturePosition = { 0, 0 };
    float textureScaleX = (float)screenWidth / forestMap.width;
    float textureScaleY = (float)screenHeight / forestMap.height;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        GVLib::Movespeed MS;
        

        //Running condition
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
            MS.movespeed = MS.movespeed * 2;

        if (IsKeyDown(KEY_D) && CharPos.x + Char_radius + MS.movespeed < screenWidth)
            CharPos.x += MS.movespeed;
        if (IsKeyDown(KEY_A) && CharPos.x - Char_radius - MS.movespeed > 0)
            CharPos.x -= MS.movespeed;
        if (IsKeyDown(KEY_W) && CharPos.y - Char_radius - MS.movespeed > 0)
            CharPos.y -= MS.movespeed;
        if (IsKeyDown(KEY_S) && CharPos.y + Char_radius + MS.movespeed < screenHeight)
            CharPos.y += MS.movespeed;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextureEx(forestMap, texturePosition, 0.0f, textureScaleX, WHITE);

        DrawCircleV(CharPos, 10, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

