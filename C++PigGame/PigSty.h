#ifndef PIGSTY_H
#define PIGSTY_H

#include "pig.h"
class PigSty 
{
   
    int pigNum;
    Pig* header;
    Pig* trailer;
    int blackPigNums;
    int smallFlowerPigNums;
    int bigWhitePigNums;
    void init();
public:
   PigSty();
    static const int pigNumMax=10;
    ~PigSty();
    int getPigNum(){return pigNum;}
    int getBlackPigNum(){return blackPigNums;}
    int getSmallFlowerPigNum(){return smallFlowerPigNums;}
    int getBigWhitePigNum(){return bigWhitePigNums;}
    void setPigNum(int a){ pigNum=a;}
    void setBlackPigNum(int a){blackPigNums=a;}
    void setSmallFlowerPigNum(int a){ smallFlowerPigNums=a;}
    void setBigWhitePigNum(int a){bigWhitePigNums=a;}
    Pig* first(){return header->succ;}
    Pig* last(){return trailer->pred;}
    Pig& operator[](int index);
    void insert(PigBreed::Type breed);
    void insert(Pig*p);
    Pig* removePig(Pig *p);
    void clear();
    void increasePigNums(PigBreed::Type breed);
    void decreasePigNums(PigBreed::Type breed);
    void print(int t);
	void pigStyNextTime(int day);
	int countPigNumOfWeight(PigBreed::Type breed,double weight1,double weight2);
	int countPigNumOfGrowTime(PigBreed::Type breed,int month1,int month2);
};

#endif // PIGSTY_H

