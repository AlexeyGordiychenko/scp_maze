#include "scp_model.h"

#include <tuple>

void scp::Model::InitializeMaze(const std::string filename) {
  maze_.Initialize(filename);
}
bool scp::Model::EmptyMaze() const { return maze_.Empty(); }
int scp::Model::GetMazeRows() const { return maze_.GetRows(); }
int scp::Model::GetMazeCols() const { return maze_.GetCols(); }
const std::vector<bool>& scp::Model::GetMazeRWalls() const {
  return maze_.GetRWalls();
}
const std::vector<bool>& scp::Model::GetMazeBWalls() const {
  return maze_.GetBWalls();
}
void scp::Model::InitializeCave(const std::string filename) {
  cave_.Initialize(filename);
}
bool scp::Model::EmptyCave() const { return cave_.Empty(); }
int scp::Model::GetCaveRows() const { return cave_.GetRows(); }
int scp::Model::GetCaveCols() const { return cave_.GetCols(); }
const std::vector<bool>& scp::Model::GetCaveCells() const {
  return cave_.GetCells();
}
void scp::Model::GenerateCave(int chance, int rows, int cols) {
  cave_.GenerateCave(chance, rows, cols);
}

bool scp::Model::CaveCellularAutomaton(int birth_limit, int death_limit) {
  return cave_.CellularAutomaton(birth_limit, death_limit);
}

void scp::Model::SaveMaze(const std::string filename) { maze_.Save(filename); }
void scp::Model::SaveCave(const std::string filename) { cave_.Save(filename); }

void scp::Model::GenerateMaze(int rows, int cols) {
  maze_.GenerateMaze(rows, cols);
}

std::stack<std::pair<int, int>> scp::Model::FindPath(std::pair<int, int> start,
                                                     std::pair<int, int> end) {
  return maze_.FindPath(start, end);
}
