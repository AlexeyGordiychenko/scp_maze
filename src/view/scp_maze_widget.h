#ifndef SCP_MAZE_MAZE_WIDGET_H
#define SCP_MAZE_MAZE_WIDGET_H

#include <QMouseEvent>
#include <QPainter>

#include "scp_labyrinth_widget.h"

namespace scp {

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
  // Functions
  int AdjustPathLineNearPoints(int c1, int c2, int k);
  void RenderMaze(QPainter& painter);
  void RenderPonts(QPainter& painter);
  void RenderPath(QPainter& painter);

  // Variables
  QPoint path_start_, path_end_;
  int path_edges_size_;
};
}  // namespace scp
#endif  // SCP_MAZE_MAZE_WIDGET_H
