#ifndef ENTRY_H
#define ENTRY_H
#include <QString>
#include <QDate>
#include <QTime>


class Entry
{
private:
    QString	S_ID;        		//StartZeit – EndZeit Title     Regulär //StartDatum „bis“ EndDatum Title  Termin länger als 24H
    QDate D_Start;
    QTime T_Start;
    QDate D_End;
    QTime T_End;
    QString	 S_Title;
    QString S_Description;
    int	I_Status;
    int I_Priority;
    bool B_AllDay;
    bool B_DatePlausibility;
    bool B_TimePlausibility;

public:
    //Constructor
    Entry();

    ~Entry();

    //Setter
    void setS_ID();//creates S_ID with getters
    void setS_ID(QString);        		//StartZeit – EndZeit Title     Regulär //StartDatum „bis“ EndDatum Title  Termin länger als 24H
    void setD_Start(QDate);
    void setT_Start(QTime);
    void setD_End(QDate);
    void setT_End(QTime);
    void setS_Title(QString);
    void setS_Description(QString);
    void setI_Status(int);
    void setI_Priority(int);
    void setB_AllDay(bool);

    //Getter
    QString	getS_ID() const;        		//StartZeit – EndZeit Title     Regulär //StartDatum „bis“ EndDatum Title  Termin länger als 24H
    QDate getD_Start() const;
    QTime getT_Start() const;
    QDate getD_End() const;
    QTime getT_End() const;
    QString	 getS_Title() const;
    QString getS_Description() const;
    int	getI_Status() const;
    int	getI_Priority() const;
    bool getB_AllDay() const;

    //Methods
    QString createS_ID(QDate, QTime, QDate, QTime, QString, int, int);

};

#endif // ENTRY_H
