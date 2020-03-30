#-------------------------------------------------
#
# Project created by QtCreator 2020-01-09T13:47:16
#
#-------------------------------------------------

include(../common.pri)
message("--- Example ---")
message("OS_SUFFIX="$$OS_SUFFIX)


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = GSymbolExample
TARGET = MbWidgetExample
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
    dialog.cpp \
    oiserver.cpp

HEADERS += \
    dialog.h \
    oiserver.h

FORMS += \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += $$PWD/../widgets
DEPENDPATH += $$PWD/../widgets

INCLUDEPATH += $$PWD/import/IODriverLib/includes
INCLUDEPATH += $$PWD/import/libmodbus/includes

#LIBS += -L../build-widgets-Desktop_Qt_5_11_1_GCC_64bit-Release -lmbwidgets

win32:CONFIG(release, debug|release): LIBS += -L$$shadowed($$PWD)/../widgets/release/ -lmbwidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$shadowed($$PWD)/../widgets/debug/ -lmbwidgets
else:unix: LIBS += -L$$shadowed($$PWD)/../widgets/ -lmbwidgets

unix: LIBS += -L$$PWD/../import/IODriverLib/lib/unix64/ -lIODriver
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../import/IODriverLib/lib/win32/ -lIODriver

message("LIBS = "$$LIBS)

target.path = $$PROJECT_ROOT_PATH/bin/
INSTALLS    += target

message("BIN="$$PROJECT_ROOT_PATH)
copy_to_build.path = $$PROJECT_ROOT_PATH/bin/
copy_to_build.files = $$PROJECT_ROOT_PATH/import/libmodbus/lib/unix64/*
INSTALLS += \
        copy_to_build \

