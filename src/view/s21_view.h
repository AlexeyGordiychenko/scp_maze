#ifndef S21_MAZE_VIEW_H
#define S21_MAZE_VIEW_H

#include <QMainWindow>

#include "../controller/s21_controller.h"
#include "ui_s21_view.h"

namespace Ui {
class View;
}

namespace s21 {

class Labyrinth;
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
  void Render(Labyrinth* element);
  void FilePathChange(QComboBox* element);
  void GenerateLabiryth(QComboBox* element);
  void GenerateCaveNextStep();

 private:
  // Variables
  Ui::View* ui_;
  Controller* controller_;
  int history_max_list_ = 10;
};

}  // namespace s21
#endif  // S21_MAZE_VIEW_H
