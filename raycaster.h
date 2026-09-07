#pragma once

#include <raylib.h>
#include <vector>
#include "Wall.h"

Vector2 CastRay(
    Vector2 origin,
    float angle,
    std::vector<Wall>& walls,
    float rayLength,
    int &hitWall
);