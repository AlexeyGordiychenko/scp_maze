#ifndef SCP_MAZE_CAVE_WIDGET_H
#define SCP_MAZE_CAVE_WIDGET_H

#include <QPainter>

#include "scp_labyrinth_widget.h"

namespace scp {

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
}  // namespace scp
#endif  // SCP_MAZE_CAVE_WIDGET_H
