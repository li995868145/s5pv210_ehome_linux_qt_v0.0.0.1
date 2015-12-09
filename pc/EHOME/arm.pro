#-------------------------------------------------
#
# Project created by QtCreator 2013-01-24T14:26:11
#
#-------------------------------------------------

QT       += core gui

TARGET = bdehmanager
TEMPLATE = app

INCLUDEPATH += . ../../libs/include/ ../../eh_server/include/
LIBS += -L ../../libs/lib/ -lemi


SOURCES += main.cpp\
        logindialog.cpp \
    worldtimeclock.cpp \
    imframe.cpp \
    keyboard.cpp \
    mainwindow.cpp 

HEADERS  += logindialog.h \
    worldtimeclock.h \
    mainwindow.h \
    imframe.h \
    keyboard.h \
	message.h 

FORMS    += logindialog.ui \
    keyboard.ui \ 
    mainwindow.ui 

RESOURCES += \
    pic/pics.qrc

DEFINES += "ONBOARD"
