QT += core gui
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -fmax-errors=1

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    scp_main.cc \
    view/scp_view.cc \
    view/scp_maze_widget.cc \
    view/scp_cave_widget.cc \
    model/scp_model.cc \
    model/scp_maze.cc \
    model/scp_cave.cc \
    controller/scp_controller.cc

HEADERS += \
    view/scp_view.h \
    view/scp_labyrinth_widget.h \
    view/scp_maze_widget.h \
    view/scp_cave_widget.h \
    view/scp_value_slider.h \
    model/scp_model.h \
    model/scp_labyrinth.h \
    model/scp_parser.h \
    model/scp_maze.h \
    model/scp_cave.h \
    controller/scp_controller.h

FORMS += \
    view/scp_view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

