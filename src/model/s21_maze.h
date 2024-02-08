#ifndef S21_MAZE_MAZE_H
#define S21_MAZE_MAZE_H

#include <string>
#include <vector>

#include "s21_labyrinth.h"

namespace s21 {

class Maze : public Labyrinth {
 public:
  void Initialize(const std::string filename);
  bool Empty() const;
  int GetRows() const;
  int GetCols() const;
  const std::vector<bool>& GetRWalls() const;
  const std::vector<bool>& GetBWalls() const;
  void Save(const std::string filename);

 private:
  std::vector<bool> r_walls_, b_walls_;
  void ClearData();
};
}  // namespace s21
#endif  // S21_MAZE_MAZE_H