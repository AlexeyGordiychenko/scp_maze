#include "s21_maze_widget.h"

#include "../controller/s21_controller.h"
#include "s21_view.h"

s21::MazeWidget::MazeWidget(QWidget* parent) : QWidget(parent) {
  setFixedSize(x_min_ + x_max_, y_min_ + y_max_);
}

void s21::MazeWidget::SetController(Controller* controller) {
  controller_ = controller;
}

void s21::MazeWidget::SetCellSize() {
  cell_width_ = x_max_ / controller_->GetCols();
  cell_height_ = y_max_ / controller_->GetRows();
}

void s21::MazeWidget::paintEvent(QPaintEvent* event) {
  if (controller_->Empty()) {
    return;
  }
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing);
  auto green_pen =
      QPen(Qt::green, line_width_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

  painter.setPen(green_pen);

  // Draw borders
  painter.setPen(green_pen);
  painter.drawLine(x_min_, y_min_, x_max_, y_min_);  // top
  painter.drawLine(x_min_, y_max_, x_max_, y_max_);  // bottom
  painter.drawLine(x_min_, y_min_, x_min_, y_max_);  // left
  painter.drawLine(x_max_, y_min_, x_max_, y_max_);  // right

  // Draw the maze
  auto r_walls = controller_->GetRWalls();
  auto b_walls = controller_->GetBWalls();
  auto rows = controller_->GetRows(), cols = controller_->GetCols();
  auto idx = 0;
  for (auto y = 0; y < rows; ++y) {
    for (auto x = 0; x < cols; ++x, ++idx) {
      bool is_right = x != cols - 1 && r_walls[idx];
      bool is_bottom = y != rows - 1 && b_walls[idx];

      if (is_right || is_bottom) {
        auto x_right = x_min_ + (x + 1) * cell_width_;
        auto y_bottom = y_min_ + (y + 1) * cell_height_;
        if (is_right) {
          painter.drawLine(x_right, y_min_ + y * cell_height_, x_right,
                           y_bottom);
        }
        if (is_bottom) {
          painter.drawLine(x_min_ + x * cell_width_, y_bottom, x_right,
                           y_bottom);
        }
      }
    }
  }
}