#ifndef S21_MAZE_VALUE_SLIDER_H
#define S21_MAZE_VALUE_SLIDER_H

#include <QWidget>

namespace s21 {

class ValueSlider : public QSlider {
 public:
  ValueSlider(QWidget* parent = nullptr) : QSlider(parent) {}
  ValueSlider(Qt::Orientation orientation, QWidget* parent = nullptr)
      : QSlider(orientation, parent) {}

 protected:
  void paintEvent(QPaintEvent* event) override {
    QSlider::paintEvent(event);

    QPainter painter(this);
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect knob_rect = style()->subControlRect(QStyle::CC_Slider, &opt,
                                              QStyle::SC_SliderHandle, this);
    painter.drawText(knob_rect, Qt::AlignCenter,
                     QString::number(this->value()));
  }
};
}  // namespace s21
#endif  // S21_MAZE_VALUE_SLIDER_H
