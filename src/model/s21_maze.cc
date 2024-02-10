#include "s21_maze.h"

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

void s21::Maze::GenerateMaze(int rows, int cols) {
  MazeGenerator gen;
  Maze maze = gen.GenerateMaze(cols, rows, false);
  cols_ = cols;
  rows_ = rows;
  r_walls_ = maze.r_walls_;
  b_walls_ = maze.b_walls_;
  is_empty_ = false;
}

std::stack<std::pair<int, int>> s21::Maze::FindPath(std::pair<int, int> start,
                                                    std::pair<int, int> end) {
  PathFinder pathfinder(r_walls_, b_walls_, rows_, cols_);
  std::stack<pair<int, int>> path = pathfinder.FindPath(start, end);
  return path;
}
