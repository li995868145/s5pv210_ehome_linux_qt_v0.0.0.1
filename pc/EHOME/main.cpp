#include <QtGui/QApplication>
#include "logindialog.h"
#include "mainwindow.h"
#include "imframe.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));        //支持Tr中文
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8")); //支持中文文件名显示



#ifdef ONBOARD
	strcpy(global_ip,"127.0.0.1");
	MainWindow mainwindow;
	mainwindow.setWindowFlags(Qt::FramelessWindowHint);
	mainwindow.show();
    mainwindow.setGeometry(0,0,800,480);

    imFrame *im=new imFrame;
    QWSServer::setCurrentInputMethod(im);

#else

    LoginDialog w;
    w.show();

	if (w.exec() == QDialog::Accepted)
	{
    	MainWindow mainwindow;
        mainwindow.show();
        return a.exec();

	}
	else
	{
		return -1;
	}
#endif

	return a.exec();

}
