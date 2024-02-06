#include "s21_cave.h"

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
