#include "Raycaster.h"
#include <cmath>

Vector2 CastRay(
    Vector2 origin,
    float angle,
    std::vector<Wall>& walls,
    float rayLength,
    int &hitWall
)
{
    
    float rad = angle * DEG2RAD;
    hitWall = -1;
    ;

    Vector2 direction =
    {
        cos(rad),
        sin(rad)
    };

    Vector2 rayEnd =
    {
        origin.x + direction.x * rayLength,
        origin.y + direction.y * rayLength
    };

    for (int i = 0; i < walls.size(); i++)
    {
        Wall wall = walls[i];

        Vector2 ray =
        {
            rayEnd.x - origin.x,
            rayEnd.y - origin.y
        };

        Vector2 wallDirection =
        {
            wall.end.x - wall.start.x,
            wall.end.y - wall.start.y
        };

        
    

        float cross =
        ray.x * wallDirection.y -
        ray.y * wallDirection.x;

        if (cross != 0)
        {
            Vector2 originToWallStart =
            {
                wall.start.x - origin.x,
                wall.start.y - origin.y
            };

            float t = (originToWallStart.x * wallDirection.y -
                       originToWallStart.y * wallDirection.x) / cross;

            float u = (originToWallStart.x * ray.y -
                       originToWallStart.y * ray.x) / cross;

            if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
            {
                Vector2 intersection =
                {
                    origin.x + t * ray.x,
                    origin.y + t * ray.y
                };

                float distanceToIntersection = sqrt(
                    (intersection.x - origin.x) * (intersection.x - origin.x) +
                    (intersection.y - origin.y) * (intersection.y - origin.y)
                );

                float distanceToRayEnd = sqrt(
                    (rayEnd.x - origin.x) * (rayEnd.x - origin.x) +
                    (rayEnd.y - origin.y) * (rayEnd.y - origin.y)
                );

                if (distanceToIntersection < distanceToRayEnd)
                {
                    rayEnd = intersection;
                    hitWall = i;
                }
            }
        }       
    }
    
   
    if (hitWall == -1)
    {
        return {-1, -1};
    }

 


    return rayEnd;
}