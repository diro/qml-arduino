TEMPLATE = app

QT += qml quick widgets serialport

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    arduinomgr.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    arduino.qml

HEADERS += \
    arduinomgr.h
