#include "company.h"
#include <QDebug>
company::company()
{

}

company::~company()
{

}

QString company::candidateName(QString name){
    qDebug()<<"name "<<name;
    usr_name = name;
    emit nameChangedSingal();
    return name;
}

int company::candidateAge(int age){
    qDebug()<<"age "<<age<<endl;
    usr_age = age;
    emit ageChangedSingal();
    return age;
}

QString company::candidateProfession(QString profession){
    qDebug()<<"profession "<<profession;
    usr_profession = profession;
    emit professionChangedSingal();
    return profession;
}

double company::candidateExpectSalary(double salary){
    qDebug()<<"ExpectSalary "<<salary;
    usr_salary = salary;
    emit salaryChangedSingal();
    return salary;
}
int company::getUsrAge(){
    return usr_age;
}
double company::getUsrSalary(){
    return usr_salary;
}

QString company::getUsrName(){
    return usr_name;
}

QString company::gerUsrProfession(){
    return usr_profession;
}
