#ifndef FOURIER_GLOBAL_H
#define FOURIER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FOURIER_LIBRARY)
#  define FOURIERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FOURIERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FOURIER_GLOBAL_H
