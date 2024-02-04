#ifndef S21_MAZE_CONTROLLER_H
#define S21_MAZE_CONTROLLER_H

#include <string>
#include <vector>

namespace s21 {

class Model;

class Controller {
 public:
  // Constructors and the destructor
  Controller(Model* model) : model_(model) {}
  Controller(const Controller&) = delete;
  Controller& operator=(const Controller&) = delete;
  Controller(Controller&&) = delete;
  Controller& operator=(Controller&&) = delete;
  ~Controller();

  // Main functions
  void Initialize(const std::string filename);
  bool Empty() const;
  int GetRows() const;
  int GetCols() const;
  const std::vector<bool>& GetRWalls() const;
  const std::vector<bool>& GetBWalls() const;

 private:
  Model* model_;
};
}  // namespace s21
#endif  // S21_MAZE_CONTROLLER_H
