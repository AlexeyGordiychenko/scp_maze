#ifndef S21_MAZE_LABYRINT_WIDGET_H
#define S21_MAZE_LABYRINT_WIDGET_H

#include <QPainter>
#include <QWidget>

namespace s21 {

class Controller;

class LabyrinthWidget : public QWidget {
 public:
  // Constructors
  explicit LabyrinthWidget(QWidget* parent = nullptr) : QWidget(parent) {
    setFixedSize(x_min_ + x_max_, y_min_ + y_max_);
  };

  LabyrinthWidget(const LabyrinthWidget&) = delete;
  LabyrinthWidget& operator=(const LabyrinthWidget&) = delete;
  LabyrinthWidget(LabyrinthWidget&&) = delete;
  LabyrinthWidget& operator=(LabyrinthWidget&&) = delete;

  // Functions
  void SetController(Controller* controller) { controller_ = controller; };
  void PaintInitialState(QPainter& painter) {
    painter.fillRect(rect(), QBrush(QColor(63, 63, 63)));
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::lightGray, line_width_));
    painter.setBrush(Qt::lightGray);

    // Draw borders
    painter.drawLine(x_min_, y_min_, x_max_, y_min_);  // top
    painter.drawLine(x_min_, y_max_, x_max_, y_max_);  // bottom
    painter.drawLine(x_min_, y_min_, x_min_, y_max_);  // left
    painter.drawLine(x_max_, y_min_, x_max_, y_max_);  // right
  };
  virtual void Initialize() = 0;

 protected:
  // Variables
  Controller* controller_;
  int size = 500;
  int x_min_ = 1, y_min_ = 1, x_max_ = size + x_min_, y_max_ = size + y_min_;
  double cell_width_ = 0, cell_height_ = 0;
  int line_width_ = 2;
};
}  // namespace s21
#endif  // S21_MAZE_LABYRINT_WIDGET_H
