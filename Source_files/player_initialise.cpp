#include "../Header_files/player.h"

void Player::UpdateShotgunPosition() {
    shotgun = {position.x, position.y, ShotgunWidth, ShotgunHeight};
}