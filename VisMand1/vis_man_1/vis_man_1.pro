TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    histogram.cpp \
    equalization.cpp \
    calchistogram.cpp
LIBS += `pkg-config opencv --libs`

HEADERS += \
    histogram.h \
    equalization.h \
    calchistogram.h
