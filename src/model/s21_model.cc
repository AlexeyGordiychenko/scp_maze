#include "s21_model.h"

#include <tuple>

#include "s21_parser.h"

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
