/*run this program using the console pauser or add your own getch, system("pause") or input loop */
#include "Pig.h"
#include "PigSty.h"
#include "PigFarm.h"
void mainMenu();
void gameMenu();
void checkMenu();
void nextTime(int day,PigFarm*pigFarm);
void initializeGame(PigFarm*pigFarm);
void readSaleAndBuyInfo();
void clearFile(string filename);
void copySaleFile();
void saveGameInfo(PigFarm*pigFarm);
void initializeGameByFile(PigFarm*pigFarm);
void playGame(PigFarm*pigFarm);
int gameDay=0;//游戏进行天数
int lastSalePigDay=0;//上次猪出圈的日期
int main(int argc, char** argv) {
	srand((unsigned)time(NULL));
	int select=0;
    PigFarm *pigFarm=NULL;
	clearFile("TemporaryPigSaleAndBuyInfo.txt");
	while(true) {
		mainMenu();
		cin>>select;
		switch(select) {
			case 1://新的开始
				delete pigFarm;		//从后一个界面返回后重新开始  
				pigFarm=new PigFarm;
				clearFile("PigSaleAndBuyInfo.txt");
				clearFile("PigGameInfo.txt");
				system("cls");
				initializeGame(pigFarm);
				playGame(pigFarm);
				break;
			case 2 :    //读取存档
				delete pigFarm;//从后一个界面返回后清空养猪场 
				pigFarm=new PigFarm;
				system("cls");
				cout<<"===================欢迎回到游戏======================="<<endl;
				initializeGameByFile(pigFarm);
				system("pause");
				playGame(pigFarm);
				break;
			case 3 :    //退出
				return 0;
				break;
			default:
				cout<<"输入错误，请重新输入!"<<endl;
				system("pause");
				break;
		}
		system("cls");
	}

	return 0;
}
void playGame(PigFarm*pigFarm) {
	while(true) {
		bool exitFlag=false;
		int select=0;
		system("cls");
		gameMenu();
		if((gameDay-lastSalePigDay)/30>=3) { //出圈一批猪并购入一批猪崽
			cout<<"到养猪场要出圈一批猪的时间了"<<endl;
			pigFarm->salePigs(gameDay);
			cout<<"同时，也要为养猪场购入一批猪崽"<<endl;
			system("pause");
			pigFarm->addPigs(gameDay);
			lastSalePigDay=gameDay;
		} else {
			cout<<"请输入您要进行的操作(选项前面的数字): "<<endl;
			cin>>select;
			switch(select) {
				case 1://查询猪场相关信息

					while(true) {
						bool exitFlag=false;
						int select=0,pigStyIndex;
						system("cls");
						checkMenu();
						cout<<"请输入您要进行的操作(选项前面的数字): "<<endl;
						cin>>select;

						switch(select) {
							case 1://查询某一猪圈的猪的数量和种类

								while(true) {
									cout<<"请输入你要查询的猪圈编号(0-99)："<<endl;
									cin>>pigStyIndex;
									if(pigStyIndex>=0&&pigStyIndex<=99) {
										pigFarm->pigStys[pigStyIndex].print(pigStyIndex);
										system("pause");
										break;
									} else {
										cout<<"输入错误的编号，请重新输入"<<endl;
										system("pause");
									}
								}
								break;


							case 2:

								cout<<"请输入你要查询的猪圈编号(0-99)："<<endl;
								while(true) {
									cin>>pigStyIndex;
									if(pigStyIndex>=0&&pigStyIndex<=99) {
										if(pigFarm->pigStys[pigStyIndex].getPigNum()==0) {
											cout<<"该猪圈现在没有猪，故无法查询某头猪的信息"<<endl;
										} else {
											int pigIndex;
											cout<<"该猪圈现共有"<<pigFarm->pigStys[pigStyIndex].getPigNum()<<"头猪"<<endl;
											cout<<"您可以查询编号为0-"<<pigFarm->pigStys[pigStyIndex].getPigNum()-1<<"的猪的信息"<<endl;
											cout<<"请输入您要查询的猪的编号:  "<<endl;
											cin>>pigIndex;
											pigFarm->pigStys[pigStyIndex][pigIndex].pigPrint();
										}

										break;

									} else {
										cout<<"输入错误的编号，请重新输入"<<endl;

									}
								}


								system("pause");



								break;
							case 3:
								system("cls");
								pigFarm->printEachBreedDistribution();
								system("pause");

								break;
							case 4://查询销售和购入记录
								readSaleAndBuyInfo();
								system("pause");
								break;
							case 5://返回上一界面
								exitFlag=true;
								break;
							default:
								cout<<"输入错误，请重新输入!"<<endl;
								system("pause");
								system("cls");
								break;
						}
						if(exitFlag)break;
					}

					break;
				case 2://进入下一天
					nextTime(1,pigFarm);
					break;
				case 3://进入下一个月
					nextTime(30,pigFarm);
					break;
					case 4://猪瘟模拟
					
					break; 
				case 5://保存游戏
					copySaleFile();
					saveGameInfo(pigFarm);

					break;
				case 6://退回游戏主界面(不会自动保存)
					exitFlag=true;
					break;
				default:
					cout<<"输入错误，请重新输入!"<<endl;
					system("pause");
					system("cls");
					break;
			}
		}
		if(exitFlag)break;
	}


}
void initializeGameByFile(PigFarm*pigFarm) {
	ifstream ifs;
	ifs.open("PigGameInfo.txt",ios::in);
	if(!ifs) {
		cout<<"打开文件失败"<<endl;
		exit(0);
	}
	int a,b,c,d,e;
	double weight;
	ifs>>a>>b;
	gameDay=a;
	lastSalePigDay=b;
	cout<<"游戏进行到第"<<gameDay<<"天"<<endl;
	ifs>>a>>b>>c>>d>>e;
	pigFarm->setTotalPigNums(a);
	pigFarm->setTotalBlackPigNums(b);
	pigFarm->setTotalSmallFlowerPigNums(c);
	pigFarm->setTotalBigWhitePigNums(d);
	pigFarm->setFlowerPigStyIndex(e);
	cout<<"当前养猪场共有"<<a<<"头猪    "<<b<<"头黑猪     "<<c<<"头小花猪     "<<d<<"头大白猪"<<endl;
	for(int i=0; i<PigFarm::totalPigStyNums; i++) {
		ifs>>a>>b>>c>>d;
		cout<<"************************编号为"<<i<<"的猪圈*************************************"<<endl;
		cout<<"共"<<b<<"头黑猪   "<<c<<"头小花猪    "<<d<<"头大白猪"<<endl;
		int index=0;
		while(a--) {
			Pig*p=new Pig;
			ifs>>weight>>b>>c;
			p->setWeight(weight);
			p->setGrowDay(b);
			switch(c) {
				case 0:
					p->setBreed(PigBreed::black);
					break;
				case 1:
					p->setBreed(PigBreed::smallFlower);
					break;
				case 2:
					p->setBreed(PigBreed::bigWhite);
					break;
			}
			cout<<"编号:"<<index<<"  ";
			p->pigPrint();
			pigFarm->pigStys[i].insert(p);
			index++;
		}

	}
	ifs.close();
}
void copySaleFile() {
	ifstream ifs("TemporaryPigSaleAndBuyInfo.txt",ios::in);
	ofstream ofs("PigSaleAndBuyInfo.txt",ios::out|ios::app);
	if(!ifs||!ofs) {
		cout<<"打开文件失败"<<endl;
		exit(0);
	}
	ifs.unsetf(ios::skipws);
	char ch;
	while(ifs>>ch)
		ofs<<ch;
	ifs.close();
	ofs.close();
	clearFile("TemporaryPigSaleAndBuyInfo.txt");
}
void readSaleAndBuyInfo() {
	ifstream ifs;
	char flag;
	int day,blackPig,smallFlowerPig,bigWhitePig;
	double price;
	ifs.open("PigSaleAndBuyInfo.txt",ios::in);
	if(!ifs) {
		cout<<"打开销售记录文件失败"<<endl;
		exit(0);
	}
	while(ifs>>flag&&ifs>>day&&ifs>>blackPig&&ifs>>smallFlowerPig&&ifs>>bigWhitePig) {
		cout<<"在第"<<day<<"天";
		if(flag=='+') {
			ifs>>price;

			cout<<"卖出"<<blackPig<<"头黑猪      "<<smallFlowerPig<<"头小花猪       "<<bigWhitePig<<"头大白猪"<<endl;
			cout<<"这次卖出的猪的总体售价为: "<<std::fixed<<price<<"元"<<endl;
		} else {

			cout<<"购入"<<blackPig<<"头黑猪      "<<smallFlowerPig<<"头小花猪       "<<bigWhitePig<<"头大白猪"<<endl;

		}
	}
	ifs.close();
	ifs.open("TemporaryPigSaleAndBuyInfo.txt",ios::in);
	if(!ifs) {
		cout<<"打开销售记录文件失败"<<endl;
		exit(0);
	}
	while(ifs>>flag&&ifs>>day&&ifs>>blackPig&&ifs>>smallFlowerPig&&ifs>>bigWhitePig) {
		cout<<"在第"<<day<<"天";
		if(flag=='+') {
			ifs>>price;

			cout<<"卖出"<<blackPig<<"头黑猪      "<<smallFlowerPig<<"头小花猪       "<<bigWhitePig<<"头大白猪"<<endl;
			cout<<"这次卖出的猪的总体售价为: "<<std::fixed<<price<<"元"<<endl;
		} else {

			cout<<"购入"<<blackPig<<"头黑猪      "<<smallFlowerPig<<"头小花猪       "<<bigWhitePig<<"头大白猪"<<endl;

		}
	}
	ifs.close();

}
void saveGameInfo(PigFarm*pigFarm) {
	ofstream ofs;
	ofs.open("PigGameInfo.txt",ios::out);
	if(!ofs) {
		cout<<"打开文件失败"<<endl;
		exit(0);
	}
	ofs<<gameDay<<" "<<lastSalePigDay<<endl;
	ofs<<pigFarm->getTotalPigNums()<<" "<<pigFarm->getTotalBlackPigNums()<<" "<<pigFarm->getTotalSmallFlowerPigNums()<<" "<<pigFarm->getTotalBigWhitePigNums()<<" "<<pigFarm->getFlowerPigStyIndex()<<endl;
	for(int i=0; i<PigFarm::totalPigStyNums; i++) {
		ofs<<pigFarm->pigStys[i].getPigNum()<<" "<<pigFarm->pigStys[i].getBlackPigNum()<<" "<<pigFarm->pigStys[i].getSmallFlowerPigNum()<<" "<<pigFarm->pigStys[i].getBigWhitePigNum()<<endl;
		for(Pig*p=pigFarm->pigStys[i].first(); p!=pigFarm->pigStys[i].last()->succ; p=p->succ) {
			ofs<<p->getWeight()<<" "<<p->getGrowDay()<<" "<<p->getBreed()<<endl;
		}
	}
	ofs.close();
}
void clearFile(string filename) {
	ofstream ofs;
	ofs.open(filename,ios::out);
	ofs.close();
}
void checkMenu() {
	cout<<"========================查询界面==================================";
	cout<<endl;
	cout<<endl<<"您可进行如下操作："<<endl;
	cout<<"\t\t-------------------------------------------------------------------------\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  1.  查询某一猪圈的猪的数量和种类                      |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  2.  查询某一猪圈某头猪的状态信息                      |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  3.  统计猪场每个品种猪的数量和体重、饲养时间分布情况  |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  4.  查询近5年猪的销售记录和猪崽儿的购入记录           |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  5.  返回上一界面                                      |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t-------------------------------------------------------------------------\n";
}
void nextTime(int day,PigFarm*pigFarm) {
	gameDay+=day;
	pigFarm->pigFarmNextTime(day);
}
void initializeGame(PigFarm*pigFarm) {
	gameDay=1;
	lastSalePigDay=1;
	cout<<"===================欢迎开始新的游戏=========================="<<endl;
	cout<<"现在请为养猪场添加第一批猪崽"<<endl;
	system("pause");
	pigFarm->addPigs(gameDay);

}
void gameMenu() {
	cout<<"========================养猪场==================================";
	cout<<endl;
	cout<<endl<<"您可进行如下操作："<<endl;
	cout<<"\t\t----------------------------------------------------------\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  1.  查询猪场相关信息                   |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  2.  进入下一天                         |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  3.  进入下一个月                       |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  4.  猪瘟模拟                           |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  5.  保存游戏                           |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  6.  退回游戏主界面(不会自动保存)       |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t----------------现在是第"<<gameDay<<"天------------------------------------------\n";

}
void mainMenu() {
	cout<<"========================欢迎来到养猪游戏===================================";
	cout<<endl;
	cout<<endl<<"您可进行如下操作："<<endl;
	cout<<"\t\t----------------------------------------------------------\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  1.  新的开始                           |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  2.  读取存档                           |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  3.  退出                               |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t----------------------------------------------------------\n";
	cout<<"请输入您要进行的操作(选项前面的数字): "<<endl;
}
