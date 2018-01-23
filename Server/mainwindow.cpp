#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDBusConnection>
#include <QDBusError>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&m_company,SIGNAL(ageChangedSingal()),this,SLOT(ageChangedSlot()));
    connect(&m_company,SIGNAL(nameChangedSingal()),this,SLOT(nameChangedSlot()));
    connect(&m_company,SIGNAL(professionChangedSingal()),this,SLOT(professionChangedSlot()));
    connect(&m_company,SIGNAL(salaryChangedSingal()),this,SLOT(salaryChangeSlot()));


    //new connection
    QDBusConnection connection = QDBusConnection::sessionBus();
    //registe service
    if(!connection.registerService("company.recruitment")){
        qDebug()<<connection.lastError().message();
        exit(1);
    }

    //registe object
    connection.registerObject("/company/path",&m_company,
                                   QDBusConnection::ExportAllSlots);

    setWindowTitle("companyRecuitmentSystem");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::ageChangedSlot(){
    qDebug()<<"age changed slot";
    ui->ageLine->setText(QString::number(m_company.getUsrAge()));
}

void MainWindow::nameChangedSlot(){
    qDebug()<<"name changed slot";
    ui->nameLine->setText(m_company.getUsrName());
}
void MainWindow::salaryChangeSlot(){
    qDebug()<<"salary changed slot";
    ui->salaryline->setText(QString::number(m_company.getUsrSalary()));
}
void MainWindow::professionChangedSlot(){
    qDebug()<<"profession changed slot";
    ui->professionline->setText(m_company.gerUsrProfession());
}
