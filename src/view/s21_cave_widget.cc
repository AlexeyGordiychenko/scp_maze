#include "s21_cave_widget.h"

#include "../controller/s21_controller.h"

void s21::CaveWidget::Initialize() {
  cell_width_ = x_max_ / controller_->GetCaveCols();
  cell_height_ = y_max_ / controller_->GetCaveRows();
}

void s21::CaveWidget::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);
  QPainter painter(this);
  PaintInitialState(painter);

  if (controller_->EmptyCave()) {
    return;
  }

  // Draw the cave
  auto cells = controller_->GetCaveCells();
  auto rows = controller_->GetCaveRows(), cols = controller_->GetCaveCols();
  auto idx = 0;
  for (auto y = 0; y < rows; ++y) {
    for (auto x = 0; x < cols; ++x, ++idx) {
      if (!cells[idx]) {
        painter.drawRect(x_min_ + x * cell_width_, y_min_ + y * cell_height_,
                         cell_width_, cell_height_);
      }
    }
  }
}
