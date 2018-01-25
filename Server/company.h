#ifndef COMPANY_H
#define COMPANY_H

#include <QObject>
#include <QString>

class company : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "company.interface")
public:
    explicit company();
    int getUsrAge();
    double getUsrSalary();
    QString getUsrName();
    QString gerUsrProfession();
    ~company();

signals:
    void nameChangedSingal();
    void ageChangedSingal();
    void professionChangedSingal();
    void salaryChangedSingal();
    void recruitInfo(const QString& name ,const QString& result);

public slots:
    QString candidateName(QString name);
    int candidateAge(int age);
    QString candidateProfession(QString profession);
    double candidateExpectSalary(double salary);

private:
    QString usr_name;
    int usr_age;
    QString usr_profession;
    double usr_salary;
};

#endif // COMPANY_H
