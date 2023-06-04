#ifndef MPAMPIS_H
#define MPAMPIS_H

#include "Player.h"

class Mpampis : public Player {
public:
 void move(const std::vector<std::string>& maze) override;
};

#endif
