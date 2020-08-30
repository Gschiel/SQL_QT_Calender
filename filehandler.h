#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <entry.h>
#include <filestream.h>
#include "filter.h"


class fileHandler
{
private:
    FileStream *File;
    QVector<Entry> *Data;
    QVector<QString> *ListItems;

public:
    fileHandler();
    fileHandler(QVector<Entry> *Data, QVector<QString> *ListItems,FileStream *File);

   //**********************************Setter*************************************
    void CreateFile();
    void setData(QVector<Entry> *Data);


   //**********************************Getter*************************************


    //********************************Methoden**************************************
    Entry ItemSelected(QString Parameter);
    void Save(Entry Object);
    void Save(Entry NewObject,Entry OldObject);
    void Delete(Entry Object);


};

#endif // FILEHANDLER_H
