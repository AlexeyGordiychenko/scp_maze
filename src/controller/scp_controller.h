#ifndef SCP_MAZE_CONTROLLER_H
#define SCP_MAZE_CONTROLLER_H

#include <stack>
#include <string>
#include <tuple>
#include <vector>

namespace scp {

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
  void SaveMaze(const std::string filename);
  void SaveCave(const std::string filename);
  void GenerateMaze(int r, int c);
  std::stack<std::pair<int, int>> FindPath(std::pair<int, int> start,
                                           std::pair<int, int> end);

 private:
  Model* model_;
};
}  // namespace scp
#endif  // SCP_MAZE_CONTROLLER_H
