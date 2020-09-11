
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include "Pig.h"
#include "PigSty.h"
#include "PigFarm.h"
void mainMenu();
void gameMenu();
void checkMenu();
void nextTime(int day,PigFarm*pigFarm); 
void InitializeGame(PigFarm*pigFarm);
int gameDay=0;//��Ϸ�������� 
int lastSalePigDay=0;//�ϴ����Ȧ������ 
int main(int argc, char** argv) {
	srand((unsigned)time(NULL));
	int select=0;
	PigFarm *pigFarm=new PigFarm; 
	while(true)
	{
		mainMenu();
		cin>>select;
		switch(select)
		{
			case 1://�µĿ�ʼ
				system("cls");
				InitializeGame(pigFarm);
				while(true)
				{
					bool exitFlag=false;
					int select=0;
					system("cls");
					gameMenu();
					if((gameDay-lastSalePigDay)/30>=3)//��Ȧһ��������һ������ 
					{
						cout<<"������Ҫ��Ȧһ�����ʱ����"<<endl;
						pigFarm->salePigs(); 
						system("pause");
						pigFarm->addPigs();  
						lastSalePigDay=gameDay;
					}
					else
					{
						cout<<"��������Ҫ���еĲ���(ѡ��ǰ�������): "<<endl;
						cin>>select;
						switch(select)
						{
							case 1://��ѯ�������Ϣ  
							
							while(true)
							{	
								bool exitFlag=false;
								int select=0,pigStyIndex;
								system("cls");
								checkMenu();
								cout<<"��������Ҫ���еĲ���(ѡ��ǰ�������): "<<endl;
								cin>>select;
							
								switch(select)
								{
									case 1://��ѯĳһ��Ȧ��������������� 
										
										while(true)
										{
											cout<<"��������Ҫ��ѯ����Ȧ���(0-99)��"<<endl;
											cin>>pigStyIndex;
											if(pigStyIndex>=0&&pigStyIndex<=99)
											{
												pigFarm->pigStys[pigStyIndex].print(pigStyIndex);
												system("pause");
												break;
											}else{
												cout<<"�������ı�ţ�����������"<<endl;
												system("pause");
											}
										}
											break;
										
										
										case 2:
											
											cout<<"��������Ҫ��ѯ����Ȧ���(0-99)��"<<endl;
											while(true)
											{
												cin>>pigStyIndex;
												if(pigStyIndex>=0&&pigStyIndex<=99)
												{
													if(pigFarm->pigStys[pigStyIndex].getPigNum()==0)
													{
														cout<<"����Ȧ����û�������޷���ѯĳͷ�����Ϣ"<<endl;
													}
													else
													{
														int pigIndex;
														cout<<"����Ȧ�ֹ���"<<pigFarm->pigStys[pigStyIndex].getPigNum()<<"ͷ��"<<endl;
														cout<<"�����Բ�ѯ���Ϊ0-"<<pigFarm->pigStys[pigStyIndex].getPigNum()-1<<"�������Ϣ"<<endl;
														cout<<"��������Ҫ��ѯ����ı��:  "<<endl;
														cin>>pigIndex;
														pigFarm->pigStys[pigStyIndex][pigIndex].pigPrint();
													}
													
													break;
													
												}else{
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
										case 4:
											
											
										break;
										case 5:
										break;
										case 6://������һ���� 
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
					
				break;
			case 2 :    //��ȡ�浵 
			
			
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
void checkMenu()
{
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
		cout<<"\t\t|                  5.  ��ӡ��ǰ��������Ϣ                              |\n";
		cout<<"\t\t|                                                                        |\n";
		cout<<"\t\t|                  6.  ������һ����                                      |\n";
		cout<<"\t\t|                                                                        |\n";
		cout<<"\t\t-------------------------------------------------------------------------\n";
}
void nextTime(int day,PigFarm*pigFarm)
{
	gameDay+=day;
	pigFarm->pigFarmNextTime(day);
}
void InitializeGame(PigFarm*pigFarm)
{
	gameDay=1;
	lastSalePigDay=1;
	cout<<"===================��ӭ��ʼ�µ���Ϸ=========================="<<endl;
	cout<<"������Ϊ������ӵ�һ������"<<endl;
	system("pause");
	pigFarm->addPigs();
	
}
void gameMenu()
{
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
void mainMenu()
{
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
