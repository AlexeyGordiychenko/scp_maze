#include "s21_mazegenerator.h"

#include <algorithm>

s21::Maze s21::MazeGenerator::GenerateMaze(int cols, int rows,
                                           bool debug = false,
                                           int seed = time(0)) {
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

  return Maze(false, cols, rows, r_walls, b_walls);
}

void s21::MazeGenerator::PlaceRightWalls() {
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

void s21::MazeGenerator::PlaceBottomWalls() {
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

void s21::MazeGenerator::ShowNewRow() {
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

void s21::MazeGenerator::MarkupCells() {
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
