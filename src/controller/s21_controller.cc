#include "s21_controller.h"

#include "../model/s21_model.h"

s21::Controller::~Controller() {}

void s21::Controller::Initialize(const std::string filename) {
  model_->Initialize(filename);
}

bool s21::Controller::Empty() const { return model_->Empty(); }
