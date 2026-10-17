#include "../Header_files/physics.h"

#include <raylib.h>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

pair<float, Vector2> CheckCollision(const Rectangle& active, Vector2 velocity, float fixed_dt, const Rectangle& passive){
    //Minkowski sum (collision box)
    Rectangle minkowskiSum = {passive.x - active.width / 2, passive.y - active.height / 2, passive.width + active.width, passive.height + active.height};

    //Collision slabs
    float minX = minkowskiSum.x;
    float maxX = minkowskiSum.x + minkowskiSum.width;
    float minY = minkowskiSum.y;
    float maxY = minkowskiSum.y + minkowskiSum.height;

    //Raycasting
    float rayOriginX = active.x + active.width / 2;
    float rayOriginY = active.y + active.height / 2;
    float rayEndX = rayOriginX + velocity.x * fixed_dt;
    float rayEndY = rayOriginY + velocity.y * fixed_dt;

    float t1x, t2x, t1y, t2y;

    if (! (velocity.x == 0.0f )) { // Prevent division by zero for vertical movement
        t1x = (minX - rayOriginX) / (velocity.x * fixed_dt);
        t2x = (maxX - rayOriginX) / (velocity.x * fixed_dt);
    }
    else { // If velocity.x is zero, set t1x and t2x to extreme values to avoid division by zero
        t1x = -std::numeric_limits<float>::infinity();
        t2x = std::numeric_limits<float>::infinity();
    }

    if (! (velocity.y == 0.0f )) { // Prevent division by zero for horizontal movement
        t1y = (minY - rayOriginY) / (velocity.y * fixed_dt);
        t2y = (maxY - rayOriginY) / (velocity.y * fixed_dt);
    }
    else { // If velocity.y is zero, set t1y and t2y to extreme values to avoid division by zero
        t1y = -std::numeric_limits<float>::infinity();
        t2y = std::numeric_limits<float>::infinity();
    }

    float tminX = min(t1x, t2x);
    float tmaxX = max(t1x, t2x);
    float tminY = min(t1y, t2y);
    float tmaxY = max(t1y, t2y);

    float tFarEntry = max(tminX, tminY);
    float tNearExit = min(tmaxX, tmaxY);

    if (tFarEntry <= tNearExit && tFarEntry >= 0 && tFarEntry <= 1) {
        //Collision detected
        if (tminX > tminY){
            if (velocity.x < 0){
                return {tFarEntry, {1.0f, 0.0f}}; // Collision on the right side
            }
            else{
                return {tFarEntry, {-1.0f, 0.0f}}; // Collision on the left side
            }
        }
        else{
            if (velocity.y < 0){
                return {tFarEntry, {0.0f, 1.0f}}; // Collision on the bottom side
            }
            else{
                return {tFarEntry, {0.0f, -1.0f}}; // Collision on the top side
            }
        }
    }
    else{
        //No collision
        return {1.0f, {0.0f, 0.0f}}; //Return 1.0f if no collision detected
    }
}