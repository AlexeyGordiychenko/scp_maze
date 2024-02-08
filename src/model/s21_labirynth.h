#ifndef S21_MAZE_LABIRYNTH_H
#define S21_MAZE_LABIRYNTH_H

#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace s21 {

class Labirynth {
 protected:
  template <typename... Args>
  std::tuple<int, int> ParseFile(std::string filename,
                                 std::string str_labirynth, Args&... args) {
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
        throw std::runtime_error("Failed to read size of a " + str_labirynth +
                                 ".");
      } else if (iss >> temp) {
        throw std::runtime_error("Too many values for the size of a " +
                                 str_labirynth + ".");
      }
    } else {
      throw std::runtime_error("File is empty.");
    }

    (ParseMatrix(file, rows, cols, args), ...);

    while (std::getline(file, line)) {
      if (!line.empty())
        throw std::runtime_error("Too many rows for a " + str_labirynth + ".");
    }

    if (rows > 50 or cols > 50) {
      throw std::runtime_error("Size of a " + str_labirynth +
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
};
}  // namespace s21
#endif  // S21_MAZE_LABIRYNTH_H