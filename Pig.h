#ifndef PIG_H
#define PIG_H
#include "pigbreed.h"
#include<iostream> 
#include<stdlib.h>
#include<time.h>
#include<fstream>
using namespace std;
class Pig
{
    PigBreed::Type breed;
    double weight;
    int growDay;
public:
    static constexpr double weightMax=75;
    static constexpr int salesPrice[3]={30,14,12};
    Pig* pred;
    Pig* succ;
    Pig(){}
    Pig(PigBreed::Type breed);
    PigBreed::Type getBreed(){return breed;}
    double getWeight(){return weight;}
    void insert(PigBreed::Type breed);
    void insert(Pig*p);
	void growWeight(int day); 
	void pigNextTime(int day);
	int getGrowDay(){return growDay;}
	void pigPrint();
};

#endif // PIG_H

