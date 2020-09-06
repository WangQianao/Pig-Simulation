#include <bits/stdc++.h>
using namespace std;
enum PigBreed{black,smallFlower,bigWhight};
class Pig
{
	private:
	PigBreed pigBreed;
	double weight;
	string breed;
	public:
	Pig* pred;
	Pig* succ;
	Pig(PigBreed pigBreed);
	Pig(){}
	double getWeight(){return weight;}
	void insert(PigBreed pigBreed);
	
};

Pig::Pig(PigBreed pigBreed)
{
	this->pigBreed=pigBreed;
	weight=(rand()%(50-20+1))+20;
	pred=NULL;
	succ=NULL;
}
void Pig::insert(PigBreed pigBreed)
{
	Pig * p=new Pig(pigBreed);
	p->pred=this;
	p->succ=this->succ;
	this->succ->pred=p;
	this->succ=p;
}
class PigSty{
	private:
	int index;
	int pigNumMax=10;
	int pigNum;
	Pig* header;
	Pig* trailer;

	void init();
	public:
	PigSty(){init();}
	~PigSty();
	void setIndex(int i){index=i;}
	int getIndex(){return index;}
	int getPigNum(){return pigNum;}
	Pig* first(){return header->succ;}
	Pig* last(){return trailer->pred;}
	Pig& operator[](int index);
	void insert(PigBreed pigBreed){this->last()->insert(pigBreed);pigNum++;}	
};

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
	
}
PigSty::~PigSty(){
	delete header;
	delete trailer;
}
class PigFarm
{
	int totalPigNums;
	int totalPigNumsMax=1000;
	public:
	PigSty pigStys[100];
	PigFarm();
	int getSurplus(){return totalPigNumsMax-totalPigNums;}
	void deteAddPigNums(int &blackPig,int &smallFlowerPig,int &bigWhightPig,int &singlePigNum);
	void addPigs();
	
};
PigFarm::PigFarm()
{
	for(int i=0;i<100;i++)
	{
		pigStys[i].setIndex(i);
	}
	this->totalPigNums=0;
}
void PigFarm::deteAddPigNums(int &blackPig,int &smallFlowerPig,int &bigWhightPig,int &singlePigNum)
{
	int isRandom;//确定是手动输入数量还是自动随机 
	while(1)//确定这批录入猪的数量 ,同时确定了每个猪圈多少猪 
	{
		cout<<"手动输入猪的数量请按0    自动随机请按1"<<endl; 
		cin>>isRandom;
		if(isRandom)//随机拟定猪的数量 
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
		for(int i=1;i<=10;i++)
		{
			if((((smallFlowerPig+bigWhightPig)/i)+(blackPig/i))>100)
			{
				continue;
			}
			else
			{
				if(blackPig%i!=0&&(smallFlowerPig+bigWhightPig)%i!=0)
				{
					if((((smallFlowerPig+bigWhightPig)/i)+(blackPig/i))+2>100)
					{
						continue;
					}
				}
				else if(blackPig%i!=0||(smallFlowerPig+bigWhightPig)%i!=0)
				{
					if((((smallFlowerPig+bigWhightPig)/i)+(blackPig/i))+1>100)
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
void PigFarm::addPigs()
{
	int blackPig=0,smallFlowerPig=0,bigWhightPig=0,singlePigNum=0;
	this->deteAddPigNums(blackPig,smallFlowerPig,bigWhightPig,singlePigNum);
	this->totalPigNums+=(blackPig+smallFlowerPig+bigWhightPig);
	/* 开始将黑猪放入猪圈中   */ 
	int extraBlackPigs=blackPig%singlePigNum;
	int oneLessNumBlackPigStys=singlePigNum-extraBlackPigs;
	int blackPigStys=(extraBlackPigs==0)?(blackPig/singlePigNum):(blackPig/singlePigNum+1);
	cout<<"多余的黑猪有："<<extraBlackPigs<<" "<<"少一只的黑猪猪圈有："<<oneLessNumBlackPigStys<<" "<<"黑猪猪圈有："<<blackPigStys<<endl;
	int t=0,m=oneLessNumBlackPigStys;
	while(m--)
	{
		int p=singlePigNum-1;
		while(p--)
		{
			cout<<"第"<<t<<"个猪圈"<<" ";
			this->pigStys[t].insert(black);
			cout<<"成功插入一头黑猪"<<endl;
		}
		cout<<"第"<<t<<"个猪圈目前有"<<this->pigStys[t].getPigNum()<<"头猪"<<endl;
		t++;
	}
	 m=blackPigStys-oneLessNumBlackPigStys;
	while(m--)
	{
		int p=singlePigNum;
		while(p--)
		{
			this->pigStys[t].insert(black);
		}
		t++;
	}
	/*    将小花猪和大花白猪放入到猪圈中    */
	int extraFlowerPigs=(smallFlowerPig+bigWhightPig)%singlePigNum;
	int oneLessNumFlowerPigStys=singlePigNum-extraFlowerPigs;
	int FlowerPigStys=(extraFlowerPigs==0)?((smallFlowerPig+bigWhightPig)/singlePigNum):((smallFlowerPig+bigWhightPig)/singlePigNum+1);
	cout<<"多余的花猪有："<<extraFlowerPigs<<" "<<"少一只的花猪猪圈有："<<oneLessNumFlowerPigStys<<" "<<"花猪猪圈有："<<FlowerPigStys<<endl;
	m=oneLessNumFlowerPigStys;
	int a=smallFlowerPig,b=bigWhightPig;
	while(m--)
	{
		int p=singlePigNum-1;
		while(p--)
		{
			if(a)
			{
				a--;
				cout<<"第"<<t<<"个猪圈"<<" ";
				this->pigStys[t].insert(smallFlower);
				cout<<"插入一头小花猪"<<endl;
			}
			else
			{
				b--;
				cout<<"第"<<t<<"个猪圈"<<" ";
				this->pigStys[t].insert(bigWhight);
				cout<<"插入一头大花白猪"<<endl;
			}	
		}
		cout<<"第"<<t<<"个猪圈目前有"<<this->pigStys[t].getPigNum()<<"头猪"<<endl;
		t++;
	}
	m=FlowerPigStys-oneLessNumFlowerPigStys;
	while(m--)
	{
		int p=singlePigNum;
		while(p--)
		{
			if(a)
			{
				a--;
				
				this->pigStys[t].insert(smallFlower);
			
			}
			else
			{
				b--;
				
				this->pigStys[t].insert(bigWhight);
			
			}	
		}
		t++;
	}
	
}
int main()
{
	
	PigFarm pigFarm;
	srand((unsigned int)(time(NULL)));
	pigFarm.addPigs();
	
	
	
	
	return 0;
}
