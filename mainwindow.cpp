#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Storage= new FileStream(&Data);
    file= new fileHandler(&Data,&ListItems,Storage);
    Filter= new filter(&Data,&ListItems);
    ResetInputs();
    UpdateListView();
    EditMode=false;
    ui->calendarWidget->setEnabled(true);
    ui->lbl_Help->setVisible(false);
    Help=false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_NewTask_clicked()
{
    ResetInputs();
    InputMode(true);
}

void MainWindow::on_pushButton_DeleteTask_clicked()
{
    file->Delete(SelectedEntry);
    //delete current list item
    if(ui->listWidget_TaskList->currentItem()!=nullptr)
    {    delete this->ui->listWidget_TaskList->currentItem();   }
    ResetInputs();
}

void MainWindow::on_pushButton_Save_clicked()
{

    Entry newEntry;
    newEntry=CompileEntry();
    if (newEntry.getS_ID()!="Error")
    {
        if(EditMode){
            file->Save(newEntry,SelectedEntry);
            ResetInputs();
            UpdateView(&newEntry);
        }
        else{
            file->Save(newEntry);
            ResetInputs();
            UpdateView(&newEntry);
        }
    }
    UpdateListView();
}

void MainWindow::on_pushButton_Cancel_clicked()
{
    InputMode(false);
    ResetInputs();
    UpdateView(&SelectedEntry);
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{   
    ResetInputs();
    UpdateListView(date);
}

void MainWindow::on_pushButton_Edit_clicked()
{
    if(ui->listWidget_TaskList->currentItem()!=nullptr){
            InputMode(true);
            EditMode=true;
        }
}

bool MainWindow::checkB_DatePlausibility(QDate pD_Start, QDate pD_End)
{
    if(pD_Start<=pD_End){
        return 1;//ok, da Enddatum nicht vor Startdatum
    }
    else return 0;
}

bool MainWindow::checkB_TimePlausibility(QDate pD_Start, QTime pT_Start, QDate pD_End, QTime pT_End)
{
    if(pD_Start==pD_End && pT_Start>pT_End){
        return 0;//nicht ok, da Startzeit nach Endzeit
    }
    else return 1;
}

void MainWindow::UpdateView(Entry *Object)
{
    QString TempString;
    //********************Title***************************
    ui->lineEdit_Title->setText(Object->getS_Title());
    ui->lbl_View_Title->setText(Object->getS_Title());

    //********************Descripion***************************
    ui->textEdit->setPlainText(Object->getS_Description());
    ui->lbl_View_Description->setText(Object->getS_Description());

    //********************Date and Time***************************
    ui->dateEdit_Start->setDate(Object->getD_Start());
    ui->dateEdit_End->setDate(Object->getD_End());
    ui->timeEdit_From->setTime(Object->getT_Start());
    ui->timeEdit_Until->setTime(Object->getT_End());
    if (Object->getB_AllDay()==true){
        if (Object->getD_Start()==Object->getD_End()){
            if (QDate::currentDate()==Object->getD_Start()){
                TempString=("Today whole day");
            }
            else{
                TempString="Whole Day at: " + Object->getD_Start().toString("ddd dd MMM yyyy");
            }
        }
        else{
            TempString="From "+ Object->getD_Start().toString("ddd dd MMM ") +"\n" +
                    "Until  "+ Object->getD_End().toString("ddd dd MMM yyyy");
        }
    }
    else{
        if(QDate::currentDate()==Object->getD_Start()){
           TempString="Today from: "+ Object->getT_Start().toString("hh:mm") + "\nUntil  " + Object->getT_End().toString("hh:mm");
        }
        else{
            TempString= "From "+Object->getD_Start().toString("ddd dd MMM ")+ Object->getT_Start().toString("hh:mm") + "\nUntil  " +Object->getD_End().toString("ddd dd MMM ")+ Object->getT_End().toString("hh:mm");
        }
    }
    ui->lbl_ViewTiming->setText(TempString);

    //********************Status***************************
    ui->comboBox_TaskStatus->setCurrentIndex(Object->getI_Status());
    QString Status;
    switch (Object->getI_Status()) {
        case 0: Status="";break;
        case 1: Status=("In Progress");break;
        case 2: Status=("Done");break;
    }
    ui->lbl_View_Status->setText("Status: "+Status);

    //********************Priority***************************
    ui->comboBox_Priority->setCurrentIndex(Object->getI_Priority());
    QString Priority;
    switch (Object->getI_Priority()) {
        case 0: Priority="";break;
        case 1: Priority="High";break;
        case 2: Priority="Normal";break;
    }
    ui->lbl_View_Priority->setText("Priority: "+Priority);
}

void MainWindow::on_checkBox_AllDay_clicked()
{
    if(ui->checkBox_AllDay->isChecked()){
        QTime beforeMidnight(23,59);
        QTime Midnight(0,0);
        ui->timeEdit_From->setTime(Midnight);
        ui->timeEdit_From->setEnabled(false);
        ui->timeEdit_Until->setTime(beforeMidnight);
        ui->timeEdit_Until->setEnabled(false);

    }
    else{
        ui->timeEdit_From->setTime(QTime::currentTime());
        ui->timeEdit_From->setEnabled(true);
        ui->timeEdit_Until->setTime(QTime::currentTime());
        ui->timeEdit_Until->setEnabled(true);
    }
}

void MainWindow::on_listWidget_TaskList_itemClicked(QListWidgetItem *item)
{
    QString Parameter=item->text();
    SelectedEntry =file->ItemSelected(Parameter);
    UpdateView(&SelectedEntry);
}

void MainWindow::UpdateListView()
{
  ui->listWidget_TaskList->clear();
  Filter->FilterList(ui->calendarWidget->selectedDate());
  for(int i=0;i<ListItems.length();i++){
      ui->listWidget_TaskList->addItem(ListItems[i]);
  }

}

void MainWindow::UpdateListView(QDate Parameter)
{
    ui->listWidget_TaskList->clear();
    Filter->FilterList(Parameter);
    for(int i=0;i<ListItems.length();i++){
        ui->listWidget_TaskList->addItem(ListItems[i]);
    }
    ui->calendarWidget->setSelectedDate(Parameter);
    ui->label_TaskList->setText("Your tasks for "+ Parameter.toString("ddd d MMMM yy"));
}

Entry MainWindow::CompileEntry()
{
    Entry newEntry;
    if (ui->lineEdit_Title->text()!=nullptr && checkB_DatePlausibility(ui->dateEdit_Start->date(),ui->dateEdit_End->date())!=0
            && checkB_TimePlausibility(ui->dateEdit_Start->date(), ui->timeEdit_From->time(), ui->dateEdit_End->date(), ui->timeEdit_Until->time())!=0)
    {
     ui->label_Error->setText("");
    newEntry.setD_Start(ui->dateEdit_Start->date());
    newEntry.setT_Start(ui->timeEdit_From->time());
    newEntry.setD_End(ui->dateEdit_End->date());
    newEntry.setT_End(ui->timeEdit_Until->time());
    newEntry.setS_Title(ui->lineEdit_Title->text());
    newEntry.setS_Description(ui->textEdit->toPlainText());
    newEntry.setI_Status(ui->comboBox_TaskStatus->currentIndex());
    newEntry.setI_Priority(ui->comboBox_Priority->currentIndex());
    qDebug()<<ui->checkBox_AllDay->isChecked();
    newEntry.setB_AllDay(ui->checkBox_AllDay->isChecked());
    newEntry.setS_ID();
    InputMode(false);
    return newEntry;
    }
    else {
        ui->label_Error->setText("Details incorrect! Please check!");
    }
    InputMode(true);
    return newEntry;

}

void MainWindow::ResetInputs()
{
    EditMode=false;
    InputMode(false);
    ui->lineEdit_Title->setText("");
    ui->label_Error->setText("");
    ui->dateEdit_Start->setDate(ui->calendarWidget->selectedDate());
    ui->dateEdit_End->setDate(ui->calendarWidget->selectedDate());
    ui->timeEdit_From->setTime(QTime::currentTime());
    ui->timeEdit_Until->setTime(QTime::currentTime());
    ui->checkBox_AllDay->setCheckState(Qt::Unchecked);
    ui->comboBox_Priority->setCurrentIndex(0);
    ui->comboBox_TaskStatus->setCurrentIndex(0);
    ui->textEdit->setText("");

    ui->lbl_ViewTiming->setText("");
    ui->lbl_View_Title->setText("");
    ui->lbl_View_Status->setText("");
    ui->lbl_View_Priority->setText("");
    ui->lbl_View_Description->setText("");


}

void MainWindow::InputMode(bool Input)
{

    ui->groupBox_View->setVisible(!Input);
    ui->groupBox_TaskDetails->setVisible(Input);
    ui->calendarWidget->setEnabled(!Input);
    ui->listWidget_TaskList->setEnabled(!Input);
    ui->pushButton_NewTask->setEnabled(!Input);
    ui->pushButton_Edit->setEnabled(!Input);
    ui->pushButton_DeleteTask->setEnabled(!Input);
    ui->groupBox_TaskDetails->setEnabled(Input);
    ui->textEdit->setReadOnly(!Input);
    ui->pushButton_Save->setVisible(Input);
    ui->pushButton_Cancel->setVisible(Input);
}

void MainWindow::on_pushButton_clicked()
{
    Help= !Help;
    qDebug()<<Help;
    ui->lbl_Help->setVisible(Help);
}
