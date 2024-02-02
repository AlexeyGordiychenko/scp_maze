#ifndef S21_MAZE_V2_GLWIDGET_H
#define S21_MAZE_V2_GLWIDGET_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

namespace s21 {

class Controller;
class View;

class MazeWidget : public QWidget {
  Q_OBJECT
 public:
  // Constructors
  explicit MazeWidget(QWidget* parent = nullptr);
  MazeWidget(const MazeWidget&) = delete;
  MazeWidget& operator=(const MazeWidget&) = delete;
  MazeWidget(MazeWidget&&) = delete;
  MazeWidget& operator=(MazeWidget&&) = delete;

  // Functions
  void SetController(Controller* controller);
  void Initialize();

 protected:
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;

 private:
  // Functions

  // Variables
  Controller* controller_;
  View* view_;
  int size = 500;
  int x_min_ = 1, y_min_ = 1, x_max_ = size + x_min_, y_max_ = size + y_min_;
  int cell_width_ = 0, cell_height_ = 0, line_width_ = 2;
  QPoint path_start_, path_end_;
};
}  // namespace s21
#endif  // S21_MAZE_V2_GLWIDGET_H
