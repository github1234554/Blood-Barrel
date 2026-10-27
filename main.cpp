#include <raylib.h> // The raylib library is a simple and easy-to-use library to enjoy videogames programming.

#include "Header_files/entity.h" // Include the entity.h header file that contains the definition of the Entity struct and its derived Player struct
#include "Header_files/player.h" // Include the player.h header file that contains the definition of the Player struct and its member functions

#include "Header_files/render.h" // Include the render.h header file that contains the declaration of the Render function

using namespace std; // This line allows you to use standard library functions and objects without the std:: prefix.


int main(){

    // INITIALIZE WINDOW >>>
    InitWindow(1680, 1050, "GAME"); // Initializes a window low res
    SetTargetFPS(2000); // Sets the target frames per second to 75

    float fixed_dt = 1.0f / 240.0f; // Fixed delta time for physics updates
    float dt;
    float accumulator = 0.0f; // Accumulator for fixed time step

    //Spawn player
    Player player;
    player.Reset(true);// Initializes the player position, collision box, and velocity

    //MAIN GAME LOOP >>>
    while(WindowShouldClose() == false){ // Main game loop, runs until the window is closed (close button or ESC key)
        // Fixed Delta Time
        dt = GetFrameTime(); // Get the time elapsed since the last frame

        if (dt > 0.25f) {dt = 0.25f;} // Clamp dt to avoid spiral of death
        
        accumulator += dt;
        
        while (accumulator >= fixed_dt) {
            accumulator -= fixed_dt; // Decrease accumulator by fixed_dt
            player.Update(fixed_dt, player.floor);
        }

        player.InputHandling(fixed_dt);
        player.UpdateShotgunPosition();

        //Render
        Render(player, player.floor, player.floor2, fixed_dt, dt);

        
    }

    return 0;
}