########################################
### \author JackeyLea
### \date 2024-01-14
### \brief 单元测试
########################################

QT += core testlib

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include

HEADERS += \
    include/texaspokertest.h \
    include/card.h \
    include/comparecards.h

SOURCES += \
        src/main.cpp \
        src/texaspokertest.cpp \
        src/comparecards.cpp \
        src/card.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
