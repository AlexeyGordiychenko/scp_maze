#include "s21_model.h"

#include <fstream>
#include <sstream>

void s21::Model::Initialize(const std::string filename) {
  ClearData();
  ParseFile(filename);
}

bool s21::Model::Empty() const { return is_empty_; }

void s21::Model::ClearData() { is_empty_ = true; }

void s21::Model::ParseFile(std::string filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Can't open the file.");
  }

  std::string line;
  char temp = 0;
  if (std::getline(file, line)) {
    std::istringstream iss(line);
    if (!(iss >> rows_ >> cols_)) {
      throw std::runtime_error("Failed to read size of a maze.");
    } else if (iss >> temp) {
      throw std::runtime_error("Too many values for the size of a maze.");
    }
  } else {
    throw std::runtime_error("File is empty.");
  }

  ParseMatrix(file, r_walls_);
  ParseMatrix(file, b_walls_);

  if (std::getline(file, line) and !line.empty()) {
    throw std::runtime_error("Too many rows for a maze.");
  }

  is_empty_ = false;
}

void s21::Model::ParseMatrix(std::ifstream& file, std::vector<bool>& data) {
  std::string line;
  int rows_count = 0;
  while (rows_count < rows_ && std::getline(file, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream iss(line);
    char value;
    for (auto i = 0; i < cols_; ++i) {
      if (iss >> value) {
        if (value != '0' && value != '1') {
          throw std::runtime_error("Matrix values must be 0 or 1.");
        }
        data.push_back(bool(value - '0'));
      } else {
        throw std::runtime_error("Not enough data for matrix columns.");
        file.close();
      }
    }
    if (iss >> value) {
      throw std::runtime_error("Too much data for matrix columns.");
    }
    rows_count++;
  }
  if (data.size() != size_t(rows_ * cols_)) {
    throw std::runtime_error("Not enough data for matrix rows.");
  }
}