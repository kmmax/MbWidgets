include(../common.pri)
message("--- Test ---")

QT += testlib
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG 	 += c++14

DEFINES +=



# --- Vars ---

MOC_EXAMPLE_PATH =	# Path to moc files for Example project
win32:CONFIG(release, debug|release): {
        MOC_EXAMPLE_PATH=$$shadowed($$PWD)/../example/release
}
else:win32:CONFIG(debug, debug|release): {
        MOC_EXAMPLE_PATH=$$shadowed($$PWD)/../example/debug
}
else:unix: {
        MOC_EXAMPLE_PATH=$$shadowed($$PWD)/../example
}
message("MOC_EXAMPLE_PATH="$$MOC_EXAMPLE_PATH)



# --- Sources ---

INCLUDEPATH += \
    ../example \
    ../widgets \

SOURCES +=  \
    tst_test_oiserver.cpp \
    ../example/oiserver.cpp \
    ../widgets/converter.cpp \
    ../widgets/data.cpp \
    ../widgets/indicator.cpp \
    ../widgets/led.cpp \
    ../widgets/mbbutton.cpp \
    ../widgets/mbwidget.cpp \
    ../widgets/message.cpp \
        $$MOC_EXAMPLE_PATH/moc_oiserver.cpp


# --- Libraries ---

# MbWidgets
win32:CONFIG(release, debug|release): LIBS += -L$$shadowed($$PWD)/../widgets/release/ -lmbwidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$shadowed($$PWD)/../widgets/debug/ -lmbwidgets
else:unix: LIBS += -L$$shadowed($$PWD)/../widgets/ -lmbwidgets

# IODriver
unix: LIBS += -L$$PWD/../import/IODriverLib/lib/unix64/ -lIODriver
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../import/IODriverLib/lib/win32/ -lIODriver


target.path = $$PROJECT_ROOT_PATH/bin/
INSTALLS    += target
