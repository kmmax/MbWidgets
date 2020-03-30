include(../common.pri)
message("--- plugins ---")

CONFIG      += plugin debug_and_release
#TARGET      = $$qtLibraryTarget(modbuswidgetcollectionplugin)
TARGET      = modbuswidgetcollectionplugin
TEMPLATE    = lib

CONFIG += c++14

HEADERS     = \
        mbbuttonplugin.h \
        mbmessageplugin.h \
        mbindicatorplugin.h \
        mbledplugin.h \
        modbuswidgetcollection.h \

SOURCES     = \
        mbbuttonplugin.cpp \
        mbmessageplugin.cpp \
        mbindicatorplugin.cpp \
        mbledplugin.cpp \
        modbuswidgetcollection.cpp \


RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$MX_INSTALL_PLUGINS/designer
INSTALLS    += target
message("target.path="$$target.path)

include(mbwidget.pri)
include(mbbutton.pri)
include(mbmessage.pri)
include(mbindicator.pri)

DISTFILES +=

