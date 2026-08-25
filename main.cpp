#include <iostream>
#include <raylib.h> // The raylib library is a simple and easy-to-use library to enjoy videogames programming.

int main(){

    // INITIALIZE WINDOW
    InitWindow(1680, 1050, "Player"); // Initializes a window
    SetTargetFPS(60); // Sets the target frames per second to 60

    //INITIALIZE PLAYER
    Vector2 playerPosition = {float(GetScreenWidth()) / 5.0f, float(GetScreenHeight()) / 5.0f}; // Position of the player
    float speed = 200.0f; // Speed of the player
    float gravity = 0.0f; // Gravity (not used in this example)
    float gravityMod = 1500.0f;// Gravity modifier

    float radius = 30.0f; // Radius of the circle (player)

    // SHOTGUN PROPULSION
    float velocityX = 0.0f; // Velocity of the player in the X direction
    float angle = M_PI / 2;// Blast angle
    float blastPower = 860.0f;// Blast power
    float blastXMod = 0.7f;// Blast modifier
    
    //INITIALIZE FLOOR
    float floorLevel = GetScreenHeight() - (GetScreenHeight() / 5.0f) - radius;

    std::string mouseX;
    std::string mouseY;

    //MAIN GAME LOOP
    while(WindowShouldClose() == false){ // Main game loop, runs until the window is closed (close button or ESC key)
        // UPDATE
        float dt = GetFrameTime(); // Gets the time in seconds for the last frame drawn (delta time)

        //Reset
        if (IsKeyPressed(KEY_R)){
            playerPosition = {float(GetScreenWidth()) / 5.0f, float(GetScreenHeight()) / 5.0f};
            gravity = 0.0f;
            velocityX = 0.0f;
            angle = M_PI / 2;
        }

        // Propell
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){// Shotgun propulsion
            angle = atan2((GetMouseY() - playerPosition.y), (playerPosition.x - GetMouseX()));
            if (angle > 0){
                gravity = -blastPower * sin(angle);
            }
            else{
                gravity += -blastPower * sin(angle);
            }
            if ((velocityX > 0 && GetMouseX() < playerPosition.x) || (velocityX < 0 && GetMouseX() > playerPosition.x)){
                velocityX += blastPower * cos(angle) * blastXMod * 0.2;
            }
            else{
                velocityX = blastPower * cos(angle) * blastXMod;
            }
        }

        std::string mouseX = std::to_string(GetMouseX());
        std::string mouseY = std::to_string(GetMouseY());
        
        //APPLYING MOVEMENT
        if (playerPosition.y + gravity * dt >= floorLevel) { // If player will hit floor level next update ( or slightly below due to update priorities)
            playerPosition.y = floorLevel; // Set player back to floor level
            gravity = 0.0f; // Resets gravity
            if ( ! ((velocityX < 5.0f) && (velocityX > -5.0f))){
                velocityX = velocityX * 56 * dt; // Applies friction to the player (not used in this example)
            }
            else{
                velocityX = 0.0f;
            }
        }
        else{
            gravity += gravityMod * dt; // Increases gravity (not used in this example)
            playerPosition.y += gravity * dt; // Applies gravity to the player (not used in this example)
        }

        playerPosition.x += velocityX * dt; // Applies velocity to the player

        // RENDERING
        BeginDrawing(); // Begins drawing
        ClearBackground(RAYWHITE); // Clears the background with white color
        DrawCircleV(playerPosition, radius, MAROON); // Player
        DrawText((mouseX + ", " + mouseY).c_str(), 10, 10, 20, BLACK); // Debug text
        DrawText(std::to_string(angle).c_str(), 10, 30, 20, BLUE); // Debug text
        EndDrawing(); // Ends drawing
    }

    return 0;
}