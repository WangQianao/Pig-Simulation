#include "pig.h"
#include<QTime>
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
void Pig::pigPrint()
{
    /*
    cout<<"Æ·ÖÖ£º";
    switch(breed)
    {
        case 0:
            cout<<"ºÚÖí      ";
            break;
            case 1:
                cout<<"Ð¡»¨Öí      ";
                break;
            case 2:
                cout<<"´ó°×Öí       ";
                break;
    }
    cout<<"ÌåÖØ:"<<weight<<"kg         ";
    cout<<"ËÇÑøÊ±¼ä:"<<growDay<<"Ìì"<<endl;
    */
}
