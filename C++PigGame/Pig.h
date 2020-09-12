#ifndef PIG_H
#define PIG_H
#include "pigbreed.h"
#include<iostream> 
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<iomanip>
using namespace std;
class Pig
{
    PigBreed::Type breed;
    double weight;
    int growDay;
    bool infected=false;
    int infectedDay=0;
public:
    static constexpr double weightMax=75;
    static constexpr int salesPrice[3]={30,14,12};
    Pig* pred;
    Pig* succ;
    Pig();
    Pig(PigBreed::Type breed);
    double getWeight(){return weight;}
    void setWeight(double a){ weight=a;}
    PigBreed::Type getBreed(){return breed;}
    void setBreed(PigBreed::Type a){ breed=a;}
    int getGrowDay(){return growDay;}
	void setGrowDay(int a){ growDay=a;}
    void insert(PigBreed::Type breed);
    void insert(Pig*p);
	void growWeight(int day); 
	void pigNextTime(int day);
	void pigPrint();
};

#endif // PIG_H
