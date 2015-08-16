#-------------------------------------------------
#
# Project created by QtCreator 2015-08-10T19:34:40
#
#-------------------------------------------------


QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport


TARGET = qcustomplot
CONFIG(debug, debug|release) {
  TARGET = $$join(TARGET,,,d) # if compiling in debug mode, append a "d" to the library name
  QMAKE_TARGET_PRODUCT = "QCustomPlot (debug mode)"
  QMAKE_TARGET_DESCRIPTION = "Plotting library for Qt (debug mode)"
} else {
  QMAKE_TARGET_PRODUCT = "QCustomPlot"
  QMAKE_TARGET_DESCRIPTION = "Plotting library for Qt"
}
QMAKE_TARGET_COMPANY = "www.qcustomplot.com"
QMAKE_TARGET_COPYRIGHT = "Copyright (C) by Emanuel Eichhammer"


SOURCES += main.cpp\
    qcustomplot.cpp

HEADERS  += \
    qcustomplot.h

FORMS    += plottermainwindow.ui
