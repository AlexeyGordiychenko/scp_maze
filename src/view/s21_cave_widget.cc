#include "s21_cave_widget.h"

#include "../controller/s21_controller.h"
#include "s21_view.h"

s21::CaveWidget::CaveWidget(QWidget* parent) : QWidget(parent) {
  setFixedSize(x_min_ + x_max_, y_min_ + y_max_);
}

void s21::CaveWidget::SetController(Controller* controller) {
  controller_ = controller;
}

void s21::CaveWidget::Initialize() {
  // cell_width_ = x_max_ / controller_->GetCols();
  // cell_height_ = y_max_ / controller_->GetRows();
}

void s21::CaveWidget::paintEvent(QPaintEvent* event) {
  // if (controller_->Empty()) {
  //   return;
  // }
}
