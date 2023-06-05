#include "MazeGame.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "Constants.h"
#include<iostream>

MazeGame::MazeGame(const std::string& mazeFile) : turnCounter(1), gameOver(false) {
 loadMazeFromFile(mazeFile);
 initializePlayersAndGem();
 lastGemRefreshTime = std::chrono::steady_clock::now();
}

void MazeGame::loadMazeFromFile(const std::string& mazeFile) {
 std::ifstream file(mazeFile);
 if (!file.is_open()) {
 std::cerr << "Error: Failed to open maze file: " << mazeFile << std::endl;
 exit(1);
 }

 std::string line;
 while (std::getline(file, line)) {
 maze.push_back(line);
 }

 if (maze.empty()) {
 std::cerr << "Error: Maze file is empty: " << mazeFile << std::endl;
 exit(1);
 }
}

void MazeGame::initializePlayersAndGem() {
 std::srand(std::time(nullptr));

 // Place Player 1 randomly
 Position p1Pos;
 do {
 p1Pos.row = std::rand() % maze.size();
 p1Pos.col = std::rand() % maze[0].size();
 } while (maze[p1Pos.row][p1Pos.col] != CORRIDOR_CHAR);
 player1.setPosition(p1Pos.row, p1Pos.col);

 // Place Player 2 randomly, avoiding the same position as Player 1
 Position p2Pos;
 do {
 p2Pos.row = std::rand() % maze.size();
 p2Pos.col = std::rand() % maze[0].size();
 } while (maze[p2Pos.row][p2Pos.col] != CORRIDOR_CHAR ||
 (p2Pos.row == p1Pos.row && p2Pos.col == p1Pos.col));
 player2.setPosition(p2Pos.row, p2Pos.col);

 // Place the gem randomly
 Position gemPos;
 do {
 gemPos.row = std::rand() % maze.size();
 gemPos.col = std::rand() % maze[0].size();
 } while (maze[gemPos.row][gemPos.col] != CORRIDOR_CHAR);
 gem.setPosition(gemPos.row, gemPos.col);
 player2.setGemPosition(gemPos); // Update the position of the gem for Player 2
}

void MazeGame::drawMaze() {
 clear();
 for (const auto& row : maze) {
 printw("%s\n", row.c_str());
 }
}

void MazeGame::drawPlayersAndGem() {
 if (has_colors() == TRUE) {
 start_color();
 init_pair(1, COLOR_GREEN, COLOR_BLACK);
 init_pair(2, COLOR_RED, COLOR_BLACK);
 init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

 attron(COLOR_PAIR(1));
 mvaddch(player2.getPosition().row, player2.getPosition().col, PLAYER2_CHAR);
 attroff(COLOR_PAIR(1));

 attron(COLOR_PAIR(2));
 mvaddch(player1.getPosition().row, player1.getPosition().col, PLAYER1_CHAR);
 attroff(COLOR_PAIR(2));

 attron(COLOR_PAIR(3));
 mvaddch(gem.getPosition().row, gem.getPosition().col, GEM_CHAR);
 attroff(COLOR_PAIR(3));
 } else {
 mvaddch(player1.getPosition().row, player1.getPosition().col, PLAYER1_CHAR);
 mvaddch(player2.getPosition().row, player2.getPosition().col, PLAYER2_CHAR);
 mvaddch(gem.getPosition().row, gem.getPosition().col, GEM_CHAR);
 }
}



void MazeGame::repositionGem() {
 Position newPos;
 do {
 newPos.row = std::rand() % maze.size();
 newPos.col = std::rand() % maze[0].size();
 } while (maze[newPos.row][newPos.col] != CORRIDOR_CHAR);
 gem.setPosition(newPos.row, newPos.col);
 player2.setGemPosition(newPos);
}

void MazeGame::checkGemCollected() {
 if (player1.getPosition().row == gem.getPosition().row && player1.getPosition().col == gem.getPosition().col) {
 gameOver = true;
 mvprintw(maze.size() + 1, 0, "Player 1 collected the gem! Game over.");
 } else if (player2.getPosition().row == gem.getPosition().row && player2.getPosition().col == gem.getPosition().col) {
 gameOver = true;
 mvprintw(maze.size() + 1, 0, "Player 2 collected the gem! Game over.");
 }
}

void MazeGame::play() {
 initscr();
 noecho();
 keypad(stdscr, TRUE);

 while (!gameOver) {
 drawMaze();
 drawPlayersAndGem();
 refresh();

 if (turnCounter % 2 != 0) {
 player1.move(maze);
 } else {
 player2.move(maze);
 }

 checkGemCollected();

 // Refresh the gem every 10 seconds
 auto currentTime = std::chrono::steady_clock::now();
 std::chrono::duration<double> elapsedSeconds = currentTime - lastGemRefreshTime;
 if (elapsedSeconds.count() >= 10.0) {
 repositionGem();
 lastGemRefreshTime = currentTime;
 }

 turnCounter++;

 // Check if the user pressed the ESC key
 if (getch() == 27) {
 gameOver = true;
 mvprintw(maze.size() + 1, 0, "Game over. You pressed the ESC key.");
 }
 }

 getch();
 endwin();
}
