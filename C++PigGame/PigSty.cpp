#include "pigsty.h"
using namespace std;
void PigSty::init()
{
    header=new Pig(PigBreed::black);
    trailer=new Pig(PigBreed::black);
    header->succ=trailer;
    header->pred=NULL;
    trailer->pred=header;
    trailer->succ=NULL;
    pigNum=0;
    this->bigWhitePigNums=0;
    this->blackPigNums=0;
    this->smallFlowerPigNums=0;
}
PigSty::PigSty() 
{
    init();
}
void PigSty::print(int t)
{
    cout<<"���Ϊ"<<t<<"����Ȧ����"<<this->pigNum<<"ͷ��"<<endl;
	cout<<"���к���"<<this->blackPigNums<<"ͷ    С����"<<this->smallFlowerPigNums<<"ͷ    �����"<<this->bigWhitePigNums<<"ͷ"<<endl;
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
