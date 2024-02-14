#ifndef SCP_MAZE_VIEW_H
#define SCP_MAZE_VIEW_H

#include <QMainWindow>
#include <QTimer>

#include "../controller/scp_controller.h"
#include "ui_scp_view.h"

namespace Ui {
class View;
}

namespace scp {

class LabyrinthWidget;

class View : public QMainWindow {
  Q_OBJECT

 public:
  // Constructors and the destructor
  View(Controller* controller, QWidget* parent = nullptr);
  View(const View&) = delete;
  View& operator=(const View&) = delete;
  View(View&&) = delete;
  View& operator=(View&&) = delete;
  ~View();

 private slots:
  void OpenMazeFile();
  void OpenCaveFile();
  void OpenFile(QComboBox* file_path);
  void Render(LabyrinthWidget* element);
  void FilePathChange(QComboBox* element);
  void GenerateLabyrinth(QComboBox* element);
  void GenerateCaveNextStep();
  void GenerateCavePlay();
  void StopTimer();
  void StartTimer();
  void SaveLabyrinth(QComboBox* element);

 private:
  // Variables
  Ui::View* ui_;
  Controller* controller_;
  int history_max_list_ = 10;
  QTimer timer_;
};

}  // namespace scp
#endif  // SCP_MAZE_VIEW_H
