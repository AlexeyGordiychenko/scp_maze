#include "s21_maze.h"

#include <tuple>

#include "s21_parser.h"

void s21::Maze::Initialize(const std::string filename) {
  ClearData();
  auto parser = s21::Parser();
  std::tie(rows_, cols_) = parser.ParseFile(filename, r_walls_, b_walls_);
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
