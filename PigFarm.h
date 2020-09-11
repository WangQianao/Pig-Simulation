#ifndef PIGFARM_H
#define PIGFARM_H
#include "pigsty.h"
class PigFarm 
{
    int totalPigNums;
    static const int totalPigNumsMax=1000;
    int totalBlackPigNums;
    int totalSmallFlowerPigNums;
    int totalBigWhightPigNums;
    int flowerPigStyIndex;
public:
    PigFarm();
    static const int totalPigStyNums=100;
    PigSty pigStys[totalPigStyNums];
    int getSurplus(){return totalPigNumsMax-totalPigNums;}
    void deteAddPigNums(int &blackPig,int &smallFlowerPig,int &bigWhightPig,int &singlePigNum);
    void addPigs();
    void addPigsMenu();
    void putPigIntoSty(int c,int d,int singlePigNum,int oneLessNumPigStys,int PigStys,PigBreed::Type breed1,PigBreed::Type breed2);
    void increasePigNums(int blackPig,int smallFlowerPig,int bigWhightPig);
    void decreasePigNums(int blackPig,int smallFlowerPig,int bigWhightPig);
    void print();
    void salePigs();
    void changePigDistribution(int blackPigStys);
	void pigFarmNextTime(int day);
	void printEachBreedDistribution();
	void printPigDistribution(PigBreed::Type breed,int lo,int hi);
};

#endif // PIGFARM_H

