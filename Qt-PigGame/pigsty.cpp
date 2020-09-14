#include "pigsty.h"
#include <QDebug>
PigSty::PigSty(QObject *parent) : QObject(parent)
{
    init();
}
void PigSty::init()
{
    header=new Pig;
    trailer=new Pig;
    header->succ=trailer;
    header->pred=NULL;
    trailer->pred=header;
    trailer->succ=NULL;
    pigNum=0;
    this->bigWhitePigNums=0;
    this->blackPigNums=0;
    this->smallFlowerPigNums=0;
}

QString PigSty::print(int t)
{
    QString info;
    info=QString("编号为 %1 的猪圈现在有 %2 头猪,其中黑猪 %3 头,小花猪 %4 头,大白猪 %5 头").arg(t).arg(this->pigNum).arg(this->blackPigNums).arg(this->smallFlowerPigNums).arg(this->bigWhitePigNums);
    return info;
}
void PigSty::increasePigNums(PigBreed::Type breed)
{
    pigNum++;
    switch(breed)
    {
        case 0: this->blackPigNums++;break;
        case 1: this->smallFlowerPigNums++;break;
        case 2: this->bigWhitePigNums++;break;
    }
}
void PigSty::decreasePigNums(PigBreed::Type breed)
{
    pigNum--;
    switch(breed)
    {
        case 0: this->blackPigNums--;break;
        case 1: this->smallFlowerPigNums--;break;
        case 2: this->bigWhitePigNums--;break;
    }
}
void PigSty::insert(Pig*p)
{
    this->insert(p->getBreed());
}
void PigSty::insert(PigBreed::Type breed)
{

    this->last()->insert(breed);
    this->increasePigNums(breed);
}
void PigSty::clear()
{
    int t=this->pigNum;
    while(t--)
    {
        Pig*p=this->removePig(this->last());
        delete p;
    }

}
Pig* PigSty::removePig(Pig*p)
{
        p->pred->succ=p->succ;
        p->succ->pred=p->pred;
        p->pred=NULL;
        p->succ=NULL;
        this->decreasePigNums(p->getBreed());
        return p;
}
Pig& PigSty::operator[](int index)
{
    Pig* p=first();
    while(index--)p=p->succ;
    return *p;
}


PigSty::~PigSty(){
    this->clear();
    delete header;
    delete trailer;
}
void PigSty::pigStyNextTime(int day)
{
    for(Pig*p=this->first();p!=this->trailer;p=p->succ)
    {

        p->pigNextTime(day);
    }
}
int PigSty::countPigNumOfWeight(PigBreed::Type breed,double weight1,double weight2)
{
    int count=0;
    for(Pig*p=this->first();p!=this->trailer;p=p->succ)
    {
        if(p->getBreed()==breed&&p->getWeight()>=weight1&&p->getWeight()<=weight2)
        {
            count++;
        }
    }
    return count;
}
int PigSty::countPigNumOfGrowTime(PigBreed::Type breed,int month1,int month2)
{
    int count=0;
    for(Pig*p=this->first();p!=this->trailer;p=p->succ)
    {
        if(p->getBreed()==breed&&p->getGrowDay()>=30*month1&&p->getGrowDay()<30*month2)
        {
            count++;
        }
    }
    return count;
}
