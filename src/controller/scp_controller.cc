#include "scp_controller.h"

#include "../model/scp_model.h"

scp::Controller::~Controller() {}

void scp::Controller::InitializeMaze(const std::string filename) {
  model_->InitializeMaze(filename);
}

bool scp::Controller::EmptyMaze() const { return model_->EmptyMaze(); }

int scp::Controller::GetMazeRows() const { return model_->GetMazeRows(); }
int scp::Controller::GetMazeCols() const { return model_->GetMazeCols(); }
const std::vector<bool>& scp::Controller::GetMazeRWalls() const {
  return model_->GetMazeRWalls();
}
const std::vector<bool>& scp::Controller::GetMazeBWalls() const {
  return model_->GetMazeBWalls();
}

void scp::Controller::InitializeCave(const std::string filename) {
  model_->InitializeCave(filename);
}

bool scp::Controller::EmptyCave() const { return model_->EmptyCave(); }

int scp::Controller::GetCaveRows() const { return model_->GetCaveRows(); }
int scp::Controller::GetCaveCols() const { return model_->GetCaveCols(); }

const std::vector<bool>& scp::Controller::GetCaveCells() const {
  return model_->GetCaveCells();
}

void scp::Controller::GenerateCave(int chance, int rows, int cols) {
  return model_->GenerateCave(chance, rows, cols);
}

bool scp::Controller::CaveCellularAutomaton(int birth_limit, int death_limit) {
  return model_->CaveCellularAutomaton(birth_limit, death_limit);
}

void scp::Controller::SaveMaze(const std::string filename) {
  model_->SaveMaze(filename);
}

void scp::Controller::SaveCave(const std::string filename) {
  model_->SaveCave(filename);
}

void scp::Controller::GenerateMaze(int rows, int cols) {
  model_->GenerateMaze(rows, cols);
}

std::stack<std::pair<int, int>> scp::Controller::FindPath(
    std::pair<int, int> start, std::pair<int, int> end) {
  return model_->FindPath(start, end);
}
