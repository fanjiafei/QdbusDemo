#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include "companyInterface.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->AgeLine,SIGNAL(editingFinished()),this,SLOT(AgeEvent()));
    connect(this->ui->NameLine,SIGNAL(editingFinished()),this,SLOT(NameEvent()));
    connect(this->ui->ProfessionLine,SIGNAL(editingFinished()),this,SLOT(ProfessionEvent()));
    connect(this->ui->SalaryLine,SIGNAL(editingFinished()),this,SLOT(SalaryEvent()));
    setWindowTitle("Candidate Info System");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::NameEvent(){
    qDebug()<<"Recv Name Change Event";
    m_candidate.setCandidateName(this->ui->NameLine->text());
}

void MainWindow::AgeEvent(){
    qDebug()<<"Recv Age Change Event";
    m_candidate.setCandidateAge(this->ui->AgeLine->text().toInt());
}

void MainWindow::ProfessionEvent(){
    qDebug()<<"Recv Profession Change Event";
    m_candidate.setCandidateProfession(this->ui->ProfessionLine->text());
}

void MainWindow::SalaryEvent(){
    qDebug()<<"Recv Salary Change Event";
    m_candidate.setCandidateExpectSalary(this->ui->SalaryLine->text().toDouble());
}
