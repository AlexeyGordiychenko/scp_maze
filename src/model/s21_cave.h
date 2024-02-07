#ifndef S21_MAZE_CAVE_H
#define S21_MAZE_CAVE_H

#include <string>
#include <vector>

namespace s21 {

class Cave {
 public:
  void Initialize(const std::string filename);
  bool Empty() const;
  int GetRows() const;
  int GetCols() const;
  const std::vector<bool>& GetCells() const;
  void GenerateCave(int chance, int rows, int cols);
  bool CellularAutomaton(int birth_limit, int death_limit);

 private:
  bool is_empty_ = true;
  int rows_, cols_;
  std::vector<bool> cells_;
  void ClearData();
  int CountNeighbors(int row, int col);
};
}  // namespace s21
#endif  // S21_MAZE_CAVE_H