#ifndef S21_MAZE_MAZE_H
#define S21_MAZE_MAZE_H

#include <string>
#include <vector>

#include "s21_labyrinth.h"
#include "s21_mazegenerator.h"

namespace s21 {

class Maze : public Labyrinth {
 public:
  Maze() {}
  Maze(bool is_empty, int rows, int cols, const std::vector<bool> r_walls,
       const std::vector<bool> b_walls);
  void Initialize(const std::string filename);
  bool Empty() const;
  int GetRows() const;
  int GetCols() const;
  const std::vector<bool>& GetRWalls() const;
  const std::vector<bool>& GetBWalls() const;
  void Save(const std::string filename);
  void GenerateMaze(int rows, int cols);

 private:
  std::vector<bool> r_walls_, b_walls_;
  void ClearData();
};
}  // namespace s21
#endif  // S21_MAZE_MAZE_H
