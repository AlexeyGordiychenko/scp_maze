#include "s21_controller.h"

#include "../model/s21_model.h"

s21::Controller::~Controller() {}

void s21::Controller::InitializeMaze(const std::string filename) {
  model_->InitializeMaze(filename);
}

bool s21::Controller::EmptyMaze() const { return model_->EmptyMaze(); }

int s21::Controller::GetMazeRows() const { return model_->GetMazeRows(); }
int s21::Controller::GetMazeCols() const { return model_->GetMazeCols(); }
const std::vector<bool>& s21::Controller::GetMazeRWalls() const {
  return model_->GetMazeRWalls();
}
const std::vector<bool>& s21::Controller::GetMazeBWalls() const {
  return model_->GetMazeBWalls();
}

void s21::Controller::InitializeCave(const std::string filename) {
  model_->InitializeCave(filename);
}

bool s21::Controller::EmptyCave() const { return model_->EmptyCave(); }

int s21::Controller::GetCaveRows() const { return model_->GetCaveRows(); }
int s21::Controller::GetCaveCols() const { return model_->GetCaveCols(); }
const std::vector<bool>& s21::Controller::GetCaveCells() const {
  return model_->GetCaveCells();
}
