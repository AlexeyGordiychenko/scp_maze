#include "s21_view.h"

#include <QFileDialog>
#include <QMessageBox>

#include "s21_labyrinth_widget.h"

s21::View::View(Controller* controller, QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::View), controller_(controller) {
  ui_->setupUi(this);

  // Stop the play timer if any of the buttons is pressed
  connect(ui_->caveOpenFile, &QPushButton::clicked, this, &View::StopTimer);
  connect(ui_->tabWidget, (&QTabWidget::currentChanged), this,
          &View::StopTimer);
  connect(ui_->caveFilePath, (&QComboBox::currentIndexChanged), this,
          &View::StopTimer);
  connect(ui_->caveGenerateBtn, &QPushButton::clicked, this, &View::StopTimer);
  connect(ui_->caveNextStep, &QPushButton::clicked, this, &View::StopTimer);
  connect(ui_->caveSaveBtn, &QPushButton::clicked, this, &View::StopTimer);

  // Normal slots
  connect(ui_->mazeOpenFile, &QPushButton::clicked, this, &View::OpenMazeFile);
  connect(ui_->caveOpenFile, &QPushButton::clicked, this, &View::OpenCaveFile);
  connect(ui_->mazeFilePath, (&QComboBox::currentIndexChanged), this,
          [this]() { FilePathChange(ui_->mazeFilePath); });
  connect(ui_->caveFilePath, (&QComboBox::currentIndexChanged), this,
          [this]() { FilePathChange(ui_->caveFilePath); });

  connect(ui_->caveGenerateBtn, &QPushButton::clicked, this,
          [this]() { GenerateLabyrinth(ui_->caveFilePath); });

  connect(ui_->caveNextStep, &QPushButton::clicked, this,
          &View::GenerateCaveNextStep);
  connect(ui_->cavePlay, &QPushButton::clicked, this, &View::GenerateCavePlay);
  connect(&timer_, &QTimer::timeout, this, &View::GenerateCaveNextStep);

  connect(ui_->mazeSaveBtn, &QPushButton::clicked, this,
          [this]() { SaveLabyrinth(ui_->mazeFilePath); });
  connect(ui_->caveSaveBtn, &QPushButton::clicked, this,
          [this]() { SaveLabyrinth(ui_->caveFilePath); });

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

void s21::View::Render(s21::LabyrinthWidget* element) {
  element->Initialize();
  element->update();
}

void s21::View::FilePathChange(QComboBox* element) {
  std::string filename = element->currentText().toStdString();
  if (filename.empty()) return;
  auto index = element->findText("");
  if (index) element->removeItem(index);
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

void s21::View::GenerateLabyrinth(QComboBox* element) {
  std::string filename = element->currentText().toStdString();
  if (!filename.empty()) {
    element->addItem("");
    element->setCurrentIndex(element->count());
  }
  if (element == ui_->mazeFilePath) {
  } else if (element == ui_->caveFilePath) {
    controller_->GenerateCave(ui_->caveChance->value(),
                              ui_->caveNumRows->value(),
                              ui_->caveNumCols->value());
    Render(ui_->caveWidget);
  }
}

void s21::View::GenerateCaveNextStep() {
  auto res = controller_->CaveCellularAutomaton(ui_->caveBirthSlider->value(),
                                                ui_->caveDeathSlider->value());
  if (res)
    Render(ui_->caveWidget);
  else
    StopTimer();
}

void s21::View::GenerateCavePlay() {
  if (timer_.isActive()) {
    StopTimer();
  } else {
    StartTimer();
  }
}

void s21::View::StopTimer() {
  timer_.stop();
  ui_->cavePlay->setIcon(QIcon::fromTheme("media-playback-start"));
  ui_->cavePlay->setText("Play");
}

void s21::View::StartTimer() {
  timer_.start(ui_->caveDelay->value());
  ui_->cavePlay->setIcon(QIcon::fromTheme("media-playback-stop"));
  ui_->cavePlay->setText("Stop");
}

void s21::View::SaveLabyrinth(QComboBox* element) {
  auto labyrinth_text = ui_->tabWidget->tabText(ui_->tabWidget->currentIndex());
  QFileDialog save_dialog(this);
  save_dialog.setDefaultSuffix(".txt");
  QString file_name = save_dialog.getSaveFileName(
      this, labyrinth_text + " saving", "", "Text files (*.txt)");
  if (!file_name.isEmpty()) {
    if (QFileInfo(file_name).suffix().isEmpty()) {
      file_name += ".txt";
    }
    QString msg_text = labyrinth_text + " saved successfully.";
    try {
      if (element == ui_->mazeFilePath) {
        controller_->SaveMaze(file_name.toStdString());
      } else if (element == ui_->caveFilePath) {
        controller_->SaveCave(file_name.toStdString());
      }
    } catch (const std::exception& e) {
      msg_text = e.what();
    }
    QMessageBox msg;
    msg.information(0, "", msg_text);
  }
}
