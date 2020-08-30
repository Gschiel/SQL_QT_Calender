#ifndef FILTER_H
#define FILTER_H
#include "entry.h"
#include "QVector"


class filter
{
private:
    QVector<Entry> *Data;
    QDate D_Param;
    QVector<QString> *ListItems;




public:
    filter();
    filter(QVector<Entry> *Data,QVector<QString> *ListItems);

    void FilterList(QDate D_Param);

};

#endif // FILTER_H
