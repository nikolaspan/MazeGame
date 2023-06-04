#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Position.h"

class Player {
protected:
 Position position;

public:
 Player() {}

 void setPosition(int row, int col);
 Position getPosition() const;

 virtual void move(const std::vector<std::string>& maze) = 0;
};

#endif
