#ifndef S21_MAZE_V2_MODEL_H
#define S21_MAZE_V2_MODEL_H

#include <string>
#include <vector>

namespace s21 {

class Model {
 public:
  void Initialize(const std::string filename);
  bool Empty() const;
  int GetRows() const;
  int GetCols() const;
  const std::vector<bool>& GetRWalls() const;
  const std::vector<bool>& GetBWalls() const;

 private:
  bool is_empty_ = true;
  int rows_, cols_;
  std::vector<bool> r_walls_, b_walls_;
  void ClearData();
};
}  // namespace s21
#endif  // S21_MAZE_V2_MODEL_H