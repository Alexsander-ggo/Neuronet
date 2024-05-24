QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

SOURCES += \
        Form.cpp \
        LayerNN.cpp \
        Neuronet.cpp \
        main.cpp \
        qcustomplot.cpp

HEADERS += \
    Form.h \
    LayerNN.h \
    Neuronet.h \
    qcustomplot.h

FORMS += \
    Form.ui
