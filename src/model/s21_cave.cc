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