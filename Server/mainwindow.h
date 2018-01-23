#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDBusConnection>
#include "company.h"
#include <QDebug>
#include <QDBusError>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void ageChangedSlot();
    void nameChangedSlot();
    void professionChangedSlot();
    void salaryChangeSlot();
private:
    Ui::MainWindow *ui;
    company m_company;
};

#endif // MAINWINDOW_H
