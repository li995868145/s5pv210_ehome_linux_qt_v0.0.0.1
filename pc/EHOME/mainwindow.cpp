#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "message.h"
#include <QDebug>
#include <QTimer>
#include <QProcess>

char global_ip[20];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButtonMachineMsg->setFocus();
//    QTimer *timer=new QTimer();
//    connect(timer,SIGNAL(timeout()),this,SLOT(on_TemperatureTimer_run()));
//    timer->start(5000);


}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * 当点击设置网络的【OK】按钮时
 */
void MainWindow::on_pushButtonConfigNetwork_clicked()
{
    if(ui->lineEditSetNetworkIp->text().length()==0){
        messagebox("IP地址不能为空");
        return;
    }
    struct net_config config;
    strcpy(config.ipv4,ui->lineEditSetNetworkIp->text().toAscii());
    if(machine_net_config(global_ip,(char *)&config)){
        messagebox("网络设置错误");
    }else{
        messagebox("IP地址设置成功，设备重启后请使用新IP登陆");
        ui->lineEditSetNetworkIp->clear();
    }
}
/*新的槽函数*/
void MainWindow::on_pushButtonParlourLightOn_clicked()
{
    int on=O_MCMMAIN_ZIGBEE_REQ_ON;
    if(message_set_zigbee(global_ip,&on)){
        messagebox("设置失败");
    }else{
        ui->labelParlourLight->setText("开启");
//        ui->pushButtonParlourLightOn->setEnabled(false);
//        ui->pushButtonParlourLightOff->setEnabled(true);
    }
}

void MainWindow::on_pushButtonParlourLightOff_clicked()
{
    int off=O_MCMMAIN_ZIGBEE_REQ_OFF;
    if(message_set_zigbee(global_ip,&off)){
        messagebox("设置失败");
    }else{
        ui->labelParlourLight->setText("关闭");
//        ui->pushButtonParlourLightOff->setEnabled(false);
//        ui->pushButtonParlourLightOn->setEnabled(true);
    }
}

void MainWindow::on_pushButtonCorridorLightOn_clicked()
{
}

void MainWindow::on_pushButtonCorridorLightOff_clicked()
{
}

void MainWindow::on_pushButtonAlarmOn_clicked()
{
    if(message_set_alarm(global_ip,1)){
        messagebox("报警器设置失败");
    }else{
        ui->labelAlarm->setText("开启");
    }
}

void MainWindow::on_pushButtonAlarmOff_clicked()
{
    if(message_set_alarm(global_ip,0)){
        messagebox("报警器设置失败");
    }else{
        ui->labelAlarm->setText("关闭");
    }
}

void MainWindow::on_dateTimeEditCurtime_dateTimeChanged(const QDateTime &date)
{
    ui->worldTimeClock->setTime(date.time());
}

void MainWindow::messagebox(QString str)
{
    QMessageBox Msgbox;
    Msgbox.setText(str);
    Msgbox.exec();
}

void MainWindow::on_pushButtonGetTemp_clicked()
{
    int tmp;
     qDebug("get temperature");
     if(message_get_temperature(global_ip,&tmp)){
         messagebox("温度获取错误");
     }else{
         ui->labelTemprature->setText(QString("%1 ‘C").arg(((float)tmp/100)));
     }

}

void MainWindow::on_pushButtonMachineMsg_clicked()
{
    struct machine_info info;

    if(message_get_machine_info(global_ip,(char *)&info)){
        messagebox("查询失败");
    }else{
        ui->labelCpuMHz->setText(QString::number(info.frequency)+" MHz");
        ui->labelFreeMem->setText(QString::number(info.freemem)+" KB");
        ui->labelFreeDisk->setText(QString::number(info.freedisk)+" MB");
    }

}

void MainWindow::on_pushButtonChangepwd_clicked()
{
    struct passwd_info info;
    if((ui->lineEditNewpwd->text().length()==0)&&(ui->lineEditNewpwd->text()!=ui->lineEditVerifyNewpwd->text())){
        messagebox("新密码输入错误");
        return;
    }
    strcpy(info.user,"tarena");
    strcpy(info.oldpwd,ui->lineEditOldpwd->text().toAscii());
    strcpy(info.pwd,ui->lineEditNewpwd->text().toAscii());
    if(change_pwd(global_ip,(char *)&info)){
        messagebox("密码修改错误");
    }else{
        messagebox("密码修改成功，重新登陆请使用新密码");
        ui->lineEditNewpwd->clear();
        ui->lineEditOldpwd->clear();
        ui->lineEditVerifyNewpwd->clear();
//        qApp->quit();
//        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
}




void MainWindow::on_pushButtonConfigUart_clicked()
{
    struct uart_config config;
    /*
        int baudrate;
        char port[16];
        char datawidth;
        char parity;
        char stopbits;
    */
    bool ok;
    config.baudrate=ui->comboBoxSetBaudRate->currentText().toInt(&ok,10);
    strcpy(config.port,ui->comboBoxSetUartPort->currentText().toAscii());
    config.datawidth=(char)ui->comboBoxSetDataBits->currentText().toInt(&ok,10);
    config.parity=(char)ui->comboBoxSetParity->currentText().toAscii()[0];
    config.stopbits=(char)ui->comboBoxSetStopBits->currentText().toInt(&ok,10);

    if(machine_uart_config(global_ip,(char *)&config)){
        messagebox("串口设置错误");
    }else{
        messagebox("串口设置成功");
    }
}

void MainWindow::on_pushButtonMACScan_clicked()
{
    ui->comboBoxPortZigbee1->clear();
    char macs[MAX_ZIGBEE_DEVICE][8]={{0}};

    if(message_get_zigbee_mac(global_ip,(char *)macs)){
        messagebox("zigbee mac地址获取失败");
    }
    for(int i=0;i<MAX_ZIGBEE_DEVICE;i++){
        qDebug("%x %x %x %x %x %x %x %x\n",macs[i][0],macs[i][1],macs[i][2],macs[i][3],macs[i][4],macs[i][5],macs[i][6],macs[i][7]);
        int empty=1;
        for(int j=0;j<8;j++){
            if(macs[i][j]!=0){
                empty=0;
                break;
            }
        }
        if(empty){
            break;
        }else{
            QString t;
            for(int j=0;j<8;j++)
                t += QString::number(macs[i][j]&(0xff), 16).toUpper()+":";
            ui->comboBoxPortZigbee1->addItem(t,Qt::Vertical);
        }
    }
}

void MainWindow::on_pushButtonMacSet_clicked()
{
    struct zigbee_config config;
    QString t=ui->comboBoxPortZigbee1->currentText();
    if(t.length()==0){
        messagebox("未扫描并选定mac地址");
        return;
    }
    QStringList l=t.split(":");
    for(int i=0;i<8;i++){
        bool ok;
        config.zigbee[i]=0xff&l.at(i).toInt(&ok,16);
        qDebug("%x\n",config.zigbee[i]);
    }

    if(machine_zigbee_config(global_ip,(char *)&config)){
        messagebox("设置zigbee MAC地址失败");
    }
}

void MainWindow::on_tabWidgetMain_currentChanged(int index)
{
    qDebug("%d\n",index);
    ui->pushButtonMachineMsg->setFocus();
}
