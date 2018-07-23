#-------------------------------------------------
#
# Project created by QtCreator 2017-03-03T13:07:33
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab01
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    render.cpp \
    conversions.cpp \
    entrypoint.cpp \
    fileworks.cpp \
    matrixworks.cpp \
    model.cpp \
    model_loadparts.cpp \
    actions.cpp \
    canvasworks.cpp

HEADERS  += widget.h \
    render.h \
    entrypoint.h \
    canvasworks.h \
    fileworks.h \
    matrixworks.h \
    model.h \
    model_loadparts.h \
    conversions.h \
    actions.h

FORMS    += widget.ui
