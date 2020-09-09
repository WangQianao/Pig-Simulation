#include <bits/stdc++.h>
using namespace std;
enum PigBreed{black,smallFlower,bigWhight};
class Pig
{
	private:
	PigBreed pigBreed;
	double weight;
	public:
	static constexpr double weightMax=40;
	static constexpr int salesPrice[3]={30,14,12};
	Pig* pred;
	Pig* succ;
	Pig(PigBreed pigBreed);
	Pig();
	PigBreed getBreed(){return pigBreed;}
	double getWeight(){return weight;}
	void insert(PigBreed pigBreed);
	void insert(Pig*p);
	
};
Pig::Pig()
{
	weight=(rand()%(50-20+1))+20;
	pred=NULL;
	succ=NULL;
}
Pig::Pig(PigBreed pigBreed)
{
	this->pigBreed=pigBreed;
	weight=(rand()%(50-20+1))+20;
	pred=NULL;
	succ=NULL;
}
void Pig::insert(Pig*p)
{
	p->pred=this;
	p->succ=this->succ;
	this->succ->pred=p;
	this->succ=p;
}
void Pig::insert(PigBreed pigBreed)
{
	Pig * p=new Pig(pigBreed);
	this->insert(p);
}
class PigSty{
	private:
	int pigNum;
	Pig* header;
	Pig* trailer;
	int blackPigNums;
	int smallFlowerPigNums;
	int bigWhightPigNums;
	void init();
	public:
	static const int pigNumMax=10;
	PigSty(){init();}
	~PigSty();
	int getPigNum(){return pigNum;}
	Pig* first(){return header->succ;}
	Pig* last(){return trailer->pred;}
	Pig& operator[](int index);
	void insert(PigBreed pigBreed);
	void insert(Pig*p);
	Pig* removePig(Pig *p);
	void clear();
	void increasePigNums(PigBreed pigBreed);
	void decreasePigNums(PigBreed pigBreed);
	void print(int t);
};
void PigSty::print(int t)
{
	cout<<"第"<<t<<"个猪圈现有"<<this->pigNum<<"头猪   黑猪"<<this->blackPigNums<<"头   小花猪"<<this->smallFlowerPigNums<<"头    大白猪"<<this->bigWhightPigNums<<"头"<<endl;
}
void PigSty::increasePigNums(PigBreed pigBreed)
{
	pigNum++;
	switch(pigBreed)
	{
		case 0: this->blackPigNums++;break;
		case 1: this->smallFlowerPigNums++;break;
		case 2: this->bigWhightPigNums++;break;
	}	
}
void PigSty::decreasePigNums(PigBreed pigBreed)
{
	pigNum--;
	switch(pigBreed)
	{
		case 0: this->blackPigNums--;break;
		case 1: this->smallFlowerPigNums--;break;
		case 2: this->bigWhightPigNums--;break;
	}	
}
void PigSty::insert(Pig*p)
{
	this->insert(p->getBreed());
}
void PigSty::insert(PigBreed pigBreed)
{
	this->last()->insert(pigBreed);
	this->increasePigNums(pigBreed);
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
Pig* PigSty::removePig(Pig*p)//将一头猪从这个猪圈中移走，但并不消除，应该能移走猪圈中任一头猪 
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


void PigSty::init()
{
	header=new Pig;
	trailer=new Pig;
	header->succ=trailer;
	header->pred=NULL;
	trailer->pred=header;
	trailer->succ=NULL;
	pigNum=0;
	this->bigWhightPigNums=0;
	this->blackPigNums=0;
	this->smallFlowerPigNums=0;
}
PigSty::~PigSty(){
	this->clear();
	delete header;
	delete trailer;
}
class PigFarm
{
	int totalPigNums;
	static const int totalPigNumsMax=1000;
	int totalBlackPigNums;
	int totalSmallFlowerPigNums;
	int totalBigWhightPigNums;
	int flowerPigStyIndex;
	public:
	static const int totalPigStyNums=100;
	PigSty pigStys[totalPigStyNums];
	PigFarm();
	int getSurplus(){return totalPigNumsMax-totalPigNums;}
	void deteAddPigNums(int &blackPig,int &smallFlowerPig,int &bigWhightPig,int &singlePigNum);
	void addPigs();
	void putPigIntoSty(int c,int d,int singlePigNum,int extraPigs,int oneLessNumPigStys,int PigStys,PigBreed pigBreed1,PigBreed pigBreed2);
	void increasePigNums(int blackPig,int smallFlowerPig,int bigWhightPig);
	void decreasePigNums(int blackPig,int smallFlowerPig,int bigWhightPig);
	void print();
	double salePigs();
	void changePigDistribution(int blackPigStys);
};
double PigFarm::salePigs()
{
	int blackPig=0,smallFlowerPig=0,bigWhightPig=0;
	double totalSalePrice=0;
	Pig*q;
	for(int i=0;i<PigFarm::totalPigStyNums;i++)
	{
		for(Pig*p=this->pigStys[i].first();p!=this->pigStys[i].last()->succ;p=p->succ)
		{
			if(p->getWeight()>Pig::weightMax)
			{
				q=p;
				p=p->pred;
				switch(q->getBreed())
				{
					case 0: 
					blackPig++;
					totalSalePrice+=(q->getWeight()*Pig::salesPrice[0]);
					break;
					case 1: 
					smallFlowerPig++;
					totalSalePrice+=(q->getWeight()*Pig::salesPrice[1]);
					break;
					case 2: 
					bigWhightPig++;
					totalSalePrice+=(q->getWeight()*Pig::salesPrice[2]);
					break;
				}
				q=this->pigStys[i].removePig(q);
				delete q;
			}
		}
	}
	this->decreasePigNums(blackPig,smallFlowerPig,bigWhightPig);
	cout<<"这次售卖卖出了"<<blackPig<<"头黑猪   "<<smallFlowerPig<<"头小花猪     "<<bigWhightPig<<"头大白猪"<<endl;
	cout<<"共卖出了"<<totalSalePrice<<"多钱"<<endl;
	return totalSalePrice;
}
void PigFarm::print()
{
	cout<<"整个养猪场现有"<<this->totalPigNums<<"头猪"<<"  黑猪"<<this->totalBlackPigNums<<"头   小花猪"<<this->totalSmallFlowerPigNums<<"头   大白猪"<<this->totalBigWhightPigNums<<"头"<<endl; 
}
PigFarm::PigFarm()
{
	this->totalPigNums=0;
	this->totalBlackPigNums=0;
    this->totalSmallFlowerPigNums=0;
    this->totalBigWhightPigNums=0;
    this->flowerPigStyIndex=0;
}
void PigFarm::increasePigNums(int blackPig,int smallFlowerPig,int bigWhightPig)
{
	this->totalPigNums+=(blackPig+smallFlowerPig+bigWhightPig);
	this->totalBlackPigNums+=blackPig;
	this->totalSmallFlowerPigNums+=smallFlowerPig;
	this->totalBigWhightPigNums+=bigWhightPig;
}
void PigFarm::decreasePigNums(int blackPig,int smallFlowerPig,int bigWhightPig)
{
	this->totalPigNums-=(blackPig+smallFlowerPig+bigWhightPig);
	this->totalBlackPigNums-=blackPig;
	this->totalSmallFlowerPigNums-=smallFlowerPig;
	this->totalBigWhightPigNums-=bigWhightPig;
}
void PigFarm::deteAddPigNums(int &blackPig,int &smallFlowerPig,int &bigWhightPig,int &singlePigNum)
{
	int isRandom;//确定是手动输入数量还是自动随机 
	while(1)//确定这批录入猪的数量 ,同时确定了每个猪圈多少猪 
	{
		cout<<"手动输入猪的数量请按0    自动随机请按1"<<endl; 
		cin>>isRandom;
		if(isRandom)//随机拟定要加入的猪的数量 
		{
			blackPig=rand()%(this->getSurplus()+1);
			smallFlowerPig=rand()%(this->getSurplus()-blackPig+1);
			bigWhightPig=rand()%(this->getSurplus()-blackPig-smallFlowerPig+1);
			cout<<"黑猪"<<blackPig<<"头"<<" "<<"小花猪"<<smallFlowerPig<<"头"<<" "<<"大花猪"<<bigWhightPig<<"头"<<endl; 
		}
		else
		{
			while(1)//手动输入要加入的猪的数量 
			{
				cin>>blackPig>>smallFlowerPig>>bigWhightPig;
				if(blackPig+smallFlowerPig+bigWhightPig>this->getSurplus())
				{
					cout<<"猪圈中不能容纳这么多猪了";
				}	
				else
				{
					break;
				}
			}
			
		}
	       /*  判断这些猪能否被成功放入猪圈中   */
		bool hasSpace=false;
		for(int i=1;i<=PigSty::pigNumMax;i++)
		{
			if((((this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)/i)+((this->totalBlackPigNums+blackPig)/i))>totalPigStyNums)
			{
				continue;
			}
			else
			{
				if((this->totalBlackPigNums+blackPig)%i!=0&&(this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)%i!=0)
				{
					if((((this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)/i)+((this->totalBlackPigNums+blackPig)/i))+2>totalPigStyNums)
					{
						continue;
					}
				}
				else if((this->totalBlackPigNums+blackPig)%i!=0||(this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)%i!=0)
				{
					if((((this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)/i)+((this->totalBlackPigNums+blackPig)/i))+1>totalPigStyNums)
					{
						continue;
					}
				}
				singlePigNum=i;
				hasSpace=true;
				cout<<"平均每个猪圈"<<i<<"头猪"<<endl;
				break;
			}
		}
		if(hasSpace){
				break;
			}
		else
		{
			cout<<"这些猪不能成功放进猪圈里，要重新输入了"<<endl;
		}
	}
}
void PigFarm::putPigIntoSty(int c,int d,int singlePigNum,int extraPigs,int oneLessNumPigStys,int PigStys,PigBreed pigBreed1,PigBreed pigBreed2)
{
	PigSty temporaryPigSty;
	int t=0,m=oneLessNumPigStys,n=PigStys-oneLessNumPigStys;
	cout<<"猪的数量为n-1的猪圈有："<<m<<"个      数量为n的猪圈有"<<n<<"个"<<endl; 
	while(m!=0||n!=0)
	{
		if(this->pigStys[t].getPigNum()==0||this->pigStys[t][0].getBreed()==pigBreed1||this->pigStys[t][0].getBreed()==pigBreed2)
		{
			
			cout<<"******************************"<<endl;
			this->pigStys[t].print(t);
			int p=singlePigNum,q=singlePigNum-1;
			if(this->pigStys[t].getPigNum()>p)
			{
				if(n>0)
				{
					int a=this->pigStys[t].getPigNum()-p;
					while(a--)
					{
					
						temporaryPigSty.insert(this->pigStys[t].removePig(this->pigStys[t].last()));
					}
					n--;
				}
				else
				{
					int a=this->pigStys[t].getPigNum()-q;
					while(a--)
					{
						temporaryPigSty.insert(this->pigStys[t].removePig(this->pigStys[t].last()));
					}
					m--;
				}
			}
			else if(this->pigStys[t].getPigNum()==p)
			{
				if(n>0)n--;
				else
				{
					temporaryPigSty.insert(this->pigStys[t].removePig(this->pigStys[t].last()));
					m--;
				}
			}
			else if(this->pigStys[t].getPigNum()==q)
			{
				if(m>0)m--;
				else
				{
					if(temporaryPigSty.getPigNum()>0)
					{
						this->pigStys[t].insert(temporaryPigSty.removePig(temporaryPigSty.last()));
					}
					else
					{
						if(c>0)
						{
							this->pigStys[t].insert(pigBreed1);
							c--;
						}
						else
						{
							this->pigStys[t].insert(pigBreed2);
							d--;
						}
					}
					
					n--;
				}
			}
			else
			{
				if(m>0)
				{
					int a=q-this->pigStys[t].getPigNum();
					while(a--)
					{
						if(temporaryPigSty.getPigNum()>0)
						{
							this->pigStys[t].insert(temporaryPigSty.removePig(temporaryPigSty.last()));
						}
						else
						{
							if(c>0)
							{
								this->pigStys[t].insert(pigBreed1);
								c--;
							}
							else
							{
								this->pigStys[t].insert(pigBreed2);
								d--;
							}
						}
						
					}
					m--;
				}
				else
				{
					int a=p-this->pigStys[t].getPigNum();
					while(a--)
					{
						if(temporaryPigSty.getPigNum()>0)
						{
							this->pigStys[t].insert(temporaryPigSty.removePig(temporaryPigSty.last()));
						}
						else
						{
							if(c>0)
							{
								this->pigStys[t].insert(pigBreed1);
								c--;
							}
							else
							{
								this->pigStys[t].insert(pigBreed2);
								d--;
							}
						}
					}
					n--;
				}
			}
			this->pigStys[t].print(t);
			cout<<"******************************"<<endl;
		}
		t++;
	}
}
void PigFarm::changePigDistribution(int blackPigStys)
{
	if(flowerPigStyIndex<blackPigStys)
	{
		for(int i=flowerPigStyIndex;i<blackPigStys;i++)
		{
			if(this->pigStys[i].getPigNum()==0)continue;
			else
			{
				while(this->pigStys[i].getPigNum()!=0)
				{
					 this->pigStys[blackPigStys].insert(this->pigStys[i].removePig(this->pigStys[i].last())); 
				}
			}
		}
	 }
	else if(flowerPigStyIndex>blackPigStys)
	{
		for(int i=flowerPigStyIndex-1;i>=blackPigStys;i--)
		{
			if(this->pigStys[i].getPigNum()==0)continue;
			else
			{
				while(this->pigStys[i].getPigNum()!=0)
				{
					 this->pigStys[0].insert(this->pigStys[i].removePig(this->pigStys[i].last())); 
				}
			}
		}
	}
	this->flowerPigStyIndex=blackPigStys;
}
void PigFarm::addPigs()
{
	int blackPig=0,smallFlowerPig=0,bigWhightPig=0,singlePigNum=0;
	this->deteAddPigNums(blackPig,smallFlowerPig,bigWhightPig,singlePigNum);
	
	/* 开始将黑猪放入猪圈中   */ 
	int extraBlackPigs=(this->totalBlackPigNums+blackPig)%singlePigNum;
	int oneLessNumBlackPigStys=(extraBlackPigs==0)?0:(singlePigNum-extraBlackPigs);
	int blackPigStys=(extraBlackPigs==0)?((this->totalBlackPigNums+blackPig)/singlePigNum):((this->totalBlackPigNums+blackPig)/singlePigNum+1);
	this->changePigDistribution(blackPigStys);
	cout<<"要插入黑猪了"<<endl;
	this->putPigIntoSty(blackPig,0,singlePigNum,extraBlackPigs,oneLessNumBlackPigStys,blackPigStys,black,black);
	/*    将小花猪和大花白猪放入到猪圈中    */
	
	int extraFlowerPigs=(this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)%singlePigNum;
	int oneLessNumFlowerPigStys=(extraFlowerPigs==0)?0:(singlePigNum-extraFlowerPigs);
	int FlowerPigStys=(extraFlowerPigs==0)?((this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)/singlePigNum):((this->totalSmallFlowerPigNums+this->totalBigWhightPigNums+smallFlowerPig+bigWhightPig)/singlePigNum+1);
	cout<<"要插入白猪了"<<endl; 
	this->putPigIntoSty(smallFlowerPig,bigWhightPig,singlePigNum,extraFlowerPigs,oneLessNumFlowerPigStys,FlowerPigStys,smallFlower,bigWhight);
	
	
	this->increasePigNums(blackPig,smallFlowerPig,bigWhightPig);
}
int main()
{
	PigFarm pigFarm;
	srand((unsigned int)(time(NULL)));

	pigFarm.addPigs();
	pigFarm.print();
	pigFarm.salePigs();
	pigFarm.print();
	
	
	return 0;
}
