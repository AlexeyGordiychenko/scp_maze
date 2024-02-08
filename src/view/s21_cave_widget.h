#ifndef S21_MAZE_CAVE_WIDGET_H
#define S21_MAZE_CAVE_WIDGET_H

#include <QPainter>

#include "s21_labyrinth_widget.h"

namespace s21 {

class Controller;

class CaveWidget : public LabyrinthWidget {
  Q_OBJECT
 public:
  // Constructors
  using LabyrinthWidget::LabyrinthWidget;

  // Functions
  void Initialize() override;
  void paintEvent(QPaintEvent* event) override;
};
}  // namespace s21
#endif  // S21_MAZE_CAVE_WIDGET_H
