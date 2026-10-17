#include "../Header_files/entity.h"
#include "../Header_files/physics.h"

#include <raylib.h>
#include <utility>
#include <vector>

using namespace std;

void Entity::Update(float fixed_dt, const Rectangle& level){
            //APPLYING MOVEMENT >>>
            velocity.y += gravityMod * fixed_dt; // Increases gravity (not used in this example)

            pair<float, Vector2> checkCollisionResult = CheckCollision(collisionBox, velocity, fixed_dt, level);

            t = checkCollisionResult.first; // Checks for collision with the level
            float tInv = 1.0f - t; // Inverse of t (used for collision response)

            float collisionNormalX = checkCollisionResult.second.x; // Gets the collision normal in the X direction
            float collisionNormalY = checkCollisionResult.second.y; // Gets the collision normal in the Y direction

            const float epsilon = 0.001f; // Small value to prevent floating-point precision issues

            // Collision response>>>

            //Temporary material properties (dampening)
            float dampening = 0.5f;
            float surface_smoothness = 0.9f;

            position.y += velocity.y * t * fixed_dt; // Applies gravity to the player (not used in this example)
            position.x += velocity.x * t * fixed_dt; // Applies velocity to the player

            if (abs(collisionNormalX) > epsilon) {velocity.x = -velocity.x * dampening;} // Reflects the velocity in the X direction if there is a collision
            if (abs(collisionNormalY) > epsilon) {velocity.y = -velocity.y * dampening; velocity.x = velocity.x * surface_smoothness;} // Reflects the gravity and applies friction

            if(! (t < 1.0f && velocity.y > -300.0f)) {position.y += velocity.y * tInv * fixed_dt;} // Applies gravity to the player (not used in this example)
            else {velocity.y = 0.0f;} // Stops the player from falling if there is a collision

            if (! (velocity.y == 0.0f && abs(velocity.x) < 10.0f)) {position.x += velocity.x * tInv * fixed_dt;} // Applies velocity to the player
            else {velocity.x = 0.0f;} // Stops the player from moving if there is a collision

            collisionBox = {position.x - CollisionBoxWH.x / 2, position.y - CollisionBoxWH.y / 2, CollisionBoxWH.x, CollisionBoxWH.y};
        }