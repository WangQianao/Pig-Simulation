#include "pig.h"
#include<QTime>
#include <QDebug>
Pig::Pig(QObject *parent) : QObject(parent)
{
    pred=NULL;
    succ=NULL;
}
Pig::Pig(PigBreed::Type breed)
{
    this->breed=breed;
    weight=(rand()%(50-20+1))+20;
    pred=NULL;
    succ=NULL;
    this->growDay=0;
}
void Pig::insert(Pig*p)
{
    p->pred=this;
    p->succ=this->succ;
    this->succ->pred=p;
    this->succ=p;
}
void Pig::insert(PigBreed::Type breed)
{
    Pig * p=new Pig(breed);
    this->insert(p);
}
void Pig::growWeight(int day)
{
    this->weight+=(double)(rand()%13)/10.0*day;
}
void Pig::pigNextTime(int day)
{

    this->growWeight(day);
    this->growDay+=day;
}
QString Pig::pigPrint()
{
    QString info="品种:";

    switch(breed)
    {
        case 0:
           info.append("黑猪");
            break;
            case 1:
                 info.append("小花猪");
                break;
            case 2:
                info.append("大白猪");
                break;
    }
    QString info1=QString("  体重:%1 kg 饲养时间: %2 天").arg(weight).arg(growDay);
    info.append(info1);
    return info;

}
