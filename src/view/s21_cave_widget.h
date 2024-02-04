#ifndef S21_CAVE_WIDGET_H
#define S21_CAVE_WIDGET_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

namespace s21 {

class Controller;
class View;

class CaveWidget : public QWidget {
  Q_OBJECT
 public:
  // Constructors
  explicit CaveWidget(QWidget* parent = nullptr);
  CaveWidget(const CaveWidget&) = delete;
  CaveWidget& operator=(const CaveWidget&) = delete;
  CaveWidget(CaveWidget&&) = delete;
  CaveWidget& operator=(CaveWidget&&) = delete;

  // Functions
  void SetController(Controller* controller);
  void Initialize();

 protected:
  void paintEvent(QPaintEvent* event) override;

 private:
  // Functions

  // Variables
  Controller* controller_;
  int size = 500;
  int x_min_ = 1, y_min_ = 1, x_max_ = size + x_min_, y_max_ = size + y_min_;
  int cell_width_ = 0, cell_height_ = 0, line_width_ = 2;
};
}  // namespace s21
#endif  // S21_CAVE_WIDGET_H
