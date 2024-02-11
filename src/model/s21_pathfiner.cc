#include "s21_pathfiner.h"

#include <algorithm>

bool s21::PathFinder::IsCanMoveLeft() {
  bool result = true;
  if ((current_.second - 1) < 0 ||
      visited_[current_.first][current_.second - 1] ||
      IsRightWall(current_.first, current_.second - 1))
    result = false;
  return result;
}

bool s21::PathFinder::IsCanMoveRight() {
  bool result = true;
  if ((current_.second + 1) >= cols_ ||
      visited_[current_.first][current_.second + 1] ||
      IsRightWall(current_.first, current_.second))
    result = false;
  return result;
}

bool s21::PathFinder::IsCanMoveUp() {
  bool result = true;
  if ((current_.first - 1) < 0 ||
      visited_[current_.first - 1][current_.second] ||
      IsBottomWall(current_.first - 1, current_.second))
    result = false;
  return result;
}

bool s21::PathFinder::IsCanMoveDown() {
  bool result = true;
  if ((current_.first + 1) >= rows_ ||
      visited_[current_.first + 1][current_.second] ||
      IsBottomWall(current_.first, current_.second))
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
  start.first = std::clamp(start.first, 0, rows_ - 1);
  start.second = std::clamp(start.second, 0, cols_ - 1);
  end.first = std::clamp(end.first, 0, rows_ - 1);
  end.second = std::clamp(end.second, 0, cols_ - 1);

  visited_[start.first][start.second] = 1;
  path_.push(start);
  while (!path_.empty()) {
    current_ = path_.top();
    if (current_ == end) {
      break;
    }
    if (IsCanMoveLeft()) {
      path_.push({current_.first, current_.second - 1});
      visited_[current_.first][current_.second - 1] = 1;
    } else if (IsCanMoveRight()) {
      path_.push({current_.first, current_.second + 1});
      visited_[current_.first][current_.second + 1] = 1;
    } else if (IsCanMoveUp()) {
      path_.push({current_.first - 1, current_.second});
      visited_[current_.first - 1][current_.second] = 1;
    } else if (IsCanMoveDown()) {
      path_.push({current_.first + 1, current_.second});
      visited_[current_.first + 1][current_.second] = 1;
    } else {
      path_.pop();
    }
  }
  return path_;
}

s21::PathFinder::PathFinder(std::vector<bool> r_walls,
                            std::vector<bool> b_walls, int rows, int cols)
    : r_walls_(r_walls),
      b_walls_(b_walls),
      rows_(std::clamp(rows, 1, 50)),
      cols_(std::clamp(cols, 1, 50)),
      visited_(std::clamp(rows, 1, 50),
               std::vector<int>(std::clamp(cols, 1, 50), 0)) {}
