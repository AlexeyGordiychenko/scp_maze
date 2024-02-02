#include "s21_controller.h"

#include "../model/s21_model.h"

s21::Controller::~Controller() {}

void s21::Controller::Initialize(const std::string filename) {
  model_->Initialize(filename);
}

bool s21::Controller::Empty() const { return model_->Empty(); }

int s21::Controller::GetRows() const { return model_->GetRows(); }
int s21::Controller::GetCols() const { return model_->GetCols(); }
const std::vector<bool>& s21::Controller::GetRWalls() const {
  return model_->GetRWalls();
}
const std::vector<bool>& s21::Controller::GetBWalls() const {
  return model_->GetBWalls();
}
