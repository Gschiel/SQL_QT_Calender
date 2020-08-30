#include "filter.h"
#include "entry.h"
#include "QDebug"

filter::filter()
{

}

filter::filter(QVector<Entry> *Data,QVector<QString> *ListItems)
{
   this->Data=Data;
    this->ListItems=ListItems;
}

void filter::FilterList(QDate D_Param)
{
    this->ListItems->clear();
    QString Temp;
    for (int i=0;i<this->Data->length();i++){
        if (Data->at(i).getD_Start().daysTo(Data->at(i).getD_End())==0)
        {
            if (Data->at(i).getD_Start()==D_Param)
            {
                Temp=Data->at(i).getS_ID();
                ListItems->push_back(Temp);
            }
            else{ continue;}
        }
        else
        {
            for (int y=0;y<=Data->at(i).getD_Start().daysTo(Data->at(i).getD_End());y++)
            {
                QDate TempDate=Data->at(i).getD_Start();
                TempDate=TempDate.addDays(y);
                 if (TempDate==D_Param)
                 {
                     Temp=Data->at(i).getS_ID();
                     ListItems->push_back(Temp);
                     break;
                 }
            }
        }
    }
    for (int i=0;i<ListItems->length();i++){
        qDebug()<<ListItems->at(i);
    }


}
