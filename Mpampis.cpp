#include "Mpampis.h"
#include <ncurses.h>
#include "Constants.h"

void Mpampis::move(const std::vector<std::string>& maze) {
 // Get current position
 int row = position.row;
 int col = position.col;

 // Get user input
 int ch = getch();
 switch (ch) {
 case KEY_UP:
 row--;
 break;
 case KEY_DOWN:
 row++;
 break;
 case KEY_LEFT:
 col--;
 break;
 case KEY_RIGHT:
 col++;
 break;
 }

 // Check if the new position is valid (not a wall)
 if (maze[row][col] == CORRIDOR_CHAR) {
 // Update position
 position.row = row;
 position.col = col;
 }
}
