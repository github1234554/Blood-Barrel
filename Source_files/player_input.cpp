#include "../Header_files/player.h"

#include <cmath>

using namespace std;

void Player::Reset(){
    position = {float(GetScreenWidth()) / 5.0f, float(GetScreenHeight()) - 400.0f};
    CollisionBoxWH = {(30.0f * 2.0f) / sqrt(2.0f), (30.0f * 2.0f) / sqrt(2.0f)}; // Collision box width and height (not used in this example)
    collisionBox = {position.x - CollisionBoxWH.x / 2, position.y - CollisionBoxWH.y / 2, CollisionBoxWH.x, CollisionBoxWH.y};
    velocity = {0.0f, 0.0f};
            angle = 0.0f;
}

void Player::InputHandling(float fixed_dt){

            angle = atan2(position.y - GetMouseY(), position.x - GetMouseX());

            //RESET >>>
            if (IsKeyPressed(KEY_R)){
                Reset();
            }

            if (IsKeyDown(KEY_A)){
                if (velocity.y == 0){
                    velocity.x = -speed;
                }
                else{
                    if (abs(ADspeed) <= 500) {ADspeed = -speed * 7.0f * fixed_dt;}
                    else {ADspeed = -500;}
                    velocity.x += ADspeed * fixed_dt;
                }
            }

            if (IsKeyDown(KEY_D)){
                if (velocity.y == 0){
                    velocity.x = speed;
                }
                else{
                    if (abs(ADspeed) <= 500) {ADspeed = speed * 7.0f * fixed_dt;}
                    else {ADspeed = 500;}
                    velocity.x += ADspeed * fixed_dt;
                }
            }

            //SHOOT >>>
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){// Shotgun propulsion
                //Propel
                if (velocity.y < -600 && GetMouseY() > position.y){
                    velocity.y += blastPower * sin(angle) * 0.6;
                }
                else if(velocity.y > 0 && GetMouseY() < position.y){
                    velocity.y += blastPower * sin(angle) * 1.0;
                }
                else{
                    velocity.y = blastPower * sin(angle);
                }
                if ((velocity.x > 400 && GetMouseX() < position.x) || (velocity.x < -400 && GetMouseX() > position.x)){
                    velocity.x += blastPower * cos(angle) * blastXMod * 0.5;
                }
                else{
                    velocity.x = blastPower * cos(angle) * blastXMod;
                    velocity.x += ADspeed * fixed_dt;
                }
            }

            angle = angle * RAD2DEG - 90.0f; // Convert angle to degrees

}