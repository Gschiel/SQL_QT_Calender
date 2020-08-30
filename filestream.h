#ifndef FILESTREAM_H
#define FILESTREAM_H
#include <entry.h>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>

class FileStream
{
private:
    QString DataBase;
    QVector<Entry> *Data;
    QSqlDatabase db;


public:
    FileStream();
    FileStream(QVector<Entry> *Data);


    //**********************************Setter*************************************

    //**********************************Getter*************************************


    //********************************Methoden**************************************





};

#endif // FILESTREAM_H
