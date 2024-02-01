#include "s21_maze_widget.h"

#include "../controller/s21_controller.h"
#include "s21_view.h"

s21::MazeWidget::MazeWidget(QWidget* parent) : QWidget(parent) {
  setFixedSize(500, 500);
}

void s21::MazeWidget::SetController(Controller* controller) {
  controller_ = controller;
}

void s21::MazeWidget::SetView(View* view) { view_ = view; }
