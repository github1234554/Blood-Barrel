//=========================================
// ||               HEADERS              ||
//=========================================


#include <iostream>
#include <raylib.h> // The raylib library is a simple and easy-to-use library to enjoy videogames programming.
#include <vector>    // REQUIRED for std::vector inside your Bullet struct
#include <cmath>     // REQUIRED for M_PI, atan2, sin, and cos
#include <string>    // REQUIRED for std::to_string in your Render function
#include <algorithm> // REQUIRED for std::erase
#include <cassert>   // REQUIRED for assert

using namespace std; // This line allows you to use standard library functions and objects without the std:: prefix.


//=========================================
//||   PRE STRUCT FUNCTION DECLARATIONS  ||
//=========================================

//Collision (active = emits ray, passive = receiving end of ray)
pair<float, Vector2> CheckCollision(const Rectangle& active, Vector2 velocity, float dt, const Rectangle& passive, bool IsLevelCollision = true);


// ==========================================
// ||               STRUCTS                ||
// ==========================================

//ENTITY STRUCT >>>
struct Entity{
    protected:
        //Transform
        Vector2 position = {0.0f, 0.0f}; // Player position
        Vector2 velocity = {0.0f, 0.0f}; // Gravity (not used in this example)
        float gravityMod = 7000.0f;// Gravity modifier
        float t = 1.0f; // Time of collision (not used in this example)

        //Collision
        Vector2 CollisionBoxWH;
        Rectangle collisionBox;
    
    public:
        //Update transform and collision box
        void Update(float dt, const Rectangle& level){
            //APPLYING MOVEMENT >>>
            velocity.y += gravityMod * dt; // Increases gravity (not used in this example)

            pair<float, Vector2> checkCollisionResult = CheckCollision(collisionBox, velocity, dt, level);

            t = checkCollisionResult.first; // Checks for collision with the level
            float tInv = 1.0f - t; // Inverse of t (used for collision response)

            float collisionNormalX = checkCollisionResult.second.x; // Gets the collision normal in the X direction
            float collisionNormalY = checkCollisionResult.second.y; // Gets the collision normal in the Y direction

            const float epsilon = 0.001f; // Small value to prevent floating-point precision issues

            // Collision response>>>

            //Temporary material properties (dampening)
            float dampening = 0.5f;
            float friction = 0.8f;

            if (t < 1.0f) { // If there is a collision
                if (abs(collisionNormalX) > epsilon) {velocity.x = -velocity.x * dampening;} // Reflects the velocity in the X direction if there is a collision
                if (abs(collisionNormalY) > epsilon) {velocity.y = -velocity.y * dampening; velocity.x = velocity.x * friction;} // Reflects the gravity

                if (abs(velocity.y) < 300 && std::round(t * 10.0f) / 10.0f <= 0.8f) {velocity.y = 0;} // If the gravity is small enough, set it to 0 (not used in this example)
                std::cout << abs(velocity.y) << ", t: " << std::round(t * 10.0f) / 10.0f << std::endl; // Debugging line to check if the condition is true or false

                position.y += velocity.y * tInv* dt; // Applies gravity to the player (not used in this example)
                position.x += velocity.x * tInv * dt; // Applies velocity to the player
            }
            else{
                position.y += velocity.y * t * dt; // Applies gravity to the player (not used in this example)
                position.x += velocity.x * t * dt; // Applies velocity to the player
            }

            collisionBox = {position.x - CollisionBoxWH.x / 2, position.y - CollisionBoxWH.y / 2, CollisionBoxWH.x, CollisionBoxWH.y};
        }
};

//PLAYER STRUCT >>>
struct Player : public Entity{
    private:
        //Temporary
        float radius = 30.0f; // Radius of the circle (player)
        float ShotgunWidth = 20.0f;
        float ShotgunHeight = radius + 20.0f;
        Rectangle shotgun;
            
        float angle = 0.0f;// Blast angle
        float blastPower = 2000.0f;// Blast power
        float blastXMod = 0.9f;// Blast modifier

    public:
            
        //Temporary floor
        Rectangle floor = {0.0f, float(GetScreenHeight()) - 300.0f, float(GetScreenWidth()) / 1.0f, float(GetScreenHeight() / 3.0f)};

        void Reset(){
            position = {float(GetScreenWidth()) / 5.0f, float(GetScreenHeight()) - 400.0f};
            CollisionBoxWH = {(30.0f * 2.0f) / sqrt(2.0f), (30.0f * 2.0f) / sqrt(2.0f)}; // Collision box width and height (not used in this example)
            collisionBox = {position.x - CollisionBoxWH.x / 2, position.y - CollisionBoxWH.y / 2, CollisionBoxWH.x, CollisionBoxWH.y};
            velocity = {0.0f, 0.0f};
            angle = 0.0f;
        }

        void InputHandling(){

            angle = atan2(position.y - GetMouseY(), position.x - GetMouseX());
            shotgun = {position.x, position.y, ShotgunWidth, ShotgunHeight};

            //RESET >>>
            if (IsKeyPressed(KEY_R)){
                Reset();
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
                }
            }

            angle = angle * RAD2DEG - 90.0f; // Convert angle to degrees

        }

        void RenderDebugText()const{
            //Text
            DrawText(TextFormat("%.2f, %.2f", position.x, position.y), 10, 10, 20, BLUE); // Debug text
            DrawText(TextFormat("%.2f, %.2f", velocity.x, velocity.y), 10, 40, 20, BLUE); // Debug text
            DrawText(TextFormat("%.i", GetFPS()), 10, 70, 20, GREEN); // Debug text
        }

        void RenderPlayer()const{
            DrawCircleV(position, radius, MAROON); // Player
            //DrawRectangleRec(collisionBox, GREEN); // Collision box
        }

        void RenderShotgun()const{
            DrawRectanglePro(shotgun, {ShotgunWidth / 2, ShotgunHeight}, angle, BLUE);
        }
};


// ==========================================
// ||   POST STRUCTFUNCTION DECLARATIONS   ||
// ==========================================


//Utils
float Rad2Deg(float radians);

//Render
void Render(const Player& player, const Rectangle& level);


// ==========================================
// ||               MAIN LOGIC             ||
// ==========================================


int main(){

    // INITIALIZE WINDOW >>>
    InitWindow(1920, 1080, "GAME"); // Initializes a window low res
    SetTargetFPS(10000); // Sets the target frames per second to 60

    //Spawn player
    Player player;
    player.Reset();

    //MAIN GAME LOOP >>>
    while(WindowShouldClose() == false){ // Main game loop, runs until the window is closed (close button or ESC key)
        // Update
        float dt = GetFrameTime(); // Gets the time in seconds for the last frame drawn (delta time)

        player.InputHandling();

        player.Update(dt, player.floor);

        //Render
        Render(player, player.floor);

        
    }

    return 0;
}


//=========================================
// ||            FUNCTIONS               ||
//=========================================


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


void Render(const Player& player, const Rectangle& level){
    //DRAW >>>
    BeginDrawing(); // Begins drawing

    //Background
    ClearBackground(RAYWHITE); // Clears the background with white color

    //Level (temporary)
    DrawRectangleRec(level, GRAY);

    //Textures (or temporary shapes)
    player.RenderShotgun();
    player.RenderPlayer();
    player.RenderDebugText();
    EndDrawing(); // Ends drawing
}