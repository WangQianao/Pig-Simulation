#ifndef PIGFARM_H
#define PIGFARM_H
#include "pigsty.h"
class PigFarm 
{
    int totalPigNums;
    static const int totalPigNumsMax=1000;
    int totalBlackPigNums;
    int totalSmallFlowerPigNums;
    int totalBigWhitePigNums;
    int flowerPigStyIndex;
public:
	int getTotalPigNums(){return totalPigNums;}
	int getTotalBlackPigNums(){return totalBlackPigNums;}
	int getTotalSmallFlowerPigNums(){return totalSmallFlowerPigNums;}
	int getTotalBigWhitePigNums(){return totalBigWhitePigNums;}
	int getFlowerPigStyIndex(){return flowerPigStyIndex;}
	void setTotalPigNums(int a){totalPigNums=a;}
	void setTotalBlackPigNums(int a){ totalBlackPigNums=a;}
	void setTotalSmallFlowerPigNums(int a){ totalSmallFlowerPigNums=a;}
	void setTotalBigWhitePigNums(int a){totalBigWhitePigNums=a;}
	void setFlowerPigStyIndex(int a){flowerPigStyIndex=a;}
    PigFarm();
    static const int totalPigStyNums=100;
    PigSty pigStys[totalPigStyNums];
    int getSurplus(){return totalPigNumsMax-totalPigNums;}
    void deteAddPigNums(int &blackPig,int &smallFlowerPig,int &bigWhitePig,int &singlePigNum);
    void addPigs(int day);
    void addPigsMenu();
    void putPigIntoSty(int c,int d,int singlePigNum,int oneLessNumPigStys,int PigStys,PigBreed::Type breed1,PigBreed::Type breed2);
    void increasePigNums(int blackPig,int smallFlowerPig,int bigWhitePig);
    void decreasePigNums(int blackPig,int smallFlowerPig,int bigWhitePig);
    void print();
    void salePigs(int day);
    void changePigDistribution(int blackPigStys);
	void pigFarmNextTime(int day);
	void printEachBreedDistribution();
	void printPigDistribution(PigBreed::Type breed,int lo,int hi);
	int fever(int pigStyIndex,int pigIndex);
	void renewPigFever();
};

#endif // PIGFARM_H

