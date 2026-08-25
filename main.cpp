#include <iostream>
#include <raylib.h> // The raylib library is a simple and easy-to-use library to enjoy videogames programming.

//
struct PlayerSettings{
    //INITIALIZE PLAYER
    Vector2 position;
    float speed = 200.0f; // Speed of the player
    float gravity = 0.0f; // Gravity (not used in this example)
    float gravityMod = 1500.0f;// Gravity modifier
    
    //Temporary
    float radius = 30.0f; // Radius of the circle (player)

    // SHOTGUN PROPULSION
    float velocityX = 0.0f; // Velocity of the player in the X direction
    float angle = M_PI / 2;// Blast angle
    float blastPower = 860.0f;// Blast power
    float blastXMod = 0.7f;// Blast modifier
};

//For testing (temporary)
void ResetPlayer(PlayerSettings& player){
    player.position = {float(GetScreenWidth()) / 5.0f, float(GetScreenHeight()) / 5.0f};
    player.gravity = 0.0f;
    player.velocityX = 0.0f;
    player.angle = M_PI / 2;
}

void InputHandling(PlayerSettings& player){
    //Reset
        if (IsKeyPressed(KEY_R)){
            ResetPlayer(player);
        }

        // Propell
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){// Shotgun propulsion
            player.angle = atan2((GetMouseY() - player.position.y), (player.position.x - GetMouseX()));
            if (player.gravity < -450 && GetMouseY() > player.position.y){
                player.gravity += -player.blastPower * sin(player.angle) * 0.4;
            }
            else if(player.gravity > 0 && GetMouseY() < player.position.y){
                player.gravity += -player.blastPower * sin(player.angle) * 0.6;
            }
            else{
                player.gravity = -player.blastPower * sin(player.angle);
            }
            if ((player.velocityX > 0 && GetMouseX() < player.position.x) || (player.velocityX < 0 && GetMouseX() > player.position.x)){
                player.velocityX += player.blastPower * cos(player.angle) * player.blastXMod * 0.2;
            }
            else{
                player.velocityX = player.blastPower * cos(player.angle) * player.blastXMod;
            }
        }
}

void UpdatePlayerPhysics(PlayerSettings& player, float floorLevel, float dt){
    //APPLYING MOVEMENT
        if (player.position.y + player.gravity * dt >= floorLevel) { // If player will hit floor level next update ( or slightly below due to update priorities)
            player.position.y = floorLevel; // Set player back to floor level
            player.gravity = 0.0f; // Resets gravity
            if ( ! ((player.velocityX < 5.0f) && (player.velocityX > -5.0f))){
                player.velocityX = player.velocityX * 56 * dt; // Applies friction to the player (not used in this example)
            }
            else{
                player.velocityX = 0.0f;
            }
        }
        else{
            player.gravity += player.gravityMod * dt; // Increases gravity (not used in this example)
            player.position.y += player.gravity * dt; // Applies gravity to the player (not used in this example)
        }

        player.position.x += player.velocityX * dt; // Applies velocity to the player
}

void Render(const PlayerSettings& player){
    BeginDrawing(); // Begins drawing
    ClearBackground(RAYWHITE); // Clears the background with white color
    DrawCircleV(player.position, player.radius, MAROON); // Player
    DrawText(std::to_string(player.velocityX).c_str(), 10, 10, 20, BLUE); // Debug text
    EndDrawing(); // Ends drawing
}

int main(){

    // INITIALIZE WINDOW
    InitWindow(1680, 1050, "Player"); // Initializes a window
    SetTargetFPS(60); // Sets the target frames per second to 60

    PlayerSettings player;
    ResetPlayer(player);

    //INITIALIZE FLOOR
    float floorLevel = GetScreenHeight() - (GetScreenHeight() / 5.0f) - player.radius;

    //MAIN GAME LOOP
    while(WindowShouldClose() == false){ // Main game loop, runs until the window is closed (close button or ESC key)
        // UPDATE
        float dt = GetFrameTime(); // Gets the time in seconds for the last frame drawn (delta time)

        InputHandling(player);
        UpdatePlayerPhysics(player, floorLevel, dt);
        Render(player);
        
    }

    return 0;
}