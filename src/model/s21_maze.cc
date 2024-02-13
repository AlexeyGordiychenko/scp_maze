#include "s21_maze.h"

#include <algorithm>
#include <map>
#include <tuple>

s21::Maze::Maze(bool is_empty, int rows, int cols,
                const std::vector<bool> r_walls,
                const std::vector<bool> b_walls)
    : s21::Labyrinth(is_empty, rows, cols),
      r_walls_(r_walls),
      b_walls_(b_walls) {}

void s21::Maze::Initialize(const std::string filename) {
  ClearData();
  std::tie(rows_, cols_) = ParseFile(filename, "maze", r_walls_, b_walls_);
  is_empty_ = false;
}

bool s21::Maze::Empty() const { return is_empty_; }

void s21::Maze::ClearData() {
  r_walls_.clear();
  b_walls_.clear();
  is_empty_ = true;
}

int s21::Maze::GetRows() const { return rows_; }
int s21::Maze::GetCols() const { return cols_; }
const std::vector<bool>& s21::Maze::GetRWalls() const { return r_walls_; }
const std::vector<bool>& s21::Maze::GetBWalls() const { return b_walls_; }

void s21::Maze::Save(const std::string filename) {
  SaveToFile(filename, rows_, cols_, r_walls_, b_walls_);
}

void s21::Maze::GenerateMaze(int cols, int rows, bool debug, int seed) {
  cols = std::clamp(cols, 1, 50);
  rows = std::clamp(rows, 1, 50);
  srand(seed);
  this->cols_ = cols;
  this->rows_ = rows;
  next_set_id_ = 1;
  right_walls_ = std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
  bottom_walls_ =
      std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0));
  row_sets_ = std::vector<int>(cols, 0);
  for (current_row_index_ = 0; current_row_index_ < rows;
       current_row_index_++) {
    MarkupCells();
    PlaceRightWalls();
    PlaceBottomWalls();
    if (debug) ShowNewRow();
  }

  std::vector<bool> r_walls, b_walls;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      r_walls.push_back(right_walls_[i][j] == 1);
      b_walls.push_back(bottom_walls_[i][j] == 1);
    }
  }

  this->r_walls_ = r_walls;
  this->b_walls_ = b_walls;
  this->is_empty_ = false;
}

void s21::Maze::PlaceRightWalls() {
  for (int i = 0; i < cols_; i++) {
    if (i == cols_ - 1) {
      right_walls_[current_row_index_][i] = 1;
    } else if (row_sets_[i] == row_sets_[i + 1]) {
      right_walls_[current_row_index_][i] = 1;
    } else if (rand() > RAND_MAX / 2) {
      right_walls_[current_row_index_][i] = 1;
    } else {
      int old_set_id = row_sets_[i];
      for (int j = 0; j < cols_; j++) {
        if (row_sets_[j] == old_set_id) {
          row_sets_[j] = row_sets_[i + 1];
        }
      }
    }
  }
  if (current_row_index_ == rows_ - 1) {
    for (int i = 0; i < cols_ - 1; i++) {
      if (row_sets_[i] != row_sets_[i + 1]) {
        right_walls_[current_row_index_][i] = 0;
        int old_set_id = row_sets_[i];
        for (int j = 0; j < cols_; j++) {
          if (row_sets_[j] == old_set_id) {
            row_sets_[j] = row_sets_[i + 1];
          }
        }
      }
    }
  }
}

void s21::Maze::PlaceBottomWalls() {
  std::map<int, int> set_size;
  for (int i = 0; i < cols_; i++) {
    set_size[row_sets_[i]] += 1;
  }
  for (int i = 0; i < cols_; i++) {
    if (rand() > (RAND_MAX / 2) && set_size[row_sets_[i]] > 1) {
      bottom_walls_[current_row_index_][i] = 1;
      set_size[row_sets_[i]] -= 1;
    } else if (current_row_index_ == rows_ - 1) {
      bottom_walls_[current_row_index_][i] = 1;
    }
  }
}

void s21::Maze::ShowNewRow() {
  bool show_id = false;
  if (current_row_index_ == 0) {
    for (int j = 0; j < cols_ * 3; j++) {
      printf("_");
    }
    printf("_\n");
  }
  for (int j = 0; j < cols_; j++) {
    if (j == 0) {
      printf("|");
    }
    if (IsBottomWall(current_row_index_, j) == 1) {
      printf("_");
      if (show_id) printf("%2d", row_sets_[j]);
      printf("_");
    } else {
      printf(" ");
      if (show_id) printf("%2d", row_sets_[j]);
      printf(" ");
    }
    if (right_walls_[current_row_index_][j] == 1) {
      printf("|");
    } else {
      printf(" ");
    }
  }
  printf("\n");
}

void s21::Maze::MarkupCells() {
  for (int i = 0; i < cols_; i++) {
    if (current_row_index_ > 0 &&
        IsBottomWall(current_row_index_ - 1, i) == 1) {
      row_sets_[i] = 0;
    }
    if (row_sets_[i] == 0) {
      row_sets_[i] = next_set_id_++;
    }
  }
}

bool s21::Maze::IsCanMoveLeft() {
  bool result = true;
  if ((current_.second - 1) < 0 ||
      visited_[current_.first][current_.second - 1] ||
      IsRWall(current_.first, current_.second - 1))
    result = false;
  return result;
}

bool s21::Maze::IsCanMoveRight() {
  bool result = true;
  if ((current_.second + 1) >= cols_ ||
      visited_[current_.first][current_.second + 1] ||
      IsRWall(current_.first, current_.second))
    result = false;
  return result;
}

bool s21::Maze::IsCanMoveUp() {
  bool result = true;
  if ((current_.first - 1) < 0 ||
      visited_[current_.first - 1][current_.second] ||
      IsBWall(current_.first - 1, current_.second))
    result = false;
  return result;
}

bool s21::Maze::IsCanMoveDown() {
  bool result = true;
  if ((current_.first + 1) >= rows_ ||
      visited_[current_.first + 1][current_.second] ||
      IsBWall(current_.first, current_.second))
    result = false;
  return result;
}

bool s21::Maze::IsBWall(int r, int c) { return b_walls_[r * cols_ + c]; }

bool s21::Maze::IsRWall(int r, int c) { return r_walls_[r * cols_ + c]; }

std::stack<std::pair<int, int>> s21::Maze::FindPath(std::pair<int, int> start,
                                                    std::pair<int, int> end) {
  start.first = std::clamp(start.first, 0, rows_ - 1);
  start.second = std::clamp(start.second, 0, cols_ - 1);
  end.first = std::clamp(end.first, 0, rows_ - 1);
  end.second = std::clamp(end.second, 0, cols_ - 1);

  visited_ = std::vector<std::vector<int>>(
      std::clamp(rows_, 1, 50), std::vector<int>(std::clamp(cols_, 1, 50), 0));
  path_ = std::stack<std::pair<int, int>>();
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
