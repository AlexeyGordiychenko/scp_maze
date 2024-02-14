#ifndef SCP_MAZE_VALUE_SLIDER_H
#define SCP_MAZE_VALUE_SLIDER_H

#include <QWidget>

namespace scp {

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
}  // namespace scp
#endif  // SCP_MAZE_VALUE_SLIDER_H
