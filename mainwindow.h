#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <entry.h>
#include "filehandler.h"
#include "QListWidgetItem"
#include "filestream.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

     bool checkB_DatePlausibility(QDate, QDate);
     bool checkB_TimePlausibility(QDate, QTime, QDate, QTime);

     void UpdateView(Entry *Object);
     void switchInterface(int);
     void UpdateListView();
     void UpdateListView(QDate Parameter);
     Entry CompileEntry();
     void ResetInputs();
     void InputMode(bool Input);


private slots:
    void on_pushButton_NewTask_clicked();

    void on_pushButton_DeleteTask_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Cancel_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_Edit_clicked();

    void on_checkBox_AllDay_clicked();

    void on_listWidget_TaskList_itemClicked(QListWidgetItem *item);


    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Entry> Data;
    fileHandler *file;
    QVector<QString> ListItems;
    FileStream *Storage;
    filter *Filter;
    Entry SelectedEntry;
    bool EditMode=false;
    bool Help;
};
#endif // MAINWINDOW_H
