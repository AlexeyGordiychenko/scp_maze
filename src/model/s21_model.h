#ifndef S21_MAZE_MODEL_H
#define S21_MAZE_MODEL_H

#include <string>
#include <vector>

#include "s21_cave.h"
#include "s21_maze.h"

namespace s21 {

class Model {
 public:
  // Maze
  void InitializeMaze(const std::string filename);
  bool EmptyMaze() const;
  int GetMazeRows() const;
  int GetMazeCols() const;
  const std::vector<bool>& GetMazeRWalls() const;
  const std::vector<bool>& GetMazeBWalls() const;
  // Cave
  void InitializeCave(const std::string filename);
  bool EmptyCave() const;
  int GetCaveRows() const;
  int GetCaveCols() const;
  const std::vector<bool>& GetCaveCells() const;
  void GenerateCave(int chance, int rows, int cols);
  bool CaveCellularAutomaton(int birth_limit, int death_limit);

 private:
  Maze maze_;
  Cave cave_;
};
}  // namespace s21
#endif  // S21_MAZE_MODEL_H