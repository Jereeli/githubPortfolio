TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        music.cpp \
        cli.cpp \
        utilities.cpp

HEADERS += \
    music.hh \
    cli.hh \
    utilities.hh
