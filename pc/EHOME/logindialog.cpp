
#include "logindialog.h"
#include "ui_logindialog.h"
#include "message.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
}

void LoginDialog::on_pushButtonConnect_clicked()
{

    if (0 == ui->lineEditUsername->displayText().length()
            || 0 == ui->lineEditPassword->displayText().length())
    {
        ui->labelLoginMessage->setText(tr("用户名或者密码不能为空"));
        return;
    }

    // 判断是否输入为空
    if (0 == ui->lineEditIp->displayText().length())
    {
        ui->labelLoginMessage->setText(tr("ip不能为空"));
        return;
    }

	strcpy(global_ip,ui->lineEditIp->displayText().toLocal8Bit());

    struct passwd_info info;
    strcpy(info.user,ui->lineEditUsername->text().toAscii());
    strcpy(info.pwd,ui->lineEditPassword->text().toAscii());
    if(machine_login(global_ip,(char *)&info)){
		ui->labelLoginMessage->setText("登陆失败");
		return ;
	}
/*
    if (retContent == 0)
    {
        ui->labelLoginMessage->setText(tr("用户名或者密码错误"));
        return;
    }
*/
    QDialog::accept();
}


void LoginDialog::on_pushButtonCancle_clicked()
{
    QDialog::reject();
}


