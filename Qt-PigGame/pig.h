#ifndef PIG_H
#define PIG_H
#include <QString>
#include <QObject>
#include "pigbreed.h"
class Pig : public QObject
{
    Q_OBJECT

    PigBreed::Type breed;
     double weight;
     int growDay;

    public:
      explicit Pig(QObject *parent = nullptr);
        bool infected=false;
        int infectedDay=0;
        static constexpr double weightMax=75;
        static constexpr int salesPrice[3]={30,14,12};
        Pig* pred;
        Pig* succ;

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
        QString pigPrint();

signals:

public slots:
};

#endif // PIG_H
