
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include "Pig.h"
#include "PigSty.h"
#include "PigFarm.h"
void mainMenu();
void gameMenu();
void checkMenu();
void nextTime(int day,PigFarm*pigFarm);
void InitializeGame(PigFarm*pigFarm,int day);
void readSaleAndBuyInfo();
void clearFile(string filename);
void copySaleFile();
void saveGameInfo(PigFarm*pigFarm,int day);
int gameDay=0;//ÓÎÏ·½øÐÐÌìÊý
int lastSalePigDay=0;//ÉÏ´ÎÖí³öÈ¦µÄÈÕÆÚ
int main(int argc, char** argv) {
	srand((unsigned)time(NULL));
	int select=0;
	PigFarm *pigFarm=new PigFarm;
	while(true) {
		mainMenu();
		cin>>select;
		switch(select) {
			case 1://ÐÂµÄ¿ªÊ¼
			clearFile("TemporaryPigSaleAndBuyInfo.txt");
			clearFile("PigSaleAndBuyInfo.txt");
				system("cls");
				InitializeGame(pigFarm,gameDay);
				while(true) {
					bool exitFlag=false;
					int select=0;
					system("cls");
					gameMenu();
					if((gameDay-lastSalePigDay)/30>=3) { //³öÈ¦Ò»ÅúÖí²¢¹ºÈëÒ»ÅúÖíáÌ
						cout<<"µ½ÑøÖí³¡Òª³öÈ¦Ò»ÅúÖíµÄÊ±¼äÁË"<<endl;
						pigFarm->salePigs(gameDay);
						cout<<"Í¬Ê±£¬Ò²ÒªÎªÑøÖí³¡¹ºÈëÒ»ÅúÖíáÌ"<<endl;
						system("pause");
						pigFarm->addPigs(gameDay);
						lastSalePigDay=gameDay;
					} else {
						cout<<"ÇëÊäÈëÄúÒª½øÐÐµÄ²Ù×÷(Ñ¡ÏîÇ°ÃæµÄÊý×Ö): "<<endl;
						cin>>select;
						switch(select) {
							case 1://²éÑ¯Öí³¡Ïà¹ØÐÅÏ¢

								while(true) {
									bool exitFlag=false;
									int select=0,pigStyIndex;
									system("cls");
									checkMenu();
									cout<<"ÇëÊäÈëÄúÒª½øÐÐµÄ²Ù×÷(Ñ¡ÏîÇ°ÃæµÄÊý×Ö): "<<endl;
									cin>>select;

									switch(select) {
										case 1://²éÑ¯Ä³Ò»ÖíÈ¦µÄÖíµÄÊýÁ¿ºÍÖÖÀà

											while(true) {
												cout<<"ÇëÊäÈëÄãÒª²éÑ¯µÄÖíÈ¦±àºÅ(0-99)£º"<<endl;
												cin>>pigStyIndex;
												if(pigStyIndex>=0&&pigStyIndex<=99) {
													pigFarm->pigStys[pigStyIndex].print(pigStyIndex);
													system("pause");
													break;
												} else {
													cout<<"ÊäÈë´íÎóµÄ±àºÅ£¬ÇëÖØÐÂÊäÈë"<<endl;
													system("pause");
												}
											}
											break;


										case 2:

											cout<<"ÇëÊäÈëÄãÒª²éÑ¯µÄÖíÈ¦±àºÅ(0-99)£º"<<endl;
											while(true) {
												cin>>pigStyIndex;
												if(pigStyIndex>=0&&pigStyIndex<=99) {
													if(pigFarm->pigStys[pigStyIndex].getPigNum()==0) {
														cout<<"¸ÃÖíÈ¦ÏÖÔÚÃ»ÓÐÖí£¬¹ÊÎÞ·¨²éÑ¯Ä³Í·ÖíµÄÐÅÏ¢"<<endl;
													} else {
														int pigIndex;
														cout<<"¸ÃÖíÈ¦ÏÖ¹²ÓÐ"<<pigFarm->pigStys[pigStyIndex].getPigNum()<<"Í·Öí"<<endl;
														cout<<"Äú¿ÉÒÔ²éÑ¯±àºÅÎª0-"<<pigFarm->pigStys[pigStyIndex].getPigNum()-1<<"µÄÖíµÄÐÅÏ¢"<<endl;
														cout<<"ÇëÊäÈëÄúÒª²éÑ¯µÄÖíµÄ±àºÅ:  "<<endl;
														cin>>pigIndex;
														pigFarm->pigStys[pigStyIndex][pigIndex].pigPrint();
													}

													break;

												} else {
													cout<<"ÊäÈë´íÎóµÄ±àºÅ£¬ÇëÖØÐÂÊäÈë"<<endl;

												}
											}


											system("pause");



											break;
										case 3:
											system("cls");
											pigFarm->printEachBreedDistribution();
											system("pause");

											break;
										case 4://²éÑ¯ÏúÊÛºÍ¹ºÈë¼ÇÂ¼
											readSaleAndBuyInfo();
											system("pause");
											break;
										case 5:
											break;
										case 6://·µ»ØÉÏÒ»½çÃæ
											exitFlag=true;
											break;
										default:
											cout<<"ÊäÈë´íÎó£¬ÇëÖØÐÂÊäÈë!"<<endl;
											system("pause");
											system("cls");
											break;
									}
									if(exitFlag)break;
								}

								break;
							case 2://½øÈëÏÂÒ»Ìì
								nextTime(1,pigFarm);
								break;
							case 3://½øÈëÏÂÒ»¸öÔÂ
								nextTime(30,pigFarm);
								break;
							case 4://±£´æÓÎÏ·
							copySaleFile();
							saveGameInfo(pigFarm,gameDay);
							
								break;
							case 5://ÍË»ØÓÎÏ·Ö÷½çÃæ(²»»á×Ô¶¯±£´æ)
								exitFlag=true;
								break;
							default:
								cout<<"ÊäÈë´íÎó£¬ÇëÖØÐÂÊäÈë!"<<endl;
								system("pause");
								system("cls");
								break;
						}
					}
					if(exitFlag)break;

				}

				break;
			case 2 :    //¶ÁÈ¡´æµµ


				break;
			case 3 :    //ÍË³ö
				return 0;
				break;
			default:
				cout<<"ÊäÈë´íÎó£¬ÇëÖØÐÂÊäÈë!"<<endl;
				system("pause");
				break;
		}
		system("cls");
	}

	return 0;
}
void copySaleFile()
{
	ifstream ifs("TemporaryPigSaleAndBuyInfo.txt",ios::in);
	ofstream ofs("PigSaleAndBuyInfo.txt",ios::out|ios::app);
	if(!ifs||!ofs)
	{
		cout<<"´ò¿ªÎÄ¼þÊ§°Ü"<<endl;
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
		cout<<"´ò¿ªÏúÊÛ¼ÇÂ¼ÎÄ¼þÊ§°Ü"<<endl;
		exit(0);
	}
	while(ifs>>flag&&ifs>>day&&ifs>>blackPig&&ifs>>smallFlowerPig&&ifs>>bigWhitePig) {
		cout<<"ÔÚµÚ"<<day<<"Ìì";
		if(flag=='+') {
			ifs>>price;

			cout<<"Âô³ö"<<blackPig<<"Í·ºÚÖí      "<<smallFlowerPig<<"Í·Ð¡»¨Öí       "<<bigWhitePig<<"Í·´ó°×Öí"<<endl;
			cout<<"Õâ´ÎÂô³öµÄÖíµÄ×ÜÌåÊÛ¼ÛÎª: "<<std::fixed<<price<<"Ôª"<<endl;
		} else {

			cout<<"¹ºÈë"<<blackPig<<"Í·ºÚÖí      "<<smallFlowerPig<<"Í·Ð¡»¨Öí       "<<bigWhitePig<<"Í·´ó°×Öí"<<endl;

		}
	}
	ifs.close();
	ifs.open("TemporaryPigSaleAndBuyInfo.txt",ios::in);
	if(!ifs) {
		cout<<"´ò¿ªÏúÊÛ¼ÇÂ¼ÎÄ¼þÊ§°Ü"<<endl;
		exit(0);
	}
	while(ifs>>flag&&ifs>>day&&ifs>>blackPig&&ifs>>smallFlowerPig&&ifs>>bigWhitePig) {
		cout<<"ÔÚµÚ"<<day<<"Ìì";
		if(flag=='+') {
			ifs>>price;

			cout<<"Âô³ö"<<blackPig<<"Í·ºÚÖí      "<<smallFlowerPig<<"Í·Ð¡»¨Öí       "<<bigWhitePig<<"Í·´ó°×Öí"<<endl;
			cout<<"Õâ´ÎÂô³öµÄÖíµÄ×ÜÌåÊÛ¼ÛÎª: "<<std::fixed<<price<<"Ôª"<<endl;
		} else {

			cout<<"¹ºÈë"<<blackPig<<"Í·ºÚÖí      "<<smallFlowerPig<<"Í·Ð¡»¨Öí       "<<bigWhitePig<<"Í·´ó°×Öí"<<endl;

		}
	}
	ifs.close();
	
}
void saveGameInfo(PigFarm*pigFarm,int day)
{
	ofstream ofs;
	ofs.open("PigGameInfo.txt",ios::out);
	ofs<<day<<endl;
	ofs<<pigFarm->getTotalPigNums()<<" "<<pigFarm->getTotalBlackPigNums()<<" "<<pigFarm->getTotalSmallFlowerPigNums()<<" "<<pigFarm->getTotalBigWhitePigNums()<<" "<<pigFarm->getFlowerPigStyIndex()<<endl;
    for(int i=0;i<PigFarm::totalPigStyNums;i++)
    {
    	ofs<<pigFarm->pigStys[i].getPigNum()<<" "<<pigFarm->pigStys[i].getBlackPigNum()<<" "<<pigFarm->pigStys[i].getSmallFlowerPigNum()<<" "<<pigFarm->pigStys[i].getBigWhitePigNum()<<endl;
    	for(Pig*p=pigFarm->pigStys[i].first();p!=pigFarm->pigStys[i].last()->succ;p=p->succ)
    	{
    		ofs<<p->getWeight()<<" "<<p->getGrowDay()<<" "<<p->getBreed()<<endl;
		}
	}
	ofs.close();
}
void clearFile(string filename)
{
	ofstream ofs;
	ofs.open(filename,ios::out);
	ofs.close();
}
void checkMenu() {
	cout<<"========================²éÑ¯½çÃæ==================================";
	cout<<endl;
	cout<<endl<<"Äú¿É½øÐÐÈçÏÂ²Ù×÷£º"<<endl;
	cout<<"\t\t-------------------------------------------------------------------------\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  1.  ²éÑ¯Ä³Ò»ÖíÈ¦µÄÖíµÄÊýÁ¿ºÍÖÖÀà                      |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  2.  ²éÑ¯Ä³Ò»ÖíÈ¦Ä³Í·ÖíµÄ×´Ì¬ÐÅÏ¢                      |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  3.  Í³¼ÆÖí³¡Ã¿¸öÆ·ÖÖÖíµÄÊýÁ¿ºÍÌåÖØ¡¢ËÇÑøÊ±¼ä·Ö²¼Çé¿ö  |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  4.  ²éÑ¯½ü5ÄêÖíµÄÏúÊÛ¼ÇÂ¼ºÍÖíáÌ¶ùµÄ¹ºÈë¼ÇÂ¼           |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  5.  ´òÓ¡µ±Ç°Öí³¡ËùÓÐÐÅÏ¢                              |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t|                  6.  ·µ»ØÉÏÒ»½çÃæ                                      |\n";
	cout<<"\t\t|                                                                        |\n";
	cout<<"\t\t-------------------------------------------------------------------------\n";
}
void nextTime(int day,PigFarm*pigFarm) {
	gameDay+=day;
	pigFarm->pigFarmNextTime(day);
}
void InitializeGame(PigFarm*pigFarm,int day) {
	gameDay=1;
	lastSalePigDay=1;
	cout<<"===================»¶Ó­¿ªÊ¼ÐÂµÄÓÎÏ·=========================="<<endl;
	cout<<"ÏÖÔÚÇëÎªÑøÖí³¡Ìí¼ÓµÚÒ»ÅúÖíáÌ"<<endl;
	system("pause");
	pigFarm->addPigs(day);

}
void gameMenu() {
	cout<<"========================ÑøÖí³¡==================================";
	cout<<endl;
	cout<<endl<<"Äú¿É½øÐÐÈçÏÂ²Ù×÷£º"<<endl;
	cout<<"\t\t----------------------------------------------------------\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  1.  ²éÑ¯Öí³¡Ïà¹ØÐÅÏ¢                   |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  2.  ½øÈëÏÂÒ»Ìì                         |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  3.  ½øÈëÏÂÒ»¸öÔÂ                       |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  4.  ±£´æÓÎÏ·                           |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  5.  ÍË»ØÓÎÏ·Ö÷½çÃæ(²»»á×Ô¶¯±£´æ)       |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t----------------ÏÖÔÚÊÇµÚ"<<gameDay<<"Ìì------------------------------------------\n";

}
void mainMenu() {
	cout<<"========================»¶Ó­À´µ½ÑøÖíÓÎÏ·===================================";
	cout<<endl;
	cout<<endl<<"Äú¿É½øÐÐÈçÏÂ²Ù×÷£º"<<endl;
	cout<<"\t\t----------------------------------------------------------\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  1.  ÐÂµÄ¿ªÊ¼                           |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  2.  ¶ÁÈ¡´æµµ                           |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t|                  3.  ÍË³ö                               |\n";
	cout<<"\t\t|                                                         |\n";
	cout<<"\t\t----------------------------------------------------------\n";
	cout<<"ÇëÊäÈëÄúÒª½øÐÐµÄ²Ù×÷(Ñ¡ÏîÇ°ÃæµÄÊý×Ö): "<<endl;
}
