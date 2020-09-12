#include "pigfarm.h"
using namespace std;
PigFarm::PigFarm() {
	this->totalPigNums=0;
	this->totalBlackPigNums=0;
	this->totalSmallFlowerPigNums=0;
	this->totalBigWhitePigNums=0;
	this->flowerPigStyIndex=0;
}
void PigFarm::salePigs(int day) {
	int blackPig=0,smallFlowerPig=0,bigWhitePig=0;
	double totalSalePrice=0;
	Pig*q;
	for(int i=0; i<PigFarm::totalPigStyNums; i++) {
		for(Pig*p=this->pigStys[i].first(); p!=this->pigStys[i].last()->succ; p=p->succ) {
			if(p->getWeight()>Pig::weightMax||(p->getGrowDay()-360)>0) { //���س���150��ĺ���������1��������г�Ȧ
				q=p;
				p=p->pred;
				switch(q->getBreed()) {
					case 0:
						blackPig++;
						totalSalePrice+=(q->getWeight()*Pig::salesPrice[0]);
						break;
					case 1:
						smallFlowerPig++;
						totalSalePrice+=(q->getWeight()*Pig::salesPrice[1]);
						break;
					case 2:
						bigWhitePig++;
						totalSalePrice+=(q->getWeight()*Pig::salesPrice[2]);
						break;
				}
				q=this->pigStys[i].removePig(q);
				delete q;
			}
		}
	}
	this->decreasePigNums(blackPig,smallFlowerPig,bigWhitePig);
	ofstream ofs;
	ofs.open("TemporaryPigSaleAndBuyInfo.txt",ios::out|ios::app);
	if(!ofs) {
		cout<<"�����ۼ�¼�ļ�ʧ��"<<endl;
		exit(0);
	}
	ofs<<'+'<<" "<<day<<" "<<blackPig<<" "<<smallFlowerPig<<" "<<bigWhitePig<<" "<<totalSalePrice<<endl;
	ofs.close();
	cout<<"��ι�����"<<blackPig<<"ͷ����      "<<smallFlowerPig<<"ͷС����       "<<bigWhitePig<<"ͷ�����"<<endl;
	cout<<"���γ�Ȧ����������ۼ�Ϊ: "<<std::fixed<<totalSalePrice<<"Ԫ"<<endl;
}
void PigFarm::print() {
	cout<<"��Ȧ����"<<this->totalPigNums<<"ͷ��"<<"����"<<this->totalBlackPigNums<<"ͷ С����"<<this->totalSmallFlowerPigNums<<"ͷ   ������"<<this->totalBigWhitePigNums<<"ͷ"<<endl;
}
void PigFarm::increasePigNums(int blackPig,int smallFlowerPig,int bigWhitePig) {
	this->totalPigNums+=(blackPig+smallFlowerPig+bigWhitePig);
	this->totalBlackPigNums+=blackPig;
	this->totalSmallFlowerPigNums+=smallFlowerPig;
	this->totalBigWhitePigNums+=bigWhitePig;
}
void PigFarm::decreasePigNums(int blackPig,int smallFlowerPig,int bigWhitePig) {
	this->totalPigNums-=(blackPig+smallFlowerPig+bigWhitePig);
	this->totalBlackPigNums-=blackPig;
	this->totalSmallFlowerPigNums-=smallFlowerPig;
	this->totalBigWhitePigNums-=bigWhitePig;
}
void PigFarm::addPigsMenu() {
	cout<<endl<<"===================================��������======================================="<<endl;
	cout<<"���ɽ������²�����"<<endl;
	cout<<"\t\t----------------------------------------------------------\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  1.  �������                           |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  2.  �ֶ�����                           |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t----------------------------------------------------------\n";
	cout<<endl<<"����������ѡ��"<<endl;
}
void PigFarm::deteAddPigNums(int &blackPig,int &smallFlowerPig,int &bigWhitePig,int &singlePigNum) {
	int select=0;
	while(true) {
		system("cls");
		this->addPigsMenu();
		cin>>select;
		switch(select) {
			case 1:
				srand((unsigned)time(NULL));
				blackPig=rand()%(this->getSurplus()+1);
				smallFlowerPig=rand()%(this->getSurplus()-blackPig+1);
				bigWhitePig=rand()%(this->getSurplus()-blackPig-smallFlowerPig+1);
				cout<<endl<<"�˴��������"<<blackPig<<"ͷ����      "<<smallFlowerPig<<"ͷС����         "<<bigWhitePig<<"ͷ�����"<<endl;
				break;
			case 2:
				while(true) {
					cout<<endl<<"��������Ҫ����ĺ��������: ";
					cin>>blackPig;
					cout<<endl<<"��������Ҫ�����С���������: ";
					cin>>smallFlowerPig;
					cout<<endl<<"��������Ҫ����Ĵ���������: ";
					cin>>bigWhitePig;
					if(blackPig+smallFlowerPig+bigWhitePig>this->getSurplus()) {
						cout<<endl<<"���������̫�࣬�������޷�װ����Щ������������";
					} else {
						break;
					}
				}
				break;
			default:
				cout<<"������������½���ѡ��"<<endl;
				system("pause");
				continue;
				break;
		}
		bool hasSpace=false;
		for(int i=1; i<=PigSty::pigNumMax; i++) {
			if((((this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)/i)+((this->totalBlackPigNums+blackPig)/i))>totalPigStyNums) {
				continue;
			} else {
				if((this->totalBlackPigNums+blackPig)%i!=0&&(this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)%i!=0) {
					if((((this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)/i)+((this->totalBlackPigNums+blackPig)/i))+2>totalPigStyNums) {
						continue;
					}
				} else if((this->totalBlackPigNums+blackPig)%i!=0||(this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)%i!=0) {
					if((((this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)/i)+((this->totalBlackPigNums+blackPig)/i))+1>totalPigStyNums) {
						continue;
					}
				}
				singlePigNum=i;
				hasSpace=true;
				break;
			}
		}
		if(hasSpace) {
			cout<<"�������̳ɹ�!"<<endl;
			system("pause");
			break;
		} else {
			cout<<endl<<"������Ȧ���޷�װ����Щ���̣��˴ι���ʧ�ܣ������½���ѡ��"<<endl;
			system("pause");
		}
	}
}
void PigFarm::putPigIntoSty(int c,int d,int singlePigNum,int oneLessNumPigStys,int PigStys,PigBreed::Type breed1,PigBreed::Type breed2) {
	PigSty temporaryPigSty;
	int t=0,m=oneLessNumPigStys,n=PigStys-oneLessNumPigStys;
	while(m!=0||n!=0) {
		if(this->pigStys[t].getPigNum()==0||this->pigStys[t][0].getBreed()==breed1||this->pigStys[t][0].getBreed()==breed2) {

			int p=singlePigNum,q=singlePigNum-1;
			if(this->pigStys[t].getPigNum()>p) {
				if(n>0) {
					int a=this->pigStys[t].getPigNum()-p;
					while(a--) {

						temporaryPigSty.insert(this->pigStys[t].removePig(this->pigStys[t].last()));
					}
					n--;
				} else {
					int a=this->pigStys[t].getPigNum()-q;
					while(a--) {
						temporaryPigSty.insert(this->pigStys[t].removePig(this->pigStys[t].last()));
					}
					m--;
				}
			} else if(this->pigStys[t].getPigNum()==p) {
				if(n>0)n--;
				else {
					temporaryPigSty.insert(this->pigStys[t].removePig(this->pigStys[t].last()));
					m--;
				}
			} else if(this->pigStys[t].getPigNum()==q) {
				if(m>0)m--;
				else {
					if(temporaryPigSty.getPigNum()>0) {
						this->pigStys[t].insert(temporaryPigSty.removePig(temporaryPigSty.last()));
					} else {
						if(c>0) {
							this->pigStys[t].insert(breed1);
							c--;
						} else {
							this->pigStys[t].insert(breed2);
							d--;
						}
					}

					n--;
				}
			} else {
			
				if(m>0) {
					int a=q-this->pigStys[t].getPigNum();
				
					while(a--) {
						if(temporaryPigSty.getPigNum()>0) {
							this->pigStys[t].insert(temporaryPigSty.removePig(temporaryPigSty.last()));
						} else {
							if(c>0) {
								
								this->pigStys[t].insert(breed1);
								c--;
							} else {
								this->pigStys[t].insert(breed2);
								d--;
							}
						}
						
					}
					m--;
				} else {
					int a=p-this->pigStys[t].getPigNum();
					while(a--) {
						if(temporaryPigSty.getPigNum()>0) {
							this->pigStys[t].insert(temporaryPigSty.removePig(temporaryPigSty.last()));
						} else {
							if(c>0) {
								this->pigStys[t].insert(breed1);
								c--;
							} else {
								this->pigStys[t].insert(breed2);
								d--;
							}
						}
					}
					n--;
				}
			}
		}
		t++;
	}
}
void PigFarm::changePigDistribution(int blackPigStys) {
	if(flowerPigStyIndex<blackPigStys) {
		for(int i=flowerPigStyIndex; i<blackPigStys; i++) {
			if(this->pigStys[i].getPigNum()==0)continue;
			else {
				while(this->pigStys[i].getPigNum()!=0) {
					this->pigStys[blackPigStys].insert(this->pigStys[i].removePig(this->pigStys[i].last()));
				}
			}
		}
	} else if(flowerPigStyIndex>blackPigStys) {
		for(int i=flowerPigStyIndex-1; i>=blackPigStys; i--) {
			if(this->pigStys[i].getPigNum()==0)continue;
			else {
				while(this->pigStys[i].getPigNum()!=0) {
					this->pigStys[0].insert(this->pigStys[i].removePig(this->pigStys[i].last()));
				}
			}
		}
	}
	this->flowerPigStyIndex=blackPigStys;
}
void PigFarm::addPigs(int day) {
	int blackPig=0,smallFlowerPig=0,bigWhitePig=0,singlePigNum=0;
	this->deteAddPigNums(blackPig,smallFlowerPig,bigWhitePig,singlePigNum);

	int extraBlackPigs=(this->totalBlackPigNums+blackPig)%singlePigNum;
	int oneLessNumBlackPigStys=(extraBlackPigs==0)?0:(singlePigNum-extraBlackPigs);
	int blackPigStys=(extraBlackPigs==0)?((this->totalBlackPigNums+blackPig)/singlePigNum):((this->totalBlackPigNums+blackPig)/singlePigNum+1);
	this->changePigDistribution(blackPigStys);
	
	this->putPigIntoSty(blackPig,0,singlePigNum,oneLessNumBlackPigStys,blackPigStys,PigBreed::black,PigBreed::black);
	int extraFlowerPigs=(this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)%singlePigNum;
	int oneLessNumFlowerPigStys=(extraFlowerPigs==0)?0:(singlePigNum-extraFlowerPigs);
	int FlowerPigStys=(extraFlowerPigs==0)?((this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)/singlePigNum):((this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)/singlePigNum+1);
	this->putPigIntoSty(smallFlowerPig,bigWhitePig,singlePigNum,oneLessNumFlowerPigStys,FlowerPigStys,PigBreed::smallFlower,PigBreed::bigWhite);
	ofstream ofs;

	ofs.open("TemporaryPigSaleAndBuyInfo.txt",ios::out|ios::app);
	if(!ofs) {
		cout<<"�����ۼ�¼�ļ�ʧ��"<<endl;
		exit(0);
	}
	ofs<<'-'<<" "<<day<<" "<<blackPig<<" "<<smallFlowerPig<<" "<<bigWhitePig<<endl;
	ofs.close();
	this->increasePigNums(blackPig,smallFlowerPig,bigWhitePig);
}
void PigFarm::pigFarmNextTime(int day) {
	for(int i=0; i<PigFarm::totalPigStyNums; i++) {
		this->pigStys[i].pigStyNextTime(day);
	}
}
void PigFarm::printPigDistribution(PigBreed::Type breed,int lo,int hi) {
	switch(breed) {
		case 0:
			cout<<"�����������"<<totalBlackPigNums;
			break;
		case 1:
			cout<<"С�����������"<<totalSmallFlowerPigNums;
			break;
		case 2:
			cout<<"������������"<<totalBigWhitePigNums;
			break;
	}
	cout<<"ͷ"<<endl;
	cout<<"���У�"<<endl;

	int pigNum=0;
	cout<<"������[20-50)kg���У�";
	for(int i=lo; i<hi; i++) {
		pigNum+=this->pigStys[i].countPigNumOfWeight(breed,20,49);
	}
	cout<<pigNum<<"ͷ"<<endl;
	pigNum=0;
	cout<<"������[50-75]kg���У�";
	for(int i=lo; i<hi; i++) {
		pigNum+=this->pigStys[i].countPigNumOfWeight(breed,50,75);
	}
	cout<<pigNum<<"ͷ"<<endl;
	pigNum=0;
	cout<<"���ش���75kg���У�";
	for(int i=lo; i<hi; i++) {
		pigNum+=this->pigStys[i].countPigNumOfWeight(breed,75,1000);
	}
	cout<<pigNum<<"ͷ"<<endl;
	pigNum=0;
	cout<<"����ʱ��С��3���µ��У�";
	for(int i=lo; i<hi; i++) {
		pigNum+=this->pigStys[i].countPigNumOfGrowTime(breed,0,3);
	}
	cout<<pigNum<<"ͷ"<<endl;
	pigNum=0;
	cout<<"����ʱ����ڵ���3����С��9���µ��У�";
	for(int i=lo; i<hi; i++) {
		pigNum+=this->pigStys[i].countPigNumOfGrowTime(breed,3,9);
	}
	cout<<pigNum<<"ͷ"<<endl;
	pigNum=0;
	cout<<"����ʱ����ڵ���9����С��1����У�";
	for(int i=lo; i<hi; i++) {
		pigNum+=this->pigStys[i].countPigNumOfGrowTime(breed,9,12);
	}
	cout<<pigNum<<"ͷ"<<endl;
}
int PigFarm::fever(int pigStyIndex,int pigIndex) {
	int day=1;
	this->pigStys[pigStyIndex][pigIndex].infected=true;
	this->pigStys[pigStyIndex][pigIndex].infectedDay++;
	while(this->totalPigNums!=0) {
		for(int i=0; i<PigFarm::totalPigStyNums; i++) {
			for(Pig*p=this->pigStys[i].first(); p!=this->pigStys[i].last()->succ; p=p->succ) {
				if(p->infected&&p->infectedDay>0) {
					for(Pig*q=this->pigStys[i].first(); q!=this->pigStys[i].last()->succ; q=q->succ) {
						if(q==p||q->infected)continue;
						else {
							if(rand()%2==1) {
								q->infected=true;
							}
						}
					}
					if(i-1>=0) {
						for(Pig*q=this->pigStys[i-1].first(); q!=this->pigStys[i-1].last()->succ; q=q->succ) {
							if(q->infected)continue;
							else {
								int t=rand()%20;
								if(t==1||t==2||t==3) { //%15����
									q->infected=true;
								}
							}
						}
					}
					if(i+1<PigFarm::totalPigStyNums) {
						for(Pig*q=this->pigStys[i+1].first(); q!=this->pigStys[i+1].last()->succ; q=q->succ) {
							if(q->infected)continue;
							else {
								if(rand()%20==1||rand()%20==2||rand()%20==2) { //%15����
									q->infected=true;
								}
							}
						}
					}
				}
			}
		}
		for(int i=0; i<PigFarm::totalPigStyNums; i++)
		{
			for(Pig*p=this->pigStys[i].first(); p!=this->pigStys[i].last()->succ; p=p->succ)
			{
				p->infectedDay++;
				if(p->infectedDay>=7)
				{
					p=this->pigStys[i].removePig(p);
					delete p;
				}
				
			}
		}
		day++;

	}
     this->renewPigFever();
	return day;
}
void PigFarm::renewPigFever()
{
	for(int i=0;i<PigFarm::totalPigStyNums;i++)
	{
		for(Pig*p=this->pigStys[i].first(); p!=this->pigStys[i].last()->succ; p=p->succ)
		{
			p->infected=false;
			p->infectedDay=0;
		}
	}
}
void PigFarm::printEachBreedDistribution() {

	printPigDistribution(PigBreed::black,0,this->flowerPigStyIndex);
	printPigDistribution(PigBreed::smallFlower,this->flowerPigStyIndex,PigFarm::totalPigStyNums);
	printPigDistribution(PigBreed::bigWhite,this->flowerPigStyIndex,PigFarm::totalPigStyNums);

}
