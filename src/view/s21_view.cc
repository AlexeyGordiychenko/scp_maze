#include "s21_view.h"

#include <QFileDialog>
#include <QMessageBox>

s21::View::View(Controller* controller, QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::View), controller_(controller) {
  ui_->setupUi(this);

  connect(ui_->openFile, &QPushButton::clicked, this, &View::OpenFile);
}

s21::View::~View() { delete ui_; }

void s21::View::OpenFile() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open maze file:"), "~/", tr("Maze Files (*.txt)"));
  if (filename.isEmpty()) return;
  auto index = ui_->filePath->findText(filename);
  auto count = ui_->filePath->count();
  if (index == -1) {
    if (count >= history_max_list_) {
      ui_->filePath->removeItem(0);
      count--;
    }
    ui_->filePath->addItem(filename);
    index = count;
  }
  FilePathChange(index);
}

void s21::View::RenderMaze() {
  if (file_changed_) {
    std::string filename = ui_->filePath->currentText().toStdString();
    try {
      controller_->Initialize(filename);
      file_changed_ = false;
    } catch (const std::exception& e) {
      QMessageBox err_msg;
      err_msg.information(0, "", e.what());
    }
    // } else {
    // controller_->RestoreVertices();
  }
}

void s21::View::FilePathChange(int idx) {
  ui_->filePath->setCurrentIndex(idx);
  file_changed_ = true;
}
