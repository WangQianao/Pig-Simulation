#ifndef PIGFARM_H
#define PIGFARM_H
#include "addpigwidget.h"
#include <QObject>
#include "pigsty.h"
#include "addpigwidget.h"
#include "drawgraph.h"
#include "gamemenu.h"
class GameMenu;
class PigFarm : public QObject
{
    Q_OBJECT

    int totalPigNums;
    int totalBlackPigNums;
    int totalSmallFlowerPigNums;
    int totalBigWhitePigNums;
    int flowerPigStyIndex;
public:
    explicit PigFarm(QObject *parent = nullptr);
    static const int totalPigStyNums=100;
     PigSty pigStys[totalPigStyNums];
    static const int totalPigNumsMax=1000; 
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
    int getSurplus(){return totalPigNumsMax-totalPigNums;}
    void addPigs(GameMenu* game,int day);
    void putPigIntoSty(int c,int d,int singlePigNum,int oneLessNumPigStys,int PigStys,PigBreed::Type breed1,PigBreed::Type breed2);
    void increasePigNums(int blackPig,int smallFlowerPig,int bigWhitePig);
    void decreasePigNums(int blackPig,int smallFlowerPig,int bigWhitePig);    
    void salePigs(GameMenu*game,int day);
    void changePigDistribution(int blackPigStys);
    void pigFarmNextTime(int day);
    void eachBreedDis(DrawGraph*draw, PigBreed::Type breed,int lo,int hi);
    int fever(int pigStyIndex,int pigIndex);
    void infecting();//进行猪瘟传染
    void clearPigFarm();
    QString print();
signals:
    void addSuccess();

public slots:
};

#endif // PIGFARM_H
