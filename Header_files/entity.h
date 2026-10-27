#pragma once

#include "../Header_files/physics.h"

#include <raylib.h>
#include <vector>

using namespace std;

//ENTITY STRUCT >>>
struct Entity : public CollisionManager{
    protected:
        //Transform
        Vector2 position = {0.0f, 0.0f}; // Player position
        Vector2 velocity = {0.0f, 0.0f}; // Gravity (not used in this example)
        float gravityMod = 7000.0f;// Gravity modifier
        float t = 1.0f; // Time of collision (not used in this example)

        //Collision
        Vector2 CollisionBoxWH;
        Rectangle collisionBox;
        int boxID = -1;
    
    public:
        //Update transform and collision box
        void Update(float fixed_dt, const Rectangle& level);
};