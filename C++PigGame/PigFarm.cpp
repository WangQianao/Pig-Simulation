#include "pigfarm.h"
using namespace std;
PigFarm::PigFarm() 
{
    this->totalPigNums=0;
    this->totalBlackPigNums=0;
    this->totalSmallFlowerPigNums=0;
    this->totalBigWhitePigNums=0;
    this->flowerPigStyIndex=0;
}
void PigFarm::salePigs(int day)
{
    int blackPig=0,smallFlowerPig=0,bigWhitePig=0;
    double totalSalePrice=0;
    Pig*q;
    for(int i=0;i<PigFarm::totalPigStyNums;i++)
    {
        for(Pig*p=this->pigStys[i].first();p!=this->pigStys[i].last()->succ;p=p->succ)
        {
            if(p->getWeight()>Pig::weightMax||(p->getGrowDay()-360)>0)//体重超过150斤的和饲养超过1年的猪将进行出圈 
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
		cout<<"打开销售记录文件失败"<<endl;
		exit(0);
	}
    ofs<<'+'<<" "<<day<<" "<<blackPig<<" "<<smallFlowerPig<<" "<<bigWhitePig<<" "<<totalSalePrice<<endl;
    ofs.close();
    cout<<"这次共卖出"<<blackPig<<"头黑猪      "<<smallFlowerPig<<"头小花猪       "<<bigWhitePig<<"头大白猪"<<endl;
	cout<<"本次出圈的猪的总体售价为: "<<std::fixed<<totalSalePrice<<"元"<<endl;
}
void PigFarm::print()
{
    cout<<"猪圈共有"<<this->totalPigNums<<"头猪"<<"黑猪"<<this->totalBlackPigNums<<"头 小花猪"<<this->totalSmallFlowerPigNums<<"头   ′大白猪"<<this->totalBigWhitePigNums<<"头"<<endl;
}
void PigFarm::increasePigNums(int blackPig,int smallFlowerPig,int bigWhitePig)
{
    this->totalPigNums+=(blackPig+smallFlowerPig+bigWhitePig);
    this->totalBlackPigNums+=blackPig;
    this->totalSmallFlowerPigNums+=smallFlowerPig;
    this->totalBigWhitePigNums+=bigWhitePig;
}
void PigFarm::decreasePigNums(int blackPig,int smallFlowerPig,int bigWhitePig)
{
    this->totalPigNums-=(blackPig+smallFlowerPig+bigWhitePig);
    this->totalBlackPigNums-=blackPig;
    this->totalSmallFlowerPigNums-=smallFlowerPig;
    this->totalBigWhitePigNums-=bigWhitePig;
}
void PigFarm::addPigsMenu()
{
	cout<<endl<<"===================================购入猪崽======================================="<<endl;
	 cout<<"您可进行如下操作："<<endl;
		cout<<"\t\t----------------------------------------------------------\n";
		cout<<"\t\t|                                                         |\n";
		cout<<"\t\t|                  1.  随机生成                           |\n";
		cout<<"\t\t|                                                         |\n";
		cout<<"\t\t|                  2.  手动输入                           |\n";
		cout<<"\t\t|                                                         |\n";
		cout<<"\t\t----------------------------------------------------------\n";
		cout<<endl<<"请输入您的选择："<<endl;
}
void PigFarm::deteAddPigNums(int &blackPig,int &smallFlowerPig,int &bigWhitePig,int &singlePigNum)
{
    int select=0;
    while(true)
    {
    	system("cls");
        this->addPigsMenu();
        cin>>select;
        switch(select)
        {
        	case 1:
        	srand((unsigned)time(NULL));
        	blackPig=rand()%(this->getSurplus()+1);
            smallFlowerPig=rand()%(this->getSurplus()-blackPig+1);
            bigWhitePig=rand()%(this->getSurplus()-blackPig-smallFlowerPig+1);
            cout<<endl<<"此次随机生成"<<blackPig<<"头黑猪      "<<smallFlowerPig<<"头小花猪         "<<bigWhitePig<<"头大白猪"<<endl;
            break;
            case 2:
            	while(true)
	            {
	            	cout<<endl<<"请输入您要购入的黑猪的数量: ";
					 cin>>blackPig;
					 cout<<endl<<"请输入您要购入的小花猪的数量: ";
	                cin>>smallFlowerPig;
	                cout<<endl<<"请输入您要购入的大白猪的数量: ";
	                cin>>bigWhitePig;
	                if(blackPig+smallFlowerPig+bigWhitePig>this->getSurplus())
	                {
	                    cout<<endl<<"购入的数量太多，养猪场中无法装下这些猪，请重新输入";
	                }
	                else
	                {
	                    break;
	                }
	            }
            	break;
            	default:
            		cout<<"输入错误，请重新进行选择"<<endl;
            		system("pause");
            		break;
		}
        bool hasSpace=false;
        for(int i=1;i<=PigSty::pigNumMax;i++)
        {
            if((((this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)/i)+((this->totalBlackPigNums+blackPig)/i))>totalPigStyNums)
            {
                continue;
            }
            else
            {
                if((this->totalBlackPigNums+blackPig)%i!=0&&(this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)%i!=0)
                {
                    if((((this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)/i)+((this->totalBlackPigNums+blackPig)/i))+2>totalPigStyNums)
                    {
                        continue;
                    }
                }
                else if((this->totalBlackPigNums+blackPig)%i!=0||(this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)%i!=0)
                {
                    if((((this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)/i)+((this->totalBlackPigNums+blackPig)/i))+1>totalPigStyNums)
                    {
                        continue;
                    }
                }
                singlePigNum=i;
                hasSpace=true;
                break;
            }
        }
        if(hasSpace){
        	   cout<<"购入猪崽成功!"<<endl;
        	   system("pause");
                break;
            }
        else
        {
            cout<<endl<<"由于猪圈中无法装下这些猪崽，此次购入失败，请重新进行选择"<<endl;
            system("pause");
        }
    }
}
void PigFarm::putPigIntoSty(int c,int d,int singlePigNum,int oneLessNumPigStys,int PigStys,PigBreed::Type breed1,PigBreed::Type breed2)
{
    PigSty temporaryPigSty;
    int t=0,m=oneLessNumPigStys,n=PigStys-oneLessNumPigStys;
    while(m!=0||n!=0)
    {
        if(this->pigStys[t].getPigNum()==0||this->pigStys[t][0].getBreed()==breed1||this->pigStys[t][0].getBreed()==breed2)
        {

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
                            this->pigStys[t].insert(breed1);
                            c--;
                        }
                        else
                        {
                            this->pigStys[t].insert(breed2);
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
                                this->pigStys[t].insert(breed1);
                                c--;
                            }
                            else
                            {
                                this->pigStys[t].insert(breed2);
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
                                this->pigStys[t].insert(breed1);
                                c--;
                            }
                            else
                            {
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
void PigFarm::addPigs(int day)
{
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
		cout<<"打开销售记录文件失败"<<endl;
		exit(0);
	}
	ofs<<'-'<<" "<<day<<" "<<blackPig<<" "<<smallFlowerPig<<" "<<bigWhitePig<<endl;
	ofs.close();
    this->increasePigNums(blackPig,smallFlowerPig,bigWhitePig);
}
void PigFarm::pigFarmNextTime(int day)
{
	for(int i=0;i<PigFarm::totalPigStyNums;i++)
	{
		this->pigStys[i].pigStyNextTime(day);
	}
}
void PigFarm::printPigDistribution(PigBreed::Type breed,int lo,int hi)
{
	switch(breed)
	{
		case 0:
			cout<<"黑猪的数量："<<totalBlackPigNums;
			break;
			case 1:
				cout<<"小花猪的数量："<<totalSmallFlowerPigNums; 
				break;
				case 2:
					cout<<"大白猪的数量："<<totalBigWhitePigNums;
					break;
	}
	cout<<"头"<<endl;
		cout<<"其中："<<endl;
	
		int pigNum=0;
	cout<<"体重在[20-50)kg的有：";
	for(int i=lo;i<hi;i++)
	{
		pigNum+=this->pigStys[i].countPigNumOfWeight(breed,20,49);
	}
	cout<<pigNum<<"头"<<endl;
	pigNum=0;
	cout<<"体重在[50-75]kg的有：";
	for(int i=lo;i<hi;i++)
	{
		pigNum+=this->pigStys[i].countPigNumOfWeight(breed,50,75);
	}
	cout<<pigNum<<"头"<<endl;
	pigNum=0;
	cout<<"体重大于75kg的有：";
	for(int i=lo;i<hi;i++)
	{
		pigNum+=this->pigStys[i].countPigNumOfWeight(breed,75,1000);
	}
	cout<<pigNum<<"头"<<endl;
	pigNum=0;
	cout<<"饲养时间小于3个月的有：";
	for(int i=lo;i<hi;i++)
	{
		pigNum+=this->pigStys[i].countPigNumOfGrowTime(breed,0,3);
	}
	cout<<pigNum<<"头"<<endl;
	pigNum=0;
	cout<<"饲养时间大于等于3个月小于9个月的有：";
	for(int i=lo;i<hi;i++)
	{
		pigNum+=this->pigStys[i].countPigNumOfGrowTime(breed,3,9);
	}
	cout<<pigNum<<"头"<<endl;
	pigNum=0;
	cout<<"饲养时间大于等于9个月小于1年的有：";
	for(int i=lo;i<hi;i++)
	{
		pigNum+=this->pigStys[i].countPigNumOfGrowTime(breed,9,12);
	}
	cout<<pigNum<<"头"<<endl;
}

void PigFarm::printEachBreedDistribution()
{
	
	printPigDistribution(PigBreed::black,0,this->flowerPigStyIndex);
	printPigDistribution(PigBreed::smallFlower,this->flowerPigStyIndex,PigFarm::totalPigStyNums);
	printPigDistribution(PigBreed::bigWhite,this->flowerPigStyIndex,PigFarm::totalPigStyNums);
	
}
