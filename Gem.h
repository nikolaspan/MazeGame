#ifndef GEM_H
#define GEM_H

#include "Position.h"

class Gem {
private:
 Position position;

public:
 Gem() {}

 void setPosition(int row, int col);
 Position getPosition() const;
};

#endif
