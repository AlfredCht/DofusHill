#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>

*.qrc
*.pro.user
*.DS_Store
 QT += widgets

TEMPLATE = app
TARGET = "Dofus hill"
INCLUDEPATH += .


SOURCES += \
    main.cpp \
    perso.cpp \
    bouftouroyal.cpp \
    tir.cpp \
    croca.cpp \
    boufton.cpp \
    bouledefeu.cpp \
    powerups.cpp \
    game.cpp

HEADERS += \
    perso.h \
    bouftouroyal.h \
    tir.h \
    croca.h \
    boufton.h \
    bouledefeu.h \
    powerups.h \
    game.h

RESOURCES += \
    ressources.qrc
