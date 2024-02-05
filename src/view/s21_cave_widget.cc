#include "s21_cave_widget.h"

#include "../controller/s21_controller.h"

void s21::CaveWidget::Initialize() {
  cell_width_ = x_max_ / controller_->GetCaveCols();
  cell_height_ = y_max_ / controller_->GetCaveRows();
}

void s21::CaveWidget::paintEvent(QPaintEvent* event) {
  if (controller_->EmptyCave()) {
    return;
  }

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(QPen(Qt::lightGray, line_width_));
  painter.setBrush(Qt::lightGray);

  // Draw borders
  painter.drawLine(x_min_, y_min_, x_max_, y_min_);  // top
  painter.drawLine(x_min_, y_max_, x_max_, y_max_);  // bottom
  painter.drawLine(x_min_, y_min_, x_min_, y_max_);  // left
  painter.drawLine(x_max_, y_min_, x_max_, y_max_);  // right

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
