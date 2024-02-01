#ifndef S21_MAZE_V2_GLWIDGET_H
#define S21_MAZE_V2_GLWIDGET_H

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

  // Funcitons
  void SetController(Controller* controller);
  void SetView(View* view);

 private:
  // Functions

  // Variables
  Controller* controller_;
  View* view_;
};
}  // namespace s21
#endif  // S21_MAZE_V2_GLWIDGET_H
