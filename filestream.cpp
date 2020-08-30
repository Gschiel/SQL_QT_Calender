#include <filestream.h>



FileStream::FileStream(QVector<Entry> *Data)
{
    this->Data=Data;
    db= QSqlDatabase::addDatabase("QODBC3");
    db.setDatabaseName("QT_ICal");
    qDebug()<< db.open();

}
