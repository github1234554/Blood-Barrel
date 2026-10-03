//=========================================
// ||               HEADERS              ||
//=========================================


#include <iostream>
#include <raylib.h> // The raylib library is a simple and easy-to-use library to enjoy videogames programming.
#include <vector>    // REQUIRED for std::vector inside your Bullet struct
#include <cmath>     // REQUIRED for M_PI, atan2, sin, and cos
#include <string>    // REQUIRED for std::to_string in your Render function
#include <algorithm> // REQUIRED for std::erase

using namespace std; // This line allows you to use standard library functions and objects without the std:: prefix.


//=========================================
//||   PRE STRUCT FUNCTION DECLARATIONS  ||
//=========================================

//Collision (active = emits ray, passive = receiving end of ray)
pair<float, Vector2> CheckCollision(const Rectangle& active, Vector2 velocity, float dt, const Rectangle& passive, bool IsLevelCollision = true);


// ==========================================
// ||               STRUCTS                ||
// ==========================================


//PLAYER STRUCT >>>
struct PlayerStats{
    //INITIALIZE PLAYER
    Vector2 position;
    float gravity = 0.0f; // Gravity (not used in this example)
    float gravityMod = 120.0f;// Gravity modifier
    
    //Temporary
    float radius = 30.0f; // Radius of the circle (player)

    //SHOTGUN PROPULSION
    float velocityX = 0.0f; // Velocity of the player in the X direction
    float angle = M_PI / 2;// Blast angle
    float blastPower = 2000.0f;// Blast power
    float blastXMod = 0.9f;// Blast modifier

    //Shape (temporary)
    float ShotgunWidth = 20.0f;
    float ShotgunHeight = radius + 20.0f;
    Rectangle shotgun;

    //Temporary floor
    Rectangle floor = {0.0f, float(GetScreenHeight()) - 300.0f, float(GetScreenWidth()) / 1.0f, float(GetScreenHeight() / 3.0f)};
    
    //COLLISION DETECTION
    float boxWH = (radius * 2.0f) / sqrt(2.0f);
    Rectangle collisionBox = {position.x - boxWH / 2, position.y - boxWH / 2, boxWH, boxWH};


    //UPDATE
    void Update(float dt, const Rectangle& level){
        //APPLYING MOVEMENT >>>
        gravity += gravityMod; // Increases gravity (not used in this example)

        float t = CheckCollision(collisionBox, {velocityX, gravity}, dt, level).first; // Checks for collision with the level
        float tInv = 1.0f - t; // Inverse of t (used for collision response)

        float collisionNormalX = CheckCollision(collisionBox, {velocityX, gravity}, dt, level).second.x; // Gets the collision normal in the X direction
        float collisionNormalY = CheckCollision(collisionBox, {velocityX, gravity}, dt, level).second.y; // Gets the collision normal in the Y direction

        const float epsilon = 0.1f; // Small value to prevent floating-point precision issues

        // Collision response>>>

        //Temporary material properties (dampening)
        float dampening = 0.5f;
        float friction = 0.8f;

        if (t < 1.0f) { // If there is a collision
            if (abs(collisionNormalX) > epsilon) {velocityX = -velocityX * dampening;} // Reflects the velocity in the X direction if there is a collision
            if (abs(collisionNormalY) > epsilon) {gravity = -gravity * dampening; velocityX = velocityX * friction;} // Reflects the gravity

            if (abs(gravity) < 300 && t <= epsilon) {gravity = 0;} // If the gravity is small enough, set it to 0 (not used in this example)

            position.y += gravity * tInv* dt; // Applies gravity to the player (not used in this example)
            position.x += velocityX * tInv * dt; // Applies velocity to the player
        }
        else{
            position.y += gravity * t * dt; // Applies gravity to the player (not used in this example)
            position.x += velocityX * t * dt; // Applies velocity to the player
        }
        
        shotgun = {position.x, position.y, ShotgunWidth, ShotgunHeight};
        collisionBox = {position.x - boxWH / 2, position.y - boxWH / 2, boxWH, boxWH};
    }

    void RenderPlayer()const{
        DrawCircleV(position, radius, MAROON); // Player
        //DrawRectangleRec(collisionBox, GREEN); // Collision box
    }

    void RenderShotgun(float angle)const{
        DrawRectanglePro(shotgun, {ShotgunWidth / 2, ShotgunHeight}, angle, BLUE);
    }
};


// ==========================================
// ||   POST STRUCTFUNCTION DECLARATIONS   ||
// ==========================================


