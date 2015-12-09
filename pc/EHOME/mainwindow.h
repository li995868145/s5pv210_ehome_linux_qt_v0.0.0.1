#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QTextCodec>
#include <QTime>
#include <QMessageBox>
#include <pthread.h>
#include <QApplication>
#include "imframe.h"

extern char global_ip[];

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_pushButtonParlourLightOn_clicked();

    void on_pushButtonParlourLightOff_clicked();

    void on_pushButtonCorridorLightOn_clicked();

    void on_pushButtonCorridorLightOff_clicked();

    void on_pushButtonAlarmOn_clicked();

    void on_pushButtonAlarmOff_clicked();

    void on_pushButtonConfigNetwork_clicked();

    void on_dateTimeEditCurtime_dateTimeChanged(const QDateTime &date);

    void on_pushButtonGetTemp_clicked();

    void on_pushButtonMachineMsg_clicked();

    void on_pushButtonChangepwd_clicked();

    void on_pushButtonConfigUart_clicked();

    void on_pushButtonMACScan_clicked();

    void on_pushButtonMacSet_clicked();

    void on_tabWidgetMain_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    void messagebox(QString str);

};


#endif // MAINWINDOW_H
