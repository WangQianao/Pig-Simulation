#include "pig.h"
Pig::Pig()
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
	cout<<"Ʒ�֣�";
	switch(breed)
	{
		case 0:
			cout<<"����      ";
			break;
			case 1:
				cout<<"С����      ";
				break;
			case 2:
				cout<<"�����       ";
				break;
	}
	cout<<"����:"<<weight<<"kg         ";
	cout<<"����ʱ��:"<<growDay<<"��"<<endl;
	
}
