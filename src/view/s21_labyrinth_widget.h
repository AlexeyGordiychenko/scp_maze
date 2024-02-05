#ifndef S21_MAZE_LABYRINT_WIDGET_H
#define S21_MAZE_LABYRINT_WIDGET_H

#include <QWidget>

namespace s21 {

class Controller;

class Labyrinth : public QWidget {
 public:
  // Constructors
  explicit Labyrinth(QWidget* parent = nullptr) : QWidget(parent) {
    setFixedSize(x_min_ + x_max_, y_min_ + y_max_);
  };

  Labyrinth(const Labyrinth&) = delete;
  Labyrinth& operator=(const Labyrinth&) = delete;
  Labyrinth(Labyrinth&&) = delete;
  Labyrinth& operator=(Labyrinth&&) = delete;

  // Functions
  void SetController(Controller* controller) { controller_ = controller; };
  virtual void Initialize() = 0;

 protected:
  // Variables
  Controller* controller_;
  int size = 500;
  int x_min_ = 1, y_min_ = 1, x_max_ = size + x_min_, y_max_ = size + y_min_;
  int cell_width_ = 0, cell_height_ = 0, line_width_ = 2;
};
}  // namespace s21
#endif  // S21_MAZE_LABYRINT_WIDGET_H
