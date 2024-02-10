#include "s21_pathfiner.h"

bool s21::PathFinder::IsCanMoveLeft() {
  bool result = true;
  if ((current.second - 1) < 0 || visited_[current.first][current.second - 1] ||
      IsRightWall(current.first, current.second - 1))
    result = false;
  return result;
}

bool s21::PathFinder::IsCanMoveRight() {
  bool result = true;
  if ((current.second + 1) >= cols_ ||
      visited_[current.first][current.second + 1] ||
      IsRightWall(current.first, current.second))
    result = false;
  return result;
}

bool s21::PathFinder::IsCanMoveUp() {
  bool result = true;
  if ((current.first - 1) < 0 || visited_[current.first - 1][current.second] ||
      IsBottomWall(current.first - 1, current.second))
    result = false;
  return result;
}

bool s21::PathFinder::IsCanMoveDown() {
  bool result = true;
  if ((current.first + 1) >= rows_ ||
      visited_[current.first + 1][current.second] ||
      IsBottomWall(current.first, current.second))
    result = false;
  return result;
}

bool s21::PathFinder::IsBottomWall(int r, int c) {
  return b_walls_[r * cols_ + c];
}

bool s21::PathFinder::IsRightWall(int r, int c) {
  return r_walls_[r * cols_ + c];
}

stack<pair<int, int>> s21::PathFinder::FindPath(pair<int, int> start,
                                                pair<int, int> end) {
  visited_[start.first][start.second] = 1;
  path.push(start);
  while (!path.empty()) {
    current = path.top();
    if (current == end) {
      break;
    }
    if (IsCanMoveLeft()) {
      path.push({current.first, current.second - 1});
      visited_[current.first][current.second - 1] = 1;
    } else if (IsCanMoveRight()) {
      path.push({current.first, current.second + 1});
      visited_[current.first][current.second + 1] = 1;
    } else if (IsCanMoveUp()) {
      path.push({current.first - 1, current.second});
      visited_[current.first - 1][current.second] = 1;
    } else if (IsCanMoveDown()) {
      path.push({current.first + 1, current.second});
      visited_[current.first + 1][current.second] = 1;
    } else {
      path.pop();
    }
  }
  return path;
}

s21::PathFinder::PathFinder(std::vector<bool> r_walls,
                            std::vector<bool> b_walls, int rows, int cols)
    : r_walls_(r_walls),
      b_walls_(b_walls),
      rows_(rows),
      cols_(cols),
      visited_(rows, std::vector<int>(cols, 0)) {}
