#ifndef S21_MAZE_CAVE_H
#define S21_MAZE_CAVE_H

#include <random>
#include <string>
#include <vector>

#include "s21_labyrinth.h"

namespace s21 {

class Cave : public Labyrinth {
 public:
  void Initialize(const std::string filename);
  bool Empty() const;
  int GetRows() const;
  int GetCols() const;
  const std::vector<bool>& GetCells() const;
  void GenerateCave(int chance, int rows, int cols,
                    unsigned seed = std::random_device{}());
  bool CellularAutomaton(int birth_limit, int death_limit);
  void Save(const std::string filename);

 private:
  bool is_empty_ = true;
  int rows_, cols_;
  std::vector<bool> cells_;
  void ClearData();
  int CountNeighbors(int row, int col);
};
}  // namespace s21
#endif  // S21_MAZE_CAVE_H