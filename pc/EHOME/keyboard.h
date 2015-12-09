#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QSignalMapper>
#include <QWSInputMethod>

namespace Ui {
class keyboard;
}

class imFrame;

class keyboard : public QWidget
{
    Q_OBJECT
    
public:
    explicit keyboard(imFrame *im);
    ~keyboard();
    QSignalMapper* mapper;

public slots:
    void prepare_outline(const QString);
signals:
    void commit_string(QString str);
    
private:
    Ui::keyboard *ui;
    imFrame *im;
};

#endif // KEYBOARD_H
