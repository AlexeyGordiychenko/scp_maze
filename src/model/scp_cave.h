#ifndef SCP_MAZE_CAVE_H
#define SCP_MAZE_CAVE_H

#include <random>
#include <string>
#include <vector>

#include "scp_labyrinth.h"

namespace scp {

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
  std::vector<bool> cells_;
  void ClearData();
  int CountNeighbors(int row, int col);
};
}  // namespace scp
#endif  // SCP_MAZE_CAVE_H