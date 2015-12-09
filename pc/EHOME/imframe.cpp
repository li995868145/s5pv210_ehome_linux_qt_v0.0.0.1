#include "imframe.h"

imFrame::imFrame()
{
    kbd=new keyboard(this);
}

imFrame::~imFrame()
{

}

void imFrame::sendpreeditContent(const QString &newString)
{
    if(newString == "Del")
    {
        inputString.resize(inputString.length()-1);
        this->sendPreeditString(inputString,0);
        qDebug("%s\n",qPrintable(inputString));
    }
    else if(newString == "Enter"){
        sendCommitString(inputString);
        inputString.clear();
    }
    else
    {
        inputString += newString;
        this->sendPreeditString(inputString,0);
    }
}


void imFrame::updateHandler(int type)
{
    if(type==QWSInputMethod::FocusIn){
        kbd->setGeometry(0,270,800,210);
        kbd->show();
    }else if(type==QWSInputMethod::FocusOut){
        inputString.clear();
        kbd->hide();
    }
}

