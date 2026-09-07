#include "Player.h"
#include <raylib.h>
#include <cmath>


void Player::UpdateRotation()
{
    if (IsKeyDown(KEY_D))
    {
        Dir += 1.0f;

        if (Dir >= 360.0f)
            Dir -= 360.0f;
    }

    if (IsKeyDown(KEY_A))
    {
        Dir -= 1.0f;

        if (Dir < 0.0f)
            Dir += 360.0f;
    }
}

void Player::Draw()
{
    float rad = Dir * DEG2RAD;

   

    Vector2 playerNose =
    {
        Pos.x + cos(rad) * 10,
        Pos.y + sin(rad) * 10
    };

    Vector2 playerBack =
    {
        Pos.x - cos(rad) * 10,
        Pos.y - sin(rad) * 10
    };

    Vector2 playerLeft =
    {
        playerBack.x + cos(rad + 3.14159f / 2) * 10,
        playerBack.y + sin(rad + 3.14159f / 2) * 10
    };

    Vector2 playerRight =
    {
        playerBack.x + cos(rad - 3.14159f / 2) * 10,
        playerBack.y + sin(rad - 3.14159f / 2) * 10
    };

    DrawTriangle(
        playerNose,
        playerRight,
        playerLeft,
        RED
    );

    DrawLineEx(
        Pos,
        playerNose,
        2.0f,
        BLUE
    );


}


void Player::Move(std::vector<Wall>& walls, int screenWidth, int screenHeight)
{
    float rad = Dir * DEG2RAD;

    Vector2 forward = {
        cos(rad) * speed,
        sin(rad) * speed
    };

    Vector2 movement = {0, 0};

    if (IsKeyDown(KEY_W))
    {
        movement = forward;
    }

    if (IsKeyDown(KEY_S))
    {
        movement = {-forward.x, -forward.y};
    }

    Vector2 futurePosition = {
        Pos.x + movement.x,
        Pos.y + movement.y
    };

    int playerHitWall = -1;

    for (int i = 0; i < walls.size(); i++)
    {
        if (CheckCollisionPointLine(
            futurePosition,
            walls[i].start,
            walls[i].end,
            10.0f))
        {
            playerHitWall = i;
            break;
        }
    }

    if (playerHitWall == -1)
    {
        if (futurePosition.x > 0 && futurePosition.x < screenWidth)
        {
            Pos.x += movement.x;
        }

        if (futurePosition.y > 0 && futurePosition.y < screenHeight)
        {
            Pos.y += movement.y;
        }
    }
    else
    {
        Wall hitWall = walls[playerHitWall];

        Vector2 wallSize = {
            hitWall.end.x - hitWall.start.x,
            hitWall.end.y - hitWall.start.y
        };

        float wallLength = sqrt(
            wallSize.x * wallSize.x +
            wallSize.y * wallSize.y
        );

        if (wallLength != 0)
        {
            wallSize.x /= wallLength;
            wallSize.y /= wallLength;
        }

        float dot =
            movement.x * wallSize.x +
            movement.y * wallSize.y;

        Vector2 slide = {
            wallSize.x * dot,
            wallSize.y * dot
        };

        Pos.x += slide.x;
        Pos.y += slide.y;
    }
}