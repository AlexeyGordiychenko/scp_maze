#include "s21_view.h"

#include <QFileDialog>
#include <QMessageBox>

#include "s21_labyrinth_widget.h"

s21::View::View(Controller* controller, QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::View), controller_(controller) {
  ui_->setupUi(this);

  connect(ui_->mazeOpenFile, &QPushButton::clicked, this, &View::OpenFile);
  connect(ui_->mazeFilePath, qOverload<int>(&QComboBox::currentIndexChanged),
          this, &View::FilePathChange);

  ui_->mazeWidget->SetController(controller);
  ui_->caveWidget->SetController(controller);
}

s21::View::~View() { delete ui_; }

void s21::View::OpenFile() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open maze file:"), "~/", tr("Maze Files (*.txt)"));
  if (filename.isEmpty()) return;
  auto index = ui_->mazeFilePath->findText(filename);
  auto count = ui_->mazeFilePath->count();
  if (index == -1) {
    if (count >= history_max_list_) {
      ui_->mazeFilePath->removeItem(0);
      count--;
    }
    ui_->mazeFilePath->addItem(filename);
    index = count;
  }
  FilePathChange(index);
}

void s21::View::RenderMaze() {
  std::string filename = ui_->mazeFilePath->currentText().toStdString();
  try {
    controller_->InitializeMaze(filename);
    ui_->mazeWidget->Initialize();
    ui_->mazeWidget->update();
  } catch (const std::exception& e) {
    QMessageBox err_msg;
    err_msg.information(0, "", e.what());
  }
}

void s21::View::FilePathChange(int idx) {
  ui_->mazeFilePath->setCurrentIndex(idx);
  RenderMaze();
}
