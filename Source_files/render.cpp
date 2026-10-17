#include "../Header_files/render.h"
#include "../Header_files/player.h"

#include <raylib.h>

using namespace std;

void Player::RenderDebugText(float fixed_dt, float dt)const{
    //Text
    DrawText(TextFormat("%.2f, %.2f", position.x, position.y), 10, 10, 20, BLUE); // Debug text
    DrawText(TextFormat("%.10f, %.10f", fixed_dt, dt), 10, 40, 20, BLUE); // Debug text
    DrawText(TextFormat("%.i", GetFPS()), 10, 70, 20, GREEN); // Debug text
}

void Player::RenderPlayer()const{
    DrawCircleV(position, radius, MAROON); // Player
    //DrawRectangleRec(collisionBox, GREEN); // Collision box
}

void Player::RenderShotgun()const{
    DrawRectanglePro(shotgun, {ShotgunWidth / 2, ShotgunHeight}, angle, BLUE);
}

void Render(const Player& player, const Rectangle& level, float fixed_dt, float dt){
    //DRAW >>>
    BeginDrawing(); // Begins drawing

    //Background
    ClearBackground(RAYWHITE); // Clears the background with white color

    //Level (temporary)
    DrawRectangleRec(level, GRAY);

    //Textures (or temporary shapes)
    player.RenderShotgun();
    player.RenderPlayer();
    player.RenderDebugText(fixed_dt, dt);
    EndDrawing(); // Ends drawing
}