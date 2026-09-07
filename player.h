#pragma once

#include <raylib.h>
#include "wall.h"
#include <vector>
class Player
{
public:
    Vector2 Pos = {400, 300};
    float Dir = 270.0f;
    float speed = 2.0f;

    void UpdateRotation();
    void Draw();
    void Move(std::vector<Wall>& walls, int screenWidth, int screenHeight); 
};