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
	int isRandom;//ȷ�����ֶ��������������Զ���� 
	while(1)//ȷ������¼��������� ,ͬʱȷ����ÿ����Ȧ������ 
	{
		cout<<"�ֶ�������������밴0    �Զ�����밴1"<<endl; 
		cin>>isRandom;
		if(isRandom)//����ⶨ������� 
		{
			blackPig=rand()%(this->getSurplus()+1);
			smallFlowerPig=rand()%(this->getSurplus()-blackPig+1);
			bigWhightPig=rand()%(this->getSurplus()-blackPig-smallFlowerPig+1);
			cout<<"����"<<blackPig<<"ͷ"<<" "<<"С����"<<smallFlowerPig<<"ͷ"<<" "<<"����"<<bigWhightPig<<"ͷ"<<endl; 
		}
		else
		{
			while(1)//�ֶ�����Ҫ������������ 
			{
				cin>>blackPig>>smallFlowerPig>>bigWhightPig;
				if(blackPig+smallFlowerPig+bigWhightPig>this->getSurplus())
				{
					cout<<"��Ȧ�в���������ô������";
				}	
				else
				{
					break;
				}
			}
			
		}
	       /*  �ж���Щ���ܷ񱻳ɹ�������Ȧ��   */
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
				cout<<"ƽ��ÿ����Ȧ"<<i<<"ͷ��"<<endl;
				break;
			}
		}
		if(hasSpace){
				break;
			}
		else
		{
			cout<<"��Щ���ܳɹ��Ž���Ȧ�Ҫ����������"<<endl;
		}
	}
}
void PigFarm::addPigs()
{
	int blackPig=0,smallFlowerPig=0,bigWhightPig=0,singlePigNum=0;
	this->deteAddPigNums(blackPig,smallFlowerPig,bigWhightPig,singlePigNum);
	this->totalPigNums+=(blackPig+smallFlowerPig+bigWhightPig);
	/* ��ʼ�����������Ȧ��   */ 
	int extraBlackPigs=blackPig%singlePigNum;
	int oneLessNumBlackPigStys=singlePigNum-extraBlackPigs;
	int blackPigStys=(extraBlackPigs==0)?(blackPig/singlePigNum):(blackPig/singlePigNum+1);
	cout<<"����ĺ����У�"<<extraBlackPigs<<" "<<"��һֻ�ĺ�����Ȧ�У�"<<oneLessNumBlackPigStys<<" "<<"������Ȧ�У�"<<blackPigStys<<endl;
	int t=0,m=oneLessNumBlackPigStys;
	while(m--)
	{
		int p=singlePigNum-1;
		while(p--)
		{
			cout<<"��"<<t<<"����Ȧ"<<" ";
			this->pigStys[t].insert(black);
			cout<<"�ɹ�����һͷ����"<<endl;
		}
		cout<<"��"<<t<<"����ȦĿǰ��"<<this->pigStys[t].getPigNum()<<"ͷ��"<<endl;
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
	/*    ��С����ʹ󻨰�����뵽��Ȧ��    */
	int extraFlowerPigs=(smallFlowerPig+bigWhightPig)%singlePigNum;
	int oneLessNumFlowerPigStys=singlePigNum-extraFlowerPigs;
	int FlowerPigStys=(extraFlowerPigs==0)?((smallFlowerPig+bigWhightPig)/singlePigNum):((smallFlowerPig+bigWhightPig)/singlePigNum+1);
	cout<<"����Ļ����У�"<<extraFlowerPigs<<" "<<"��һֻ�Ļ�����Ȧ�У�"<<oneLessNumFlowerPigStys<<" "<<"������Ȧ�У�"<<FlowerPigStys<<endl;
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
				cout<<"��"<<t<<"����Ȧ"<<" ";
				this->pigStys[t].insert(smallFlower);
				cout<<"����һͷС����"<<endl;
			}
			else
			{
				b--;
				cout<<"��"<<t<<"����Ȧ"<<" ";
				this->pigStys[t].insert(bigWhight);
				cout<<"����һͷ�󻨰���"<<endl;
			}	
		}
		cout<<"��"<<t<<"����ȦĿǰ��"<<this->pigStys[t].getPigNum()<<"ͷ��"<<endl;
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
