QMAKE_MAC_SDK = macosx10.13
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp + standard.cpp + planet.cpp + planet.h
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -larmadillo -llapack -lblas
