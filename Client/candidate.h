#ifndef CANDIDATE_H
#define CANDIDATE_H
#include <QString>
#include <QObject>
#include "companyInterface.h"
class candidate : public QObject
{
    Q_OBJECT
public:
    explicit candidate(QObject *parent = 0);
    ~candidate();
    void setCandidateName(QString name);
    void setCandidateAge(int age);
    void setCandidateExpectSalary(double salary);
    void setCandidateProfession(QString profession);
signals:

public slots:
};

#endif // CANDIDATE_H
