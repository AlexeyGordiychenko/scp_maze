#include "s21_maze_widget.h"

#include "../controller/s21_controller.h"
#include "s21_view.h"

s21::MazeWidget::MazeWidget(QWidget* parent) : QWidget(parent) {
  setFixedSize(x_min_ + x_max_, y_min_ + y_max_);
}

void s21::MazeWidget::SetController(Controller* controller) {
  controller_ = controller;
}

void s21::MazeWidget::Initialize() {
  cell_width_ = x_max_ / controller_->GetCols();
  cell_height_ = y_max_ / controller_->GetRows();
  path_start_ = QPoint();
  path_end_ = QPoint();
}

void s21::MazeWidget::paintEvent(QPaintEvent* event) {
  if (controller_->Empty()) {
    return;
  }
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(QPen(Qt::lightGray, line_width_));

  // Draw borders
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

  // Draw path's start and end points
  if (!path_start_.isNull() || !path_end_.isNull()) {
    auto path_edges_size_ =
        std::min(std::min(cell_width_, cell_height_) / 2, 6);
    auto k = path_edges_size_ / 2 - 1;
    if (!path_start_.isNull()) {
      painter.setPen(Qt::cyan);
      painter.setBrush(Qt::cyan);
      painter.drawEllipse(path_start_.x() - k, path_start_.y() - k,
                          path_edges_size_, path_edges_size_);
    }
    if (!path_end_.isNull()) {
      painter.setPen(Qt::magenta);
      painter.setBrush(Qt::magenta);
      painter.drawRect(path_end_.x() - k, path_end_.y() - k, path_edges_size_,
                       path_edges_size_);
    }
  }
}

void s21::MazeWidget::mousePressEvent(QMouseEvent* event) {
  int x = event->position().x();
  int y = event->position().y();
  int col = (x - x_min_) / cell_width_ * cell_width_ + cell_width_ / 2;
  int row = (y - y_min_) / cell_height_ * cell_height_ + cell_height_ / 2;
  if (event->buttons() & Qt::LeftButton) {
    path_start_ = QPoint(col, row);
  } else {
    path_end_ = QPoint(col, row);
  }
  update();
}
