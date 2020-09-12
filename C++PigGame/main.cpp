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
int gameDay=0;//��Ϸ��������
int lastSalePigDay=0;//�ϴ����Ȧ������
int main(int argc, char** argv) {
	srand((unsigned)time(NULL));
	int select=0;
    PigFarm *pigFarm;
	clearFile("TemporaryPigSaleAndBuyInfo.txt");
	while(true) {
		mainMenu();
		cin>>select;
		switch(select) {
			case 1://�µĿ�ʼ
				delete pigFarm;		//�Ӻ�һ�����淵�غ����¿�ʼ  
				pigFarm=new PigFarm;
				clearFile("PigSaleAndBuyInfo.txt");
				clearFile("PigGameInfo.txt");
				system("cls");
				initializeGame(pigFarm);
				playGame(pigFarm);
				break;
			case 2 :    //��ȡ�浵
				delete pigFarm;//�Ӻ�һ�����淵�غ�������� 
				pigFarm=new PigFarm;
				system("cls");
				cout<<"===================��ӭ�ص���Ϸ======================="<<endl;
				initializeGameByFile(pigFarm);
				system("pause");
				playGame(pigFarm);
				break;
			case 3 :    //�˳�
				return 0;
				break;
			default:
				cout<<"�����������������!"<<endl;
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
		if((gameDay-lastSalePigDay)/30>=3) { //��Ȧһ��������һ������
			cout<<"������Ҫ��Ȧһ�����ʱ����"<<endl;
			pigFarm->salePigs(gameDay);
			cout<<"ͬʱ��ҲҪΪ��������һ������"<<endl;
			system("pause");
			pigFarm->addPigs(gameDay);
			lastSalePigDay=gameDay;
		} else {
			cout<<"��������Ҫ���еĲ���(ѡ��ǰ�������): "<<endl;
			cin>>select;
			switch(select) {
				case 1://��ѯ�������Ϣ

					while(true) {
						bool exitFlag=false;
						int select=0,pigStyIndex;
						system("cls");
						checkMenu();
						cout<<"��������Ҫ���еĲ���(ѡ��ǰ�������): "<<endl;
						cin>>select;

						switch(select) {
							case 1://��ѯĳһ��Ȧ���������������

								while(true) {
									cout<<"��������Ҫ��ѯ����Ȧ���(0-99)��"<<endl;
									cin>>pigStyIndex;
									if(pigStyIndex>=0&&pigStyIndex<=99) {
										pigFarm->pigStys[pigStyIndex].print(pigStyIndex);
										system("pause");
										break;
									} else {
										cout<<"�������ı�ţ�����������"<<endl;
										system("pause");
									}
								}
								break;


							case 2:

								cout<<"��������Ҫ��ѯ����Ȧ���(0-99)��"<<endl;
								while(true) {
									cin>>pigStyIndex;
									if(pigStyIndex>=0&&pigStyIndex<=99) {
										if(pigFarm->pigStys[pigStyIndex].getPigNum()==0) {
											cout<<"����Ȧ����û�������޷���ѯĳͷ�����Ϣ"<<endl;
										} else {
											int pigIndex;
											cout<<"����Ȧ�ֹ���"<<pigFarm->pigStys[pigStyIndex].getPigNum()<<"ͷ��"<<endl;
											cout<<"�����Բ�ѯ���Ϊ0-"<<pigFarm->pigStys[pigStyIndex].getPigNum()-1<<"�������Ϣ"<<endl;
											cout<<"��������Ҫ��ѯ����ı��:  "<<endl;
											cin>>pigIndex;
											pigFarm->pigStys[pigStyIndex][pigIndex].pigPrint();
										}

										break;

									} else {
										cout<<"�������ı�ţ�����������"<<endl;

									}
								}


								system("pause");



								break;
							case 3:
								system("cls");
								pigFarm->printEachBreedDistribution();
								system("pause");

								break;
							case 4://��ѯ���ۺ͹����¼
								readSaleAndBuyInfo();
								system("pause");
								break;
							case 5://������һ����
								exitFlag=true;
								break;
							default:
								cout<<"�����������������!"<<endl;
								system("pause");
								system("cls");
								break;
						}
						if(exitFlag)break;
					}

					break;
				case 2://������һ��
					nextTime(1,pigFarm);
					break;
				case 3://������һ����
					nextTime(30,pigFarm);
					break;
				case 4://������Ϸ
					copySaleFile();
					saveGameInfo(pigFarm);

					break;
				case 5://�˻���Ϸ������(�����Զ�����)
					exitFlag=true;
					break;
				default:
					cout<<"�����������������!"<<endl;
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
		cout<<"���ļ�ʧ��"<<endl;
		exit(0);
	}
	int a,b,c,d,e;
	double weight;
	ifs>>a>>b;
	gameDay=a;
	lastSalePigDay=b;
	cout<<"��Ϸ���е���"<<gameDay<<"��"<<endl;
	ifs>>a>>b>>c>>d>>e;
	pigFarm->setTotalPigNums(a);
	pigFarm->setTotalBlackPigNums(b);
	pigFarm->setTotalSmallFlowerPigNums(c);
	pigFarm->setTotalBigWhitePigNums(d);
	pigFarm->setFlowerPigStyIndex(e);
	cout<<"��ǰ��������"<<a<<"ͷ��    "<<b<<"ͷ����     "<<c<<"ͷС����     "<<d<<"ͷ�����"<<endl;
	for(int i=0; i<PigFarm::totalPigStyNums; i++) {
		ifs>>a>>b>>c>>d;
		cout<<"************************���Ϊ"<<i<<"����Ȧ*************************************"<<endl;
		cout<<"��"<<b<<"ͷ����   "<<c<<"ͷС����    "<<d<<"ͷ�����"<<endl;
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
			cout<<"���:"<<index<<"  ";
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
		cout<<"���ļ�ʧ��"<<endl;
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
		cout<<"�����ۼ�¼�ļ�ʧ��"<<endl;
		exit(0);
	}
	while(ifs>>flag&&ifs>>day&&ifs>>blackPig&&ifs>>smallFlowerPig&&ifs>>bigWhitePig) {
		cout<<"�ڵ�"<<day<<"��";
		if(flag=='+') {
			ifs>>price;

			cout<<"����"<<blackPig<<"ͷ����      "<<smallFlowerPig<<"ͷС����       "<<bigWhitePig<<"ͷ�����"<<endl;
			cout<<"�����������������ۼ�Ϊ: "<<std::fixed<<price<<"Ԫ"<<endl;
		} else {

			cout<<"����"<<blackPig<<"ͷ����      "<<smallFlowerPig<<"ͷС����       "<<bigWhitePig<<"ͷ�����"<<endl;

		}
	}
	ifs.close();
	ifs.open("TemporaryPigSaleAndBuyInfo.txt",ios::in);
	if(!ifs) {
		cout<<"�����ۼ�¼�ļ�ʧ��"<<endl;
		exit(0);
	}
	while(ifs>>flag&&ifs>>day&&ifs>>blackPig&&ifs>>smallFlowerPig&&ifs>>bigWhitePig) {
		cout<<"�ڵ�"<<day<<"��";
		if(flag=='+') {
			ifs>>price;

			cout<<"����"<<blackPig<<"ͷ����      "<<smallFlowerPig<<"ͷС����       "<<bigWhitePig<<"ͷ�����"<<endl;
			cout<<"�����������������ۼ�Ϊ: "<<std::fixed<<price<<"Ԫ"<<endl;
		} else {

			cout<<"����"<<blackPig<<"ͷ����      "<<smallFlowerPig<<"ͷС����       "<<bigWhitePig<<"ͷ�����"<<endl;

		}
	}
	ifs.close();

}
void saveGameInfo(PigFarm*pigFarm) {
	ofstream ofs;
	ofs.open("PigGameInfo.txt",ios::out);
	if(!ofs) {
		cout<<"���ļ�ʧ��"<<endl;
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
	cout<<"========================��ѯ����==================================";
	cout<<endl;
	cout<<endl<<"���ɽ������²�����"<<endl;
	cout<<"\t\t-------------------------------------------------------------------------\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  1.  ��ѯĳһ��Ȧ���������������                      |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  2.  ��ѯĳһ��Ȧĳͷ���״̬��Ϣ                      |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  3.  ͳ����ÿ��Ʒ��������������ء�����ʱ��ֲ����  |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  4.  ��ѯ��5��������ۼ�¼�����̶��Ĺ����¼           |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  5.  ������һ����                                      |\n";
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
	cout<<"===================��ӭ��ʼ�µ���Ϸ=========================="<<endl;
	cout<<"������Ϊ������ӵ�һ������"<<endl;
	system("pause");
	pigFarm->addPigs(gameDay);

}
void gameMenu() {
	cout<<"========================����==================================";
	cout<<endl;
	cout<<endl<<"���ɽ������²�����"<<endl;
	cout<<"\t\t----------------------------------------------------------\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  1.  ��ѯ�������Ϣ                   |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  2.  ������һ��                         |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  3.  ������һ����                       |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  4.  ������Ϸ                           |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  5.  �˻���Ϸ������(�����Զ�����)       |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t----------------�����ǵ�"<<gameDay<<"��------------------------------------------\n";

}
void mainMenu() {
	cout<<"========================��ӭ����������Ϸ===================================";
	cout<<endl;
	cout<<endl<<"���ɽ������²�����"<<endl;
	cout<<"\t\t----------------------------------------------------------\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  1.  �µĿ�ʼ                           |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  2.  ��ȡ�浵                           |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  3.  �˳�                               |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t----------------------------------------------------------\n";
	cout<<"��������Ҫ���еĲ���(ѡ��ǰ�������): "<<endl;
}
