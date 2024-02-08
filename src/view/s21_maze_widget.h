#ifndef S21_MAZE_MAZE_WIDGET_H
#define S21_MAZE_MAZE_WIDGET_H

#include <QMouseEvent>
#include <QPainter>

#include "s21_labyrinth_widget.h"

namespace s21 {

class Controller;

class MazeWidget : public LabyrinthWidget {
  Q_OBJECT
 public:
  // Constructors
  using LabyrinthWidget::LabyrinthWidget;

  // Functions
  void Initialize() override;
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;

 private:
  // Variables
  QPoint path_start_, path_end_;
};
}  // namespace s21
#endif  // S21_MAZE_MAZE_WIDGET_H
