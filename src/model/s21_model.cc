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

  // std::string line;
  // size_t line_num = 0;
  // polygons_edges_count_ = 0;
  // while (std::getline(file, line) && ++line_num) {
  //   std::istringstream iss(line);
  //   std::string prefix;
  //   if (iss >> prefix) {
  //     if (prefix == "v") {
  //       if (!ParseVertices(iss)) {
  //         throw std::runtime_error("Line: " + std::to_string(line_num) +
  //                                  " failed to read a vertex.");
  //       }
  //     } else if (prefix == "f") {
  //       if (!ParsePolygons(iss)) {
  //         throw std::runtime_error("Line: " + std::to_string(line_num) +
  //                                  " failed to read a polygon.");
  //       }
  //     }
  //   }
  // }
  file.close();
  is_empty_ = false;
}
