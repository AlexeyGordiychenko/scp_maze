#include "s21_maze_widget.h"

#include "../controller/s21_controller.h"

void s21::MazeWidget::Initialize() {
  cell_width_ = x_max_ / controller_->GetMazeCols();
  cell_height_ = y_max_ / controller_->GetMazeRows();
  path_start_ = QPoint();
  path_end_ = QPoint();
}

void s21::MazeWidget::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);
  QPainter painter(this);
  PaintInitialState(painter);

  if (controller_->EmptyMaze()) {
    return;
  }

  // Draw the maze
  auto r_walls = controller_->GetMazeRWalls();
  auto b_walls = controller_->GetMazeBWalls();
  auto rows = controller_->GetMazeRows(), cols = controller_->GetMazeCols();
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
    auto path_edges_size =
        std::min(std::min(cell_width_, cell_height_) / 2, 30);
    auto k = path_edges_size / 2 - 1;
    if (!path_start_.isNull()) {
      painter.setPen(Qt::cyan);
      painter.setBrush(Qt::cyan);
      painter.drawEllipse(path_start_.x() - k, path_start_.y() - k,
                          path_edges_size, path_edges_size);
    }
    if (!path_end_.isNull()) {
      painter.setPen(Qt::magenta);
      painter.setBrush(Qt::magenta);
      painter.drawRect(path_end_.x() - k, path_end_.y() - k, path_edges_size,
                       path_edges_size);
    }

    // Draw path
    if (!path_start_.isNull() && !path_end_.isNull()) {
      std::stack<std::pair<int, int>> path = controller_->FindPath(
          {path_start_.y() / cell_height_, path_start_.x() / cell_width_},
          {path_end_.y() / cell_height_, path_end_.x() / cell_width_});
      if (path.size() != 0) {
        auto begin = path.top();
        path.pop();
        int x1 = cell_width_ * begin.second + cell_width_ / 2;
        int y1 = cell_height_ * begin.first + cell_height_ / 2;
        int size = path.size();
        for (int i = 0; i < size; ++i) {
          auto p = path.top();
          path.pop();
          int x2 = cell_width_ * p.second + cell_width_ / 2;
          int y2 = cell_height_ * p.first + cell_height_ / 2;
          painter.drawLine(x1, y1, x2, y2);
          x1 = x2;
          y1 = y2;
        }
      }
    }
  }
}

void s21::MazeWidget::mousePressEvent(QMouseEvent* event) {
  if (!controller_->EmptyMaze()) {
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
}
