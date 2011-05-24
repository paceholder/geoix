# -------------------------------------------------
# Project created by QtCreator 2011-05-06T14:52:05
# -------------------------------------------------
TARGET = fourier3d
TEMPLATE = app
FORMS += mainwindow.ui
HEADERS += mainwindow.h \
    welldata.h \
    ../fourier.h \
    _kiss_fft_guts.h \
    kiss_fft.h \
    ../rbf_core.h \
    ../point3D.h \
    fourierinterpolator.h
SOURCES += main.cpp \
    welldata.cpp \
    ../fourier.cpp \
    kiss_fft.cpp \
    ../rbf_core.cpp \
    ../point3D.cpp \
    fourierinterpolator.cpp \
    mainwindow.cpp
