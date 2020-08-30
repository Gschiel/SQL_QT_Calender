#include "entry.h"

//Constructor
Entry::Entry()
{
 this->setS_ID("Error");
}

Entry::~Entry()
{

}

//Setter
void Entry::setS_ID()
{
    this->S_ID = createS_ID(getD_Start(), getT_Start(), getD_End(), getT_End(), getS_Title(), getI_Status(), getI_Priority());
}

void Entry::setS_ID(QString pS_ID)
{
    this->S_ID = pS_ID;
}

void Entry::setD_Start(QDate pD_Start)
{
    this->D_Start = pD_Start;
}

void Entry::setT_Start(QTime pT_Start)
{
    this->T_Start = pT_Start;
}

void Entry::setD_End(QDate pD_End)
{
    this->D_End = pD_End;
}

void Entry::setT_End(QTime pT_End)
{
    this->T_End = pT_End;
}

void Entry::setS_Title(QString pS_Title)
{
    this->S_Title = pS_Title;
}

void Entry::setS_Description(QString pS_Description)
{
    this->S_Description = pS_Description;
}

void Entry::setI_Status(int pI_Status)
{
    if (pI_Status!=0){
       this->I_Status = pI_Status;
    }
    else{
         this->I_Status = 1;
    }

}

void Entry::setI_Priority(int pI_Priority)
{
    if (pI_Priority!=0){
        this->I_Priority = pI_Priority;
    }
    else{
        this->I_Priority=2;
    }

}

void Entry::setB_AllDay(bool pB_AllDay)
{
    this->B_AllDay = pB_AllDay;
}

//Getter
QString Entry::getS_ID() const
{
    return S_ID;
}

QDate Entry::getD_Start() const
{
    return D_Start;
}

QTime Entry::getT_Start() const
{
    return T_Start;
}

QDate Entry::getD_End() const
{
    return D_End;
}

QTime Entry::getT_End() const
{
    return T_End;
}

QString Entry::getS_Title() const
{
    return S_Title;
}

QString Entry::getS_Description() const
{
    return S_Description;
}

int Entry::getI_Status() const
{
    return I_Status;
}

int Entry::getI_Priority() const
{
    return I_Priority;
}

bool Entry::getB_AllDay() const
{
    return B_AllDay;
}

//Methods
QString Entry::createS_ID(QDate pD_Start, QTime pT_Start, QDate pD_End, QTime pT_End, QString pS_Title, int pI_Status, int pI_Priority) //formatted ID for use in list-widget
{    
    QString Status;
    QString Priority;

    switch(pI_Status){
    case 1: Status = "inPr";
            break;
    case 2: Status = "Done";
            break;
    }

    if(pI_Priority==1){
            Priority = " ! ";
    }
    else{
            Priority = "   ";
    }

    QString pS_ID;
    if(pD_Start==pD_End){
        pS_ID=pT_Start.toString("hh:mm")+(" - ")+pT_End.toString("hh:mm")+(Priority)+(Status)+("  ")+pS_Title;
    }
    else{
        pS_ID=pD_Start.toString("dd.MM")+(" - ")+pD_End.toString("dd.MM")+(Priority)+(Status)+("  ")+pS_Title;
    }
    return pS_ID;
}




