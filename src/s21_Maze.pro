QT += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -fmax-errors=1

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    s21_main.cc \
    view/s21_view.cc \
    view/s21_maze_widget.cc \
    model/s21_model.cc \
    controller/s21_controller.cc

HEADERS += \
    view/s21_view.h \
    view/s21_maze_widget.h \
    model/s21_model.h \
    controller/s21_controller.h

FORMS += \
    view/s21_view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

