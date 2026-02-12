QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include

HEADERS += \
    include/card.h \
    include/comparecards.h \
    include/gameplayer.h \
    include/gametable.h \
    include/generator.h \
    include/setupwidget.h \
    include/texaswidget.h

SOURCES += \
    src/card.cpp \
    src/comparecards.cpp \
    src/gameplayer.cpp \
    src/gametable.cpp \
    src/generator.cpp \
    src/main.cpp \
    src/setupwidget.cpp \
    src/texaswidget.cpp

FORMS += \
    ui/setupwidget.ui \
    ui/texaswidget.ui

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
