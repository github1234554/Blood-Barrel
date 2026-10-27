#include "../Header_files/physics.h"

#include <raylib.h>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

pair<float, Vector2> CollisionManager::CheckCollision(const Rectangle& active, const Vector2 velocity, const float fixed_dt, const Rectangle& passive){
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

pair<float, Vector2> CollisionManager::CollisionHandler(const Rectangle collisionBox, const vector< tuple <Rectangle, bool, int> >& collisionSet, const Vector2 velocity, const float fixed_dt){
    float t = 1.0f;
    Vector2 normal = {0.0f, 0.0f};
    for (const tuple <Rectangle, bool, int>& box : collisionSet){
        pair<float, Vector2> collisionResult = CheckCollision(collisionBox, velocity, fixed_dt, get<0>(box));
        if (collisionResult.first < t){
            t = collisionResult.first;
            normal = collisionResult.second;
        }
    }
    return {t, normal};
}

pair <bool, vector< tuple <Rectangle, bool, int> >::iterator > CollisionManager::checkID(int ID, vector< tuple <Rectangle, bool, int> >& collisionSet){
    vector< tuple <Rectangle, bool, int> >::iterator check = find_if(collisionSet.begin(), collisionSet.end(), [ID](const tuple <Rectangle, bool, int> collisionBox){
        return get<2>(collisionBox) == ID;
    });
    if (check != collisionSet.end()){
        return {true, check};
    }
    else{
        return {false, check};
    }
}

int CollisionManager::add(Rectangle collisionBox, bool isLevel, vector< tuple <Rectangle, bool, int> >& collisionSet){
    tuple <Rectangle, bool, int> box = {collisionBox, isLevel, ID_count};
    collisionSet.push_back(box);
    ID_count += 1;
    return get<2>(box);
}

void CollisionManager::remove(int ID, vector< tuple <Rectangle, bool, int> >& collisionSet){
    pair <bool, vector< tuple <Rectangle, bool, int> >::iterator > boxInSet = checkID(ID, collisionSet);
    if (boxInSet.first){
        collisionSet.erase(boxInSet.second);
    }
}
void CollisionManager::update(int ID, Vector2 position, vector< tuple <Rectangle, bool, int> >& collisionSet){
    pair <bool, vector< tuple <Rectangle, bool, int> >::iterator > boxInSet = checkID(ID, collisionSet);
    if (boxInSet.first){
        get<0>(*boxInSet.second) = {position.x - get<0>(*boxInSet.second).width / 2, position.y - get<0>(*boxInSet.second).height / 2, get<0>(*boxInSet.second).width, get<0>(*boxInSet.second).height};
    }
}
void CollisionManager::modify(int ID, Vector2 dimensions, bool isLevel, vector< tuple <Rectangle, bool, int> >& collisionSet){

}