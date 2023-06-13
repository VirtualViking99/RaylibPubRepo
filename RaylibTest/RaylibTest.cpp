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
    

    InitWindow(screenWidth, screenHeight, "RPG Test");

    //Set the position of the character, as well as the radius(this a collision so to speak)
    Vector2 CharPos{ screenWidth / 2, screenHeight / 2 };
    const float Char_radius = 10;

    //Load the texture of the map and scale to the dimensions of the screen
    Texture2D forestMap = LoadTexture("Forestmap.png");
    Vector2 texturePosition = { 0, 0 };
    float textureScaleX = (float)screenWidth / forestMap.width;
    float textureScaleY = (float)screenHeight / forestMap.height;

    


    // Create the camera Zoom Level
    float zoomLevel = (float)(forestMap.width * forestMap.height) / (screenWidth * screenHeight) / 1.6f;
    
    // Define the area of the camera
    Rectangle cameraArea = { 0, 0, forestMap.width, forestMap.height };



    // Create the camera
    Camera2D camera;
    camera.target = CharPos;
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = zoomLevel;


    // Boolean variables to track camera state
    bool isCameraAtBounds = false;
    bool isCameraMovingToCenter = false;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        GVLib::Movespeed MS;
        

        //Running condition
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
            MS.movespeed = MS.movespeed * 2;

        if (IsKeyDown(KEY_D) && CharPos.x + Char_radius + MS.movespeed < cameraArea.x + cameraArea.width) {
            CharPos.x += MS.movespeed;
            if (camera.target.x < screenWidth / 2.0f)
                camera.target.x +=MS.movespeed;
        }
        if (IsKeyDown(KEY_A) && CharPos.x - Char_radius - MS.movespeed > cameraArea.x)
        {
            CharPos.x -= MS.movespeed;
            if (camera.target.x > screenWidth / 2.0f)
                camera.target.x -= MS.movespeed;
        }
        if (IsKeyDown(KEY_W) && CharPos.y - Char_radius - MS.movespeed > cameraArea.y)
        {
            CharPos.y -= MS.movespeed;
            if (camera.target.y > screenHeight / 2.0f)
                camera.target.y -= MS.movespeed;
        }
        if (IsKeyDown(KEY_S) && CharPos.y + Char_radius + MS.movespeed < cameraArea.y + cameraArea.height)
        {
            CharPos.y += MS.movespeed;
            if (camera.target.y < screenHeight / 2.0f)
                camera.target.y += MS.movespeed;
        }

        // Check if camera is at the bounds of the texture
        if (camera.target.x <= cameraArea.x || camera.target.x >= cameraArea.width - screenWidth ||
            camera.target.y <= cameraArea.y || camera.target.y >= cameraArea.height - screenHeight)
        {
            isCameraAtBounds = true;
        }
        else
        {
            isCameraAtBounds = false;
            isCameraMovingToCenter = false;
        }

        // Adjust camera target based on camera position
        if (isCameraAtBounds)
        {
            if (!isCameraMovingToCenter)
            {
                if (camera.target.x <= cameraArea.x)
                    camera.target.x = camera.offset.x;
                else if (camera.target.x >= cameraArea.width - screenWidth)
                    camera.target.x = cameraArea.width - camera.offset.x;
                if (camera.target.y <= cameraArea.y)
                    camera.target.y = camera.offset.y;
                else if (camera.target.y >= cameraArea.height - screenHeight)
                    camera.target.y = cameraArea.height - camera.offset.y;

                isCameraMovingToCenter = true;
            }
        }
        else
        {
            camera.target = CharPos;
        }

        ClearBackground(RAYWHITE);

        BeginMode2D(camera);


        DrawTextureEx(forestMap, texturePosition, 0.0f, textureScaleX, WHITE);

        DrawCircleV(CharPos, 10, RED);


        EndMode2D();


        EndDrawing();
    }

    CloseWindow();

    return 0;
}

