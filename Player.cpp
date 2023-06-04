#include "Player.h"

void Player::setPosition(int row, int col) {
 position.row = row;
 position.col = col;
}

Position Player::getPosition() const {
 return position;
}
