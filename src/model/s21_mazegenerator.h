#ifndef S21_MAZE_MAZEGENERATOR_H
#define S21_MAZE_MAZEGENERATOR_H

#include <map>

#include "s21_maze.h"

namespace s21 {

class Maze;

class MazeGenerator {
 public:
  Maze GenerateMaze(int width, int height, bool debug, int seed);

 private:
  std::vector<std::vector<int>> right_walls_;
  std::vector<std::vector<int>> bottom_walls_;
  std::vector<int> row_sets_;
  int cols_;
  int rows_;
  int next_set_id_;
  int current_row_index_;
  void MarkupCells();
  void PlaceRightWalls();
  void PlaceBottomWalls();
  void ShowNewRow();
  bool IsRightWall(int m, int n) { return right_walls_[m][n] == 1; }
  bool IsBottomWall(int m, int n) { return bottom_walls_[m][n] == 1; }
};
}  // namespace s21
#endif  // S21_MAZE_MAZEGENERATOR_H
