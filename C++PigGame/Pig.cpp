#include "pig.h"
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
	cout<<"品种：";
	switch(breed)
	{
		case 0:
			cout<<"黑猪"<<endl;
			break;
			case 1:
				cout<<"小花猪"<<endl;
				break;
			case 2:
				cout<<"大白猪"<<endl;
				break;
	}
	cout<<"体重：  "<<weight<<"kg"<<endl;
	cout<<"饲养时间："<<growDay<<"天"<<endl;
	
}
