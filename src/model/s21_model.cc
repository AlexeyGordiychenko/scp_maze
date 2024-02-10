#include "s21_model.h"

#include <tuple>

void s21::Model::InitializeMaze(const std::string filename) {
  maze_.Initialize(filename);
}
bool s21::Model::EmptyMaze() const { return maze_.Empty(); }
int s21::Model::GetMazeRows() const { return maze_.GetRows(); }
int s21::Model::GetMazeCols() const { return maze_.GetCols(); }
const std::vector<bool>& s21::Model::GetMazeRWalls() const {
  return maze_.GetRWalls();
}
const std::vector<bool>& s21::Model::GetMazeBWalls() const {
  return maze_.GetBWalls();
}
void s21::Model::InitializeCave(const std::string filename) {
  cave_.Initialize(filename);
}
bool s21::Model::EmptyCave() const { return cave_.Empty(); }
int s21::Model::GetCaveRows() const { return cave_.GetRows(); }
int s21::Model::GetCaveCols() const { return cave_.GetCols(); }
const std::vector<bool>& s21::Model::GetCaveCells() const {
  return cave_.GetCells();
}
void s21::Model::GenerateCave(int chance, int rows, int cols) {
  cave_.GenerateCave(chance, rows, cols);
}

bool s21::Model::CaveCellularAutomaton(int birth_limit, int death_limit) {
  return cave_.CellularAutomaton(birth_limit, death_limit);
}

void s21::Model::SaveMaze(const std::string filename) { maze_.Save(filename); }
void s21::Model::SaveCave(const std::string filename) { cave_.Save(filename); }

void s21::Model::GenerateMaze(int rows, int cols) {
  maze_.GenerateMaze(rows, cols);
}

std::stack<pair<int, int>> s21::Model::FindPath(std::pair<int, int> start,
                                                std::pair<int, int> end) {
  return maze_.FindPath(start, end);
}
