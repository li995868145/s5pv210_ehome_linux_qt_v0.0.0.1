#-------------------------------------------------
#
# Project created by QtCreator 2013-01-24T14:26:11
#
#-------------------------------------------------

QT       += core gui

TARGET = ehmanager
TEMPLATE = app

INCLUDEPATH += . ../../libs/pclib/include/ ../../eh_server/include/
LIBS += -L ../../libs/pclib/lib/ -lemi


SOURCES += main.cpp\
        logindialog.cpp \
    worldtimeclock.cpp \
    mainwindow.cpp  

HEADERS  += logindialog.h \
    worldtimeclock.h \
    mainwindow.h \
	message.h  

FORMS    += logindialog.ui \
    mainwindow.ui  

RESOURCES += \
    pic/pics.qrc
