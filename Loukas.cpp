#include "Loukas.h"
#include <cstdlib>
#include "Constants.h"

void Loukas::setGemPosition(const Position& pos) {
 gemPos = pos;
}

void Loukas::move(const std::vector<std::string>& maze) {
 // Get current position
 int row = position.row;
 int col = position.col;

 // Calculate Manhattan distances to the gem
 int upDistance = abs(row - 1 - gemPos.row) + abs(col - gemPos.col);
 int downDistance = abs(row + 1 - gemPos.row) + abs(col - gemPos.col);
 int leftDistance = abs(row - gemPos.row) + abs(col - 1 - gemPos.col);
 int rightDistance = abs(row - gemPos.row) + abs(col + 1 - gemPos.col);

 // Find the minimum distance
 int minDistance = std::min(std::min(upDistance, downDistance), std::min(leftDistance, rightDistance));

 // Move towards the gem
 if (upDistance == minDistance && maze[row - 1][col] == CORRIDOR_CHAR) {
 row--;
 } else if (downDistance == minDistance && maze[row + 1][col] == CORRIDOR_CHAR) {
 row++;
 } else if (leftDistance == minDistance && maze[row][col - 1] == CORRIDOR_CHAR) {
 col--;
 } else if (rightDistance == minDistance && maze[row][col + 1] == CORRIDOR_CHAR) {
 col++;
 }

 // Update position
 position.row = row;
 position.col = col;
}
