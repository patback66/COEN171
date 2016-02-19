TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    book.cpp \
    store.cpp \
    person.cpp \
    owner.cpp \
    client.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    book.h \
    store.h \
    person.h \
    owner.h \
    client.h

