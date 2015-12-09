#ifndef __LOGINDIALOG_H__
#define __LOGINDIALOG_H__

#include <QDialog>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <QTextDecoder>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();


private slots:
    void on_pushButtonConnect_clicked();

    void on_pushButtonCancle_clicked();

private:
    Ui::LoginDialog *ui;
	void messagebox(QString);

};
#endif // LOGINDIALOG_H
