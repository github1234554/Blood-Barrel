#include <iostream>
#include <raylib.h> // The raylib library is a simple and easy-to-use library to enjoy videogames programming.

int main(){

    // Initialization of the window
    InitWindow(1680, 1050, "Player"); // Initializes a window
    SetTargetFPS(60); // Sets the target frames per second to 60

    Vector2 playerPosition = {float(GetScreenWidth()) / 5.0f, float(GetScreenHeight()) / 5.0f}; // Position of the circle
    float speed = 200.0f; // Speed of the circle
    float gravity = 0.0f; // Gravity (not used in this example)
    float gravityMod = 18.0f;// Gravity modifier
    float radius = 30.0f; // Radius of the circle

    float velocityX = 0.0f; // Velocity of the circle in the X direction
    float angle = M_PI / 2;// Blast angle
    float blastPower = 630.0f;// Blast power
    
    float floorLevel = GetScreenHeight() - (GetScreenHeight() / 5.0f) - radius;

    std::string mouseX;
    std::string mouseY;

    while(WindowShouldClose() == false){ // Main game loop, runs until the window is closed (close button or ESC key)
        //Update

        if (IsKeyPressed(KEY_R)){
            playerPosition = {float(GetScreenWidth()) / 5.0f, float(GetScreenHeight()) / 5.0f};
            gravity = 0.0f;
            velocityX = 0.0f;
            angle = M_PI / 2;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){// Shotgun propulsion
            angle = atan2((GetMouseY() - playerPosition.y), (playerPosition.x - GetMouseX()));
            if (angle > 0){
                gravity = -blastPower * sin(angle);
            }
            else{
                gravity += -blastPower * sin(angle);
            }
            if ((velocityX > 0 && cos(angle) >= 0) || (velocityX < 0 && cos(angle) <= 0)){
                velocityX += blastPower * cos(angle) * 0.2;
            }
            else{
                velocityX = blastPower * cos(angle);
            }
        }

        std::string mouseX = std::to_string(GetMouseX());
        std::string mouseY = std::to_string(GetMouseY());
        
        if (playerPosition.y + gravity * GetFrameTime() >= floorLevel) { // If player will hit floor level next update ( or slightly below due to update priorities)
            playerPosition.y = floorLevel; // Set player back to floor level
            gravity = 0.0f; // Resets gravity
            if ( ! ((velocityX < 5.0f) && (velocityX > -5.0f))){
                velocityX = velocityX * 0.97;
            }
            else{
                velocityX = 0.0f;
            }
        }
        else{
            gravity += gravityMod; // Increases gravity (not used in this example)
            playerPosition.y += gravity * GetFrameTime(); // Applies gravity to the circle (not used in this example)
        }

        playerPosition.x += velocityX * GetFrameTime(); // Applies velocity to the circle

        //Rendering
        BeginDrawing(); // Begins drawing
        ClearBackground(RAYWHITE); // Clears the background with white color
        DrawCircleV(playerPosition, radius, MAROON); // Player
        DrawText((mouseX + ", " + mouseY).c_str(), 10, 10, 20, BLACK); // Instructions
        DrawText(std::to_string(cos(angle)).c_str(), 10, 30, 20, BLUE); // Instructions
        EndDrawing(); // Ends drawing
    }

    return 0;
}