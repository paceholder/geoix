#-------------------------------------------------
#
# Project created by QtCreator 2011-05-06T14:52:05
#
#-------------------------------------------------

QT       -= core gui

TARGET = fourier
TEMPLATE = lib

DEFINES += FOURIER_LIBRARY

SOURCES += \
    kiss_fft.c

HEADERS +=\
        fourier_global.h \
    kiss_fft.h \
    _kiss_fft_guts.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE013DC02
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = fourier.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
