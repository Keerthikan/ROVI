TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    histogram.cpp \
    equalization.cpp \
    calchistogram.cpp \
    ContraHarmonic.cpp \
    fourier.cpp \
    notch.cpp \
    eq_kid.cpp
LIBS += `pkg-config opencv --libs`

HEADERS += \
    histogram.h \
    equalization.h \
    calchistogram.h \
    ContraHarmonic.h \
    fourier.h \
    notch.h \
    eq_kid.h
