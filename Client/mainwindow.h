#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "candidate.h"
#include <QString>
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
    void NameEvent();
    void AgeEvent();
    void ProfessionEvent();
    void SalaryEvent();

private:
    Ui::MainWindow *ui;
    candidate m_candidate;
    QString nextText;
};

#endif // MAINWINDOW_H
