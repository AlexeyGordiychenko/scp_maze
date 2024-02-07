#include "s21_cave.h"

#include <random>
#include <tuple>

#include "s21_parser.h"

void s21::Cave::Initialize(const std::string filename) {
  ClearData();
  auto parser = s21::Parser();
  std::tie(rows_, cols_) = parser.ParseFile(filename, "cave", cells_);
  is_empty_ = false;
}

bool s21::Cave::Empty() const { return is_empty_; }

void s21::Cave::ClearData() {
  cells_.clear();
  is_empty_ = true;
}

int s21::Cave::GetRows() const { return rows_; }
int s21::Cave::GetCols() const { return cols_; }
const std::vector<bool>& s21::Cave::GetCells() const { return cells_; }

void s21::Cave::GenerateCave(int chance, int rows, int cols) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 100);
  rows_ = rows;
  cols_ = cols;
  cells_.clear();
  for (auto i = 0; i < rows; ++i) {
    for (auto j = 0; j < cols; ++j) {
      cells_.push_back(static_cast<bool>(dis(gen) <= chance));
    }
  }
  is_empty_ = false;
}

bool s21::Cave::CellularAutomaton(int birth_limit, int death_limit) {
  std::vector<bool> new_cells(rows_ * cols_);
  bool res = false;
  for (int row = 0; row < rows_; ++row) {
    for (int col = 0; col < cols_; ++col) {
      int alive_neighbors = CountNeighbors(row, col);
      bool is_alive = cells_[row * cols_ + col];

      if (is_alive && (alive_neighbors < death_limit)) {
        new_cells[row * cols_ + col] = false;
        res = true;
      } else if (!is_alive && (alive_neighbors > birth_limit)) {
        new_cells[row * cols_ + col] = true;
        res = true;
      } else {
        new_cells[row * cols_ + col] = is_alive;
      }
    }
  }
  cells_ = new_cells;
  return res;
}

int s21::Cave::CountNeighbors(int row, int col) {
  int count = 0;
  for (int dr = -1; dr <= 1; ++dr) {
    for (int dc = -1; dc <= 1; ++dc) {
      if (dr == 0 && dc == 0) continue;

      int nb_row = row + dr;
      int nb_col = col + dc;

      if (nb_row < 0 || nb_col < 0 || nb_row >= rows_ || nb_col >= cols_ ||
          cells_[nb_row * cols_ + nb_col]) {
        ++count;
      }
    }
  }
  return count;
}