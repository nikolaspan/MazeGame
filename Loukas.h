#ifndef LOUKAS_H
#define LOUKAS_H

#include "Player.h"
#include "Position.h"

class Loukas : public Player {
private:
 Position gemPos;

public:
 void setGemPosition(const Position& pos);
 void move(const std::vector<std::string>& maze) override;
};

#endif
