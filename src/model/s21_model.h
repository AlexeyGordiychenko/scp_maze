#ifndef S21_MAZE_V2_MODEL_H
#define S21_MAZE_V2_MODEL_H

#include <string>
#include <vector>

namespace s21 {

class Model {
 public:
  void Initialize(const std::string filename);
  void ParseFile(std::string filename);
  bool Empty() const;

 private:
  bool is_empty_ = true;

  void ClearData();
};
}  // namespace s21
#endif  // S21_MAZE_V2_MODEL_H