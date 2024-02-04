#ifndef S21_MAZE_VALUE_SLIDER_H
#define S21_MAZE_VALUE_SLIDER_H

#include <QWidget>

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
    QRect knobBoundary = style()->subControlRect(QStyle::CC_Slider, &opt,
                                                 QStyle::SC_SliderHandle, this);
    int value = this->value();
    QString strValue = QString::number(value);
    painter.drawText(knobBoundary, Qt::AlignCenter, strValue);
  }
};
#endif  // S21_MAZE_WIDGET_H
