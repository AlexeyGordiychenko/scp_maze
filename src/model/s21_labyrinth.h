#ifndef S21_MAZE_LABYRINTH_H
#define S21_MAZE_LABYRINTH_H

#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace s21 {

class Labyrinth {
 protected:
  template <typename... Args>
  std::tuple<int, int> ParseFile(std::string filename,
                                 std::string str_labyrinth, Args&... args) {
    std::ifstream file(filename);

    if (!file.is_open()) {
      throw std::runtime_error("Can't open the file.");
    }

    std::string line;
    char temp = 0;
    int rows = 0, cols = 0;
    if (std::getline(file, line)) {
      std::istringstream iss(line);
      if (!(iss >> rows >> cols)) {
        throw std::runtime_error("Failed to read size of a " + str_labyrinth +
                                 ".");
      } else if (iss >> temp) {
        throw std::runtime_error("Too many values for the size of a " +
                                 str_labyrinth + ".");
      }
    } else {
      throw std::runtime_error("File is empty.");
    }

    (ParseMatrix(file, rows, cols, args), ...);

    while (std::getline(file, line)) {
      if (!line.empty())
        throw std::runtime_error("Too many rows for a " + str_labyrinth + ".");
    }

    if (rows > 50 or cols > 50) {
      throw std::runtime_error("Size of a " + str_labyrinth +
                               " is more than 50x50.");
    }
    return {rows, cols};
  }

  void ParseMatrix(std::ifstream& file, int rows, int cols,
                   std::vector<bool>& data) {
    std::string line;
    int rowscount = 0;
    while (rowscount < rows && std::getline(file, line)) {
      if (line.empty()) {
        continue;
      }
      std::istringstream iss(line);
      char value;
      for (auto i = 0; i < cols; ++i) {
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
      rowscount++;
    }
    if (data.size() != size_t(rows * cols)) {
      throw std::runtime_error("Not enough data for matrix rows.");
    }
  }

  template <typename... Args>
  void SaveToFile(std::string filename, int rows, int cols,
                  const Args&... args) {
    std::ofstream file(filename);

    if (!file.is_open()) {
      throw std::runtime_error("Can't open the file for saving.");
    }

    file << rows << " " << cols;

    (SaveMatrix(file, rows, cols, args), ...);

    file.close();
  }

  void SaveMatrix(std::ofstream& file, int rows, int cols,
                  const std::vector<bool>& data) {
    file << "\n";
    for (auto row = 0; row < rows; ++row) {
      for (auto col = 0; col < cols; ++col) {
        file << (data[row * cols + col] ? "1" : "0") << " ";
      }
      file << "\n";
    }
  }

  bool is_empty_ = true;
  int rows_ = 0, cols_ = 0;
};
}  // namespace s21
#endif  // S21_MAZE_LABYRINTH_H