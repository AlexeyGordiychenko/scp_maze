#ifndef SCP_MAZE_MAZE_H
#define SCP_MAZE_MAZE_H

#include <stack>
#include <string>
#include <vector>

#include "scp_labyrinth.h"

namespace scp {

class Maze : public Labyrinth {
 public:
  void Initialize(const std::string filename);
  bool Empty() const;
  int GetRows() const;
  int GetCols() const;
  const std::vector<bool>& GetRWalls() const;
  const std::vector<bool>& GetBWalls() const;
  void Save(const std::string filename);
  void GenerateMaze(int cols, int rows, int seed = time(0));
  std::stack<std::pair<int, int>> FindPath(std::pair<int, int> start,
                                           std::pair<int, int> end);

 private:
  std::vector<bool> r_walls_, b_walls_;
  std::vector<std::vector<int>> right_walls_;
  std::vector<std::vector<int>> bottom_walls_;
  std::vector<int> row_sets_;
  int next_set_id_;
  int current_row_index_;
  std::stack<std::pair<int, int>> path_;
  std::pair<int, int> current_;
  std::vector<std::vector<int>> visited_;
  void ClearData();
  void MarkupCells();
  void PlaceRightWalls();
  void PlaceBottomWalls();
  bool IsRightWall(int m, int n) { return right_walls_[m][n] == 1; }
  bool IsBottomWall(int m, int n) { return bottom_walls_[m][n] == 1; }
  bool IsCanMoveLeft();
  bool IsCanMoveRight();
  bool IsCanMoveUp();
  bool IsCanMoveDown();
  bool IsBWall(int r, int c);
  bool IsRWall(int r, int c);
};
}  // namespace scp
#endif  // SCP_MAZE_MAZE_H
