#include <iostream>
#include "MazeGame.h"

int main(int argc, char* argv[]) {
 if (argc != 2) {
 std::cout << "Usage: maze_game <maze_file>" << std::endl;
 return 1;
 }

 MazeGame game(argv[1]);
 game.play();

 return 0;
}
