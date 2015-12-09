#include "keyboard.h"
#include "ui_keyboard.h"
#include "imframe.h"


keyboard::keyboard(imFrame *pim) :
            QWidget(0,Qt::Tool|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint),
    ui(new Ui::keyboard)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::NoFocus);
    im=pim;

    mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(const QString)), this, SLOT(prepare_outline(const QString)));
    mapper->setMapping(ui->pushButtondel, "Del");
    connect(ui->pushButtondel, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonenter, "Enter");
    connect(ui->pushButtonenter, SIGNAL(clicked()), mapper, SLOT(map()));

    mapper->setMapping(ui->pushButton1, "1");
    connect(ui->pushButton1, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton2, "2");
    connect(ui->pushButton2, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton3, "3");
    connect(ui->pushButton3, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton4, "4");
    connect(ui->pushButton4, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton5, "5");
    connect(ui->pushButton5, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton6, "6");
    connect(ui->pushButton6, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton7, "7");
    connect(ui->pushButton7, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton8, "8");
    connect(ui->pushButton8, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton9, "9");
    connect(ui->pushButton9, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButton0, "0");
    connect(ui->pushButton0, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonq, "q");
    connect(ui->pushButtonq, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonw, "w");
    connect(ui->pushButtonw, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtone, "e");
    connect(ui->pushButtone, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonr, "r");
    connect(ui->pushButtonr, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtont, "t");
    connect(ui->pushButtont, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtony, "y");
    connect(ui->pushButtony, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonu, "u");
    connect(ui->pushButtonu, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtoni, "i");
    connect(ui->pushButtoni, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtono, "o");
    connect(ui->pushButtono, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonp, "p");
    connect(ui->pushButtonp, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtona, "a");
    connect(ui->pushButtona, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtons, "s");
    connect(ui->pushButtons, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtond, "d");
    connect(ui->pushButtond, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonf, "f");
    connect(ui->pushButtonf, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtong, "g");
    connect(ui->pushButtong, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonh, "h");
    connect(ui->pushButtonh, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonj, "j");
    connect(ui->pushButtonj, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonk, "k");
    connect(ui->pushButtonk, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonl, "l");
    connect(ui->pushButtonl, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonz, "z");
    connect(ui->pushButtonz, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonx, "x");
    connect(ui->pushButtonx, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonc, "c");
    connect(ui->pushButtonc, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonv, "v");
    connect(ui->pushButtonv, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonb, "b");
    connect(ui->pushButtonb, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonn, "n");
    connect(ui->pushButtonn, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonm, "m");
    connect(ui->pushButtonm, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtoncomma, ",");
    connect(ui->pushButtoncomma, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->pushButtonfullstop, ".");
    connect(ui->pushButtonfullstop, SIGNAL(clicked()), mapper, SLOT(map()));

}

keyboard::~keyboard()
{
    delete ui;
}

void keyboard::prepare_outline(const QString s){
    qDebug("kbd: %s",qPrintable(s));
    im->sendpreeditContent(s);
}