//Utils
float Rad2Deg(float radians);

//Player
void ResetPlayer(PlayerStats& player);
void InputHandling(PlayerStats& player);

//Render
void Render(const PlayerStats& player, const Rectangle& level);


// ==========================================
// ||               MAIN LOGIC             ||
// ==========================================


int main(){

    // INITIALIZE WINDOW >>>
    InitWindow(1920, 1080, "GAME"); // Initializes a window low res
    SetTargetFPS(60); // Sets the target frames per second to 60

    //Spawn player
    PlayerStats player;
    ResetPlayer(player);

    //MAIN GAME LOOP >>>
    while(WindowShouldClose() == false){ // Main game loop, runs until the window is closed (close button or ESC key)
        // UPDATE
        player.angle = atan2((GetMouseY() - player.position.y), (player.position.x - GetMouseX()));
        float dt = GetFrameTime(); // Gets the time in seconds for the last frame drawn (delta time)

        InputHandling(player);
        
        player.Update(dt, player.floor);

        //Render
        Render(player, player.floor);

        
    }

    return 0;
}


//=========================================
// ||            FUNCTIONS               ||
//=========================================


float Rad2Deg(float radians){
    radians = (-radians * RAD2DEG) - 90;
    return radians;
}


//For testing (temporary)
void ResetPlayer(PlayerStats& player){
    player.position = {float(GetScreenWidth()) / 5.0f, float(GetScreenHeight()) / 5.0f};
    player.collisionBox = {player.position.x - player.boxWH / 2, player.position.y - player.boxWH / 2, player.boxWH, player.boxWH};
    player.gravity = 0.0f;
    player.velocityX = 0.0f;
    player.angle = M_PI / 2;
}


void InputHandling(PlayerStats& player){
        //RESET >>>
        if (IsKeyPressed(KEY_R)){
            ResetPlayer(player);
        }

        //SHOOT >>>
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){// Shotgun propulsion
            //Propel
            if (player.gravity < -600 && GetMouseY() > player.position.y){
                player.gravity += -player.blastPower * sin(player.angle) * 0.6;
            }
            else if(player.gravity > 0 && GetMouseY() < player.position.y){
                player.gravity += -player.blastPower * sin(player.angle) * 1.0;
            }
            else{
                player.gravity = -player.blastPower * sin(player.angle);
            }
            if ((player.velocityX > 400 && GetMouseX() < player.position.x) || (player.velocityX < -400 && GetMouseX() > player.position.x)){
                player.velocityX += player.blastPower * cos(player.angle) * player.blastXMod * 0.5;
            }
            else{
                player.velocityX = player.blastPower * cos(player.angle) * player.blastXMod;
            }
        }
}


pair<float, Vector2> CheckCollision(const Rectangle& active, Vector2 velocity, float dt, const Rectangle& passive, bool IsLevelCollision){
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
    float rayEndX = rayOriginX + velocity.x * dt;
    float rayEndY = rayOriginY + velocity.y * dt;

    float t1x = (minX - rayOriginX) / (velocity.x * dt);
    float t2x = (maxX - rayOriginX) / (velocity.x * dt);
    float t1y = (minY - rayOriginY) / (velocity.y * dt);
    float t2y = (maxY - rayOriginY) / (velocity.y * dt);

    float tminX = std::min(t1x, t2x);
    float tmaxX = std::max(t1x, t2x);
    float tminY = std::min(t1y, t2y);
    float tmaxY = std::max(t1y, t2y);

    float tFarEntry = std::max(tminX, tminY);
    float tNearExit = std::min(tmaxX, tmaxY);

    if (IsLevelCollision){
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
}


void Render(const PlayerStats& player, const Rectangle& level){
    //DRAW >>>
    BeginDrawing(); // Begins drawing

    //Background
    ClearBackground(RAYWHITE); // Clears the background with white color

    //Level (temporary)
    DrawRectangleRec(level, GRAY);

    //Textures (or temporary shapes)
    player.RenderShotgun(Rad2Deg(player.angle));
    player.RenderPlayer();

    //Text
    DrawText(TextFormat("%.2f, %.2f", player.position.x, player.position.y), 10, 10, 20, BLUE); // Debug text
    DrawText(TextFormat("%.2f", player.velocityX), 10, 40, 20, BLUE); // Debug text
    DrawText(TextFormat("%.2f", player.gravity), 10, 70, 20, BLUE); // Debug text

    EndDrawing(); // Ends drawing
}