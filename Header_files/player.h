#pragma once

#include "../Header_files/entity.h"

#include <raylib.h>

using namespace std;

//PLAYER STRUCT >>>
struct Player : public Entity{
    private:
        //Temporary
        float radius = 30.0f; // Radius of the circle (player)
        float ShotgunWidth = 20.0f;
        float ShotgunHeight = radius + 20.0f;
        Rectangle shotgun = {0.0f, 0.0f, ShotgunWidth, ShotgunHeight};
            
        float angle = 0.0f;// Blast angle
        float blastPower = 2000.0f;// Blast power
        float blastXMod = 0.9f;// Blast modifier

        float speed = 900.0f; // Player speed (not used in this example)
        float ADspeed = 0.0f; // Temporary variable for speed adjustment based on key input

    public:
            
        //Temporary floor
        Rectangle floor = {0.0f, float(GetScreenHeight()) - 300.0f, float(GetScreenWidth()) / 1.0f, float(GetScreenHeight() / 3.0f)};

        void Reset();
        void InputHandling(float fixed_dt);
        
        void UpdateShotgunPosition();

        void RenderDebugText(float fixed_dt, float dt)const;
        void RenderPlayer()const;
        void RenderShotgun()const;
};