#include <iostream>
#include <raylib.h>
#include <cmath>
#include <vector>
#include "Wall.h"
#include "Player.h"
#include "Raycaster.h"


int main() {
    const int screenWidth = 1200;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Raycaster");


    SetTargetFPS(60);
    
    Player player;
    
    player.Pos = {400, 300};
    player.Dir = 270.0f;
    player.speed = 2.0f;
    std::vector<Wall> walls;
    Vector2 clickStart = {0, 0};
    Vector2 clickEnd = {0, 0};
    int rayCount = 1200;
    float rayLength = 500;
    bool editorMode = true;
    int hitWall = -1;

    float FOV = 60.0f;
    rayCount = screenWidth;



    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground({15, 15, 18, 255});
    
        Vector2 mousePos = GetMousePosition();
        player.Move(walls, screenWidth, screenHeight);
        player.UpdateRotation();
        




        if (IsKeyPressed(KEY_E))
        {
            editorMode = !editorMode;
        }

        if (editorMode == false)
        {
        
            ClearBackground({15, 15, 18, 255});

            

            for (int i = 0; i < rayCount; i++)
                {
                    float rayAngle = player.Dir - FOV / 2 + i * (FOV / rayCount);

                    Vector2 rayEnd = CastRay(
                        player.Pos,
                        rayAngle,
                        walls,
                        rayLength,
                        hitWall
                    );

                    Vector2 displayRayEnd =
                    {
                        player.Pos.x + (float)cos(rayAngle * DEG2RAD) * rayLength,
                        player.Pos.y + (float)sin(rayAngle * DEG2RAD) * rayLength
                    };

                    if (rayEnd.x != -1)
                    {
                        displayRayEnd = rayEnd;


                        Wall& wall = walls[hitWall];

                        float distanceToStart = sqrt(
                            (rayEnd.x - wall.start.x) * (rayEnd.x - wall.start.x) +
                            (rayEnd.y - wall.start.y) * (rayEnd.y - wall.start.y)
                        );

                        float distanceToEnd = sqrt(
                            (rayEnd.x - wall.end.x) * (rayEnd.x - wall.end.x) +
                            (rayEnd.y - wall.end.y) * (rayEnd.y - wall.end.y)
                        );

                        bool startConnected = false;
                        bool endConnected = false;

                        for (int j = 0; j < walls.size(); j++)
                        {
                            if (j == hitWall)
                                continue;

                            Wall& otherWall = walls[j];

                            if (CheckCollisionPointCircle(otherWall.start, wall.start, 5.0f) ||
                                CheckCollisionPointCircle(otherWall.end, wall.start, 5.0f))
                            {
                                startConnected = true;
                            }

                            if (CheckCollisionPointCircle(otherWall.start, wall.end, 5.0f) ||
                                CheckCollisionPointCircle(otherWall.end, wall.end, 5.0f))
                            {
                                endConnected = true;
                            }
                        }

                        float cornerDistance = 999999.0f;

                        if (startConnected)
                        {
                            cornerDistance = fmin(cornerDistance, distanceToStart);
                        }

                        if (endConnected)
                        {
                            cornerDistance = fmin(cornerDistance, distanceToEnd);
                        }

                        float cornerDarkness = 1.0f - cornerDistance / 50.0f;

                        if (cornerDarkness < 0.0f)
                            cornerDarkness = 0.0f;

                        if (cornerDarkness > 1.0f)
                            cornerDarkness = 1.0f;

                        if (cornerDarkness < 0.0f)
                            cornerDarkness = 0.0f;

                        if (cornerDarkness > 1.0f)
                            cornerDarkness = 1.0f;


                        float distance = sqrt(
                            (rayEnd.x - player.Pos.x) * (rayEnd.x - player.Pos.x) +
                            (rayEnd.y - player.Pos.y) * (rayEnd.y - player.Pos.y)
                        );

                        float angleDifference = rayAngle - player.Dir;
                        float correctedDistance =
                            distance * cos(angleDifference * DEG2RAD);
                        float brightness = 1.0f - correctedDistance / (float)rayLength;
                        float outlineBrightness =
                            0.3f + 0.7f * (correctedDistance / rayLength);

                        Color outlineColor = {
                            (unsigned char)(100 * outlineBrightness),
                            0,
                            0,
                            255
                        };


                        if (brightness < 0.0f)
                            brightness = 0.0f;

                        float finalBrightness = brightness * (1.0f - cornerDarkness * 0.7f);

                        Color wallColor = {
                            (unsigned char)(255 * finalBrightness),
                            0,
                            0,
                            255
                        };

                        
                        
                        float wallHeight = (30000.0f / correctedDistance) 
                            * (screenHeight / 600.0f);                        
                        float screenX = i * ((float)screenWidth / rayCount);

                        float wallTop = 300.0f - wallHeight / 2;
                        float wallBottom = 300.0f + wallHeight / 2;
                        
                        DrawLineEx(
                        {screenX, wallTop},
                        {screenX, wallBottom},
                        1.0f,
                        wallColor
                    );
                    }
            
            }
              
            
        }

        else
            {

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    clickStart = GetMousePosition();
                    clickEnd = GetMousePosition();
                }
                DrawCircleV(clickStart, 5.0f, GREEN);

                
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    DrawLineEx(clickStart, mousePos, 2.0f, GREEN);
                }
                
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    clickEnd = GetMousePosition();
                    Wall newWall;
                    newWall.start = clickStart;
                    newWall.end = clickEnd;
                    walls.push_back(newWall);
                }

                player.Draw(); 
                
            

        

                if (IsKeyDown(KEY_LEFT_SHIFT))
                {
                    if (IsKeyPressed(KEY_C))
                    {
                        clickStart = {0, 0};
                        clickEnd = {0, 0};
                        walls.clear();
                    }
                }
                ClearBackground(RAYWHITE);
                for (int i = 0; i < walls.size(); i++)
                {
                    DrawLineEx(
                        walls[i].start,
                        walls[i].end,
                        5.0f,
                        BLACK
                    );
                }        
            } 
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}