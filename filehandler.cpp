#include "filehandler.h"

fileHandler::fileHandler()
{

}

fileHandler::fileHandler(QVector<Entry> *Data, QVector<QString> *ListItems,FileStream *File)
{
this->Data=Data;
this->ListItems=ListItems;
    this->File=File;

}



void fileHandler::setData(QVector<Entry> *Data)
{
    this->Data=Data;
}

Entry fileHandler::ItemSelected(QString Parameter)
{

    QVector<QString> ListItems;
    for(int i=0;i<this->Data->length();i++)
        if(Parameter==this->Data->at(i).getS_ID()){
            return this->Data->at(i);
        }

}

void fileHandler::Save(Entry Object)
{
    Data->push_back(Object);




}

void fileHandler::Save(Entry NewObject, Entry OldObject)
{
   for (int i=0;i<Data->length();i++){
       if (OldObject.getS_ID()==Data->at(i).getS_ID()){
           Data->replace(i,NewObject);


       }
   }
}

void fileHandler::Delete(Entry Object){
    for(int i=0;i<this->Data->length();i++)
        if(Object.getS_ID()==this->Data->at(i).getS_ID()){
            Data->removeAt(i);
        }

}

