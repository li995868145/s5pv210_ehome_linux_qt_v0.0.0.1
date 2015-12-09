#ifndef IMFRAME_H
#define IMFRAME_H

#include <QWSInputMethod>
#include "keyboard.h"


class imFrame:public QWSInputMethod
{
Q_OBJECT
public:
    imFrame();
    ~imFrame();
    void updateHandler(int);
    void sendpreeditContent(const QString &);

private:
    keyboard *kbd;
    QString inputString;



};

#endif // IMFRAME_H
