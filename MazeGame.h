#ifndef MAZEGAME_H
#define MAZEGAME_H

#include <vector>
#include <string>
#include <chrono>
#include "Mpampis.h"
#include "Loukas.h"
#include "Gem.h"

class MazeGame {
private:
 std::vector<std::string> maze;
 Mpampis player1;
 Loukas player2;
 Gem gem;
 int turnCounter;
 bool gameOver;
 std::chrono::steady_clock::time_point lastGemRefreshTime;

public:
 MazeGame(const std::string& mazeFile);

 void loadMazeFromFile(const std::string& mazeFile);
 void initializePlayersAndGem();
 void drawMaze();
 void drawPlayersAndGem();
 void repositionGem();
 void checkGemCollected();
 void play();
};

#endif
