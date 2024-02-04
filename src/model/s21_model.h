#ifndef S21_MAZE_MODEL_H
#define S21_MAZE_MODEL_H

#include <string>
#include <vector>

#include "s21_maze.h"

namespace s21 {

class Model {
 public:
  void InitializeMaze(const std::string filename);
  bool EmptyMaze() const;
  int GetMazeRows() const;
  int GetMazeCols() const;
  const std::vector<bool>& GetMazeRWalls() const;
  const std::vector<bool>& GetMazeBWalls() const;

 private:
  Maze maze_;
};
}  // namespace s21
#endif  // S21_MAZE_MODEL_H