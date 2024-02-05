#include "s21_view.h"

#include <QFileDialog>
#include <QMessageBox>

#include "s21_labyrinth_widget.h"

s21::View::View(Controller* controller, QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::View), controller_(controller) {
  ui_->setupUi(this);

  connect(ui_->mazeOpenFile, &QPushButton::clicked, this, &View::OpenMazeFile);
  connect(ui_->caveOpenFile, &QPushButton::clicked, this, &View::OpenCaveFile);
  connect(ui_->mazeFilePath, (&QComboBox::currentIndexChanged), this,
          [this]() { FilePathChange(ui_->mazeFilePath); });
  connect(ui_->caveFilePath, (&QComboBox::currentIndexChanged), this,
          [this]() { FilePathChange(ui_->caveFilePath); });

  ui_->mazeWidget->SetController(controller);
  ui_->caveWidget->SetController(controller);
}

s21::View::~View() { delete ui_; }

void s21::View::OpenMazeFile() { OpenFile(ui_->mazeFilePath); }

void s21::View::OpenCaveFile() { OpenFile(ui_->caveFilePath); }

void s21::View::OpenFile(QComboBox* file_path) {
  QString filename = QFileDialog::getOpenFileName(this, tr("Open file:"), "~/",
                                                  tr("Text Files (*.txt)"));
  if (filename.isEmpty()) return;
  auto index = file_path->findText(filename);
  auto count = file_path->count();
  if (index == -1) {
    if (count >= history_max_list_) {
      file_path->removeItem(0);
      count--;
    }
    file_path->addItem(filename);
    index = count;
  }
  file_path->setCurrentIndex(index);
}

void s21::View::Render(s21::Labyrinth* element) {
  element->Initialize();
  element->update();
}

void s21::View::FilePathChange(QComboBox* element) {
  std::string filename = element->currentText().toStdString();
  try {
    if (element == ui_->mazeFilePath) {
      controller_->InitializeMaze(filename);
      Render(ui_->mazeWidget);
    } else if (element == ui_->caveFilePath) {
      controller_->InitializeCave(filename);
      Render(ui_->caveWidget);
    }
  } catch (const std::exception& e) {
    QMessageBox err_msg;
    err_msg.information(0, "", e.what());
  }
}