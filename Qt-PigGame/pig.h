#ifndef PIG_H
#define PIG_H
#include <QString>
#include <QObject>
#include "pigbreed.h"
class Pig : public QObject
{
    Q_OBJECT

    PigBreed::Type breed;  //猪的品种
    double weight;         //猪的体重
    int growDay;           //饲养时间
public:
    Pig* pred;      //双向链表
    Pig* succ;
    explicit Pig(QObject *parent = nullptr);
    Pig(PigBreed::Type breed);
    bool infected=false;   //是否被感染猪瘟，初始化为未被感染
    int infectedDay=0;     //已被感染天数，初始化为0
    static constexpr double weightMax=75;  //体重大于75Kg就可以出圈
    static constexpr int salesPrice[3]={30,14,12}; //黑猪30元一kg，小花猪14元一kg，大花白猪12元一kg
    static constexpr int buyPrice[3]={910,350,280};//买进猪崽黑猪一头910元，小花猪350元一头，大花白猪280元一头
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
    QString pigPrint();//打印猪相关信息

signals:

public slots:
};

#endif // PIG_H
