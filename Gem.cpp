#include "Gem.h"

void Gem::setPosition(int row, int col) {
 position.row = row;
 position.col = col;
}

Position Gem::getPosition() const {
 return position;
}
