#include "candidate.h"

candidate::candidate(QObject *parent) : QObject(parent)
{
    company::interface *p_company;
    p_company = new company::interface("company.recruitment","/company/path",
                                 QDBusConnection::sessionBus());
    connect(p_company,SIGNAL(recruitInfo(QString, QString)),
            this,SLOT(recruitInfoSlot(QString ,QString)));
}

candidate::~candidate()
{

}
void candidate::recruitInfoSlot(const QString &usr_name,const QString& info){
    qDebug()<<"-------------";
    qDebug()<<"candidate's name is "<<usr_name<<" recruit result "<<info;
}

void candidate::setCandidateName(QString name){
    company::interface m_company("company.recruitment","/company/path",
                                 QDBusConnection::sessionBus());
    QDBusPendingReply<QString> reply = m_company.candidateName(name);
    reply.waitForFinished();
    if(reply.isValid()){
        qDebug()<<"candidate's name is "<<reply.value();
    }
}

void candidate::setCandidateAge(int age){
    company::interface m_company("company.recruitment","/company/path",
                                 QDBusConnection::sessionBus());
    QDBusPendingReply<int> reply = m_company.candidateAge(age);
    reply.waitForFinished();
    if(reply.isValid()){
        qDebug("candidate's age is %d",reply.value());
    }
}

void candidate::setCandidateExpectSalary(double salary){
    company::interface m_company("company.recruitment","/company/path",
                                 QDBusConnection::sessionBus());
    QDBusPendingReply<double> reply = m_company.candidateExpectSalary(salary);
    reply.waitForFinished();
    if(reply.isValid()){
        qDebug()<<"candidate's salary is "<<reply.value();
    }
}

void candidate::setCandidateProfession(QString profession){
    company::interface m_company("company.recruitment","/company/path",
                                 QDBusConnection::sessionBus());
    QDBusPendingReply<QString> reply = m_company.candidateProfession(profession);
    reply.waitForFinished();
    if(reply.isValid()){
        qDebug()<<"candidate's profession is" <<reply.value();
    }
}
