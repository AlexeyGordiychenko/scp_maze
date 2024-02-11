#ifndef S21_PATHFINDER_H
#define S21_PATHFINDER_H

#include <stack>
#include <utility>
#include <vector>

#include "s21_maze.h"

using namespace std;

namespace s21 {

class PathFinder {
 public:
  std::stack<pair<int, int>> FindPath(pair<int, int> start, pair<int, int> end);
  PathFinder(std::vector<bool> r_walls_, std::vector<bool> b_walls_, int rows_,
             int cols_);

 private:
  bool IsCanMoveLeft();
  bool IsCanMoveRight();
  bool IsCanMoveUp();
  bool IsCanMoveDown();
  bool IsBottomWall(int r, int c);
  bool IsRightWall(int r, int c);

  stack<pair<int, int>> path_;
  pair<int, int> current_;
  std::vector<bool> r_walls_, b_walls_;
  int rows_, cols_;
  std::vector<std::vector<int>> visited_;
};
}  // namespace s21
#endif  // S21_PATHFINDER_H
