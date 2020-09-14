#include "pigfarm.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
PigFarm::PigFarm(QObject *parent) : QObject(parent)
{
    this->totalPigNums=0;
    this->totalBlackPigNums=0;
    this->totalSmallFlowerPigNums=0;
    this->totalBigWhitePigNums=0;
    this->flowerPigStyIndex=0;
}

void PigFarm::salePigs(int day) {
    int blackPig=0,smallFlowerPig=0,bigWhitePig=0;
    double totalSalePrice=0;
    Pig*q;
    for(int i=0; i<PigFarm::totalPigStyNums; i++) {
        for(Pig*p=this->pigStys[i].first(); p!=this->pigStys[i].last()->succ; p=p->succ) {
            if(p->getWeight()>Pig::weightMax||(p->getGrowDay()-360)>0) { //ÌåÖØ³¬¹ý150½ïµÄºÍËÇÑø³¬¹ý1ÄêµÄÖí½«½øÐÐ³öÈ¦
                q=p;
                p=p->pred;
                switch(q->getBreed()) {
                case 0:
                    blackPig++;
                    totalSalePrice+=(q->getWeight()*Pig::salesPrice[0]);
                    break;
                case 1:
                    smallFlowerPig++;
                    totalSalePrice+=(q->getWeight()*Pig::salesPrice[1]);
                    break;
                case 2:
                    bigWhitePig++;
                    totalSalePrice+=(q->getWeight()*Pig::salesPrice[2]);
                    break;
                }
                q=this->pigStys[i].removePig(q);
                delete q;
            }
        }
    }
    this->decreasePigNums(blackPig,smallFlowerPig,bigWhitePig);
    QMessageBox msgBox;
    QFile ofs("TemporaryPigSaleAndBuyInfo.txt");
    if(!ofs.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("打开文件失败");
        msgBox.exec();
        exit(0);
    }

    QTextStream out(&ofs);
    out<<'+'<<" "<<day<<" "<<blackPig<<" "<<smallFlowerPig<<" "<<bigWhitePig<<" "<<totalSalePrice<<"\n";
    ofs.close();


    msgBox.setIcon(QMessageBox::Information);
    QString str = QString("这次共卖出%1头黑猪,%2头小花猪,%3头大白猪,共%4元").arg(blackPig).arg(smallFlowerPig).arg(bigWhitePig).arg(QString::number(totalSalePrice,'f',1));
    msgBox.setText(str);
    msgBox.exec();
}
QString PigFarm::print() {

    QString s=QString("当前养猪场共有%1头猪,%2头黑猪,%3头小花猪,%4头大白猪").arg( this->totalPigNums).arg(this->totalBlackPigNums).arg(this->totalSmallFlowerPigNums).arg(this->totalBigWhitePigNums);
    return s;
}
void PigFarm::increasePigNums(int blackPig,int smallFlowerPig,int bigWhitePig) {
    this->totalPigNums+=(blackPig+smallFlowerPig+bigWhitePig);
    this->totalBlackPigNums+=blackPig;
    this->totalSmallFlowerPigNums+=smallFlowerPig;
    this->totalBigWhitePigNums+=bigWhitePig;
}
void PigFarm::decreasePigNums(int blackPig,int smallFlowerPig,int bigWhitePig) {
    this->totalPigNums-=(blackPig+smallFlowerPig+bigWhitePig);
    this->totalBlackPigNums-=blackPig;
    this->totalSmallFlowerPigNums-=smallFlowerPig;
    this->totalBigWhitePigNums-=bigWhitePig;
}
void PigFarm::putPigIntoSty(int c,int d,int singlePigNum,int oneLessNumPigStys,int PigStys,PigBreed::Type breed1,PigBreed::Type breed2) {
    PigSty temporaryPigSty;
    int t=0,m=oneLessNumPigStys,n=PigStys-oneLessNumPigStys;
    while(m!=0||n!=0) {
        if(this->pigStys[t].getPigNum()==0||this->pigStys[t][0].getBreed()==breed1||this->pigStys[t][0].getBreed()==breed2) {

            int p=singlePigNum,q=singlePigNum-1;
            if(this->pigStys[t].getPigNum()>p) {
                if(n>0) {
                    int a=this->pigStys[t].getPigNum()-p;
                    while(a--) {

                        temporaryPigSty.insert(this->pigStys[t].removePig(this->pigStys[t].last()));
                    }
                    n--;
                } else {
                    int a=this->pigStys[t].getPigNum()-q;
                    while(a--) {
                        temporaryPigSty.insert(this->pigStys[t].removePig(this->pigStys[t].last()));
                    }
                    m--;
                }
            } else if(this->pigStys[t].getPigNum()==p) {
                if(n>0)n--;
                else {
                    temporaryPigSty.insert(this->pigStys[t].removePig(this->pigStys[t].last()));
                    m--;
                }
            } else if(this->pigStys[t].getPigNum()==q) {
                if(m>0)m--;
                else {
                    if(temporaryPigSty.getPigNum()>0) {
                        this->pigStys[t].insert(temporaryPigSty.removePig(temporaryPigSty.last()));
                    } else {
                        if(c>0) {
                            this->pigStys[t].insert(breed1);
                            c--;
                        } else {
                            this->pigStys[t].insert(breed2);
                            d--;
                        }
                    }

                    n--;
                }
            } else {

                if(m>0) {
                    int a=q-this->pigStys[t].getPigNum();

                    while(a--) {
                        if(temporaryPigSty.getPigNum()>0) {
                            this->pigStys[t].insert(temporaryPigSty.removePig(temporaryPigSty.last()));
                        } else {
                            if(c>0) {

                                this->pigStys[t].insert(breed1);
                                c--;
                            } else {
                                this->pigStys[t].insert(breed2);
                                d--;
                            }
                        }

                    }
                    m--;
                } else {
                    int a=p-this->pigStys[t].getPigNum();
                    while(a--) {
                        if(temporaryPigSty.getPigNum()>0) {
                            this->pigStys[t].insert(temporaryPigSty.removePig(temporaryPigSty.last()));
                        } else {
                            if(c>0) {
                                this->pigStys[t].insert(breed1);
                                c--;
                            } else {
                                this->pigStys[t].insert(breed2);
                                d--;
                            }
                        }
                    }
                    n--;
                }
            }
        }
        t++;
    }
}
void PigFarm::changePigDistribution(int blackPigStys) {
    if(flowerPigStyIndex<blackPigStys) {
        for(int i=flowerPigStyIndex; i<blackPigStys; i++) {
            if(this->pigStys[i].getPigNum()==0)continue;
            else {
                while(this->pigStys[i].getPigNum()!=0) {
                    this->pigStys[blackPigStys].insert(this->pigStys[i].removePig(this->pigStys[i].last()));
                }
            }
        }
    } else if(flowerPigStyIndex>blackPigStys) {
        for(int i=flowerPigStyIndex-1; i>=blackPigStys; i--) {
            if(this->pigStys[i].getPigNum()==0)continue;
            else {
                while(this->pigStys[i].getPigNum()!=0) {
                    this->pigStys[0].insert(this->pigStys[i].removePig(this->pigStys[i].last()));
                }
            }
        }
    }
    this->flowerPigStyIndex=blackPigStys;
}
void PigFarm::addPigs(int day) {
    AddPigWidget *widget = new AddPigWidget(this);
    widget->show();
    connect(widget,&AddPigWidget::AddPigWidgetBack,[=](){

        widget->hide();//点击了确认按钮并且购买成功后，就会关闭购买界面
        int extraBlackPigs=(this->totalBlackPigNums+widget->blackPig)%widget->single;
        int oneLessNumBlackPigStys=(extraBlackPigs==0)?0:(widget->single-extraBlackPigs);
        int blackPigStys=(extraBlackPigs==0)?((this->totalBlackPigNums+widget->blackPig)/widget->single):((this->totalBlackPigNums+widget->blackPig)/widget->single+1);
        this->changePigDistribution(blackPigStys);
        this->putPigIntoSty(widget->blackPig,0,widget->single,oneLessNumBlackPigStys,blackPigStys,PigBreed::black,PigBreed::black);
        int extraFlowerPigs=(this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+widget->smallFlowerPig+widget->bigWhitePig)%widget->single;
        int oneLessNumFlowerPigStys=(extraFlowerPigs==0)?0:(widget->single-extraFlowerPigs);
        int FlowerPigStys=(extraFlowerPigs==0)?((this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+widget->smallFlowerPig+widget->bigWhitePig)/widget->single):((this->totalSmallFlowerPigNums+this->totalBigWhitePigNums+widget->smallFlowerPig+widget->bigWhitePig)/widget->single+1);
        this->putPigIntoSty(widget->smallFlowerPig,widget->bigWhitePig,widget->single,oneLessNumFlowerPigStys,FlowerPigStys,PigBreed::smallFlower,PigBreed::bigWhite);
        QFile ofs("TemporaryPigSaleAndBuyInfo.txt");
        if(!ofs.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("打开文件失败");
            msgBox.exec();
            exit(0);
        }

        QTextStream out(&ofs);
        out<<'-'<<" "<<day<<" "<<widget->blackPig<<" "<<widget->smallFlowerPig<<" "<<widget->bigWhitePig<<"\n";
        this->increasePigNums(widget->blackPig,widget->smallFlowerPig,widget->bigWhitePig);
        delete widget;
        emit  addSuccess();//购买成功后发送购买 成功信号


    });

}
void PigFarm::pigFarmNextTime(int day) {

    for(int i=0; i<PigFarm::totalPigStyNums; i++) {
        this->pigStys[i].pigStyNextTime(day);
    }
}

int PigFarm::fever(int pigStyIndex,int pigIndex) {
    int day=1,deadPigNum=0;
    this->pigStys[pigStyIndex][pigIndex].infected=true;
    this->pigStys[pigStyIndex][pigIndex].infectedDay++;
    while(this->totalPigNums!=deadPigNum) {
        for(int i=0; i<PigFarm::totalPigStyNums; i++) {
            for(Pig*p=this->pigStys[i].first(); p!=this->pigStys[i].last()->succ; p=p->succ) {
                if(p->infected&&p->infectedDay>0) {
                    for(Pig*q=this->pigStys[i].first(); q!=this->pigStys[i].last()->succ; q=q->succ) {
                        if(q==p||q->infected)continue;
                        else {
                            if(rand()%2==1) {
                                q->infected=true;
                            }
                        }
                    }
                    if(i-1>=0) {
                        for(Pig*q=this->pigStys[i-1].first(); q!=this->pigStys[i-1].last()->succ; q=q->succ) {
                            if(q->infected)continue;
                            else {
                                int t=rand()%20;
                                if(t==1||t==2||t==3) { //%15¸ÅÂÊ
                                    q->infected=true;
                                }
                            }
                        }
                    }
                    if(i+1<PigFarm::totalPigStyNums) {
                        for(Pig*q=this->pigStys[i+1].first(); q!=this->pigStys[i+1].last()->succ; q=q->succ) {
                            if(q->infected)continue;
                            else {
                                int t=rand()%20;
                                if(t==1||t==2||t==3) { //%15¸ÅÂÊ
                                    q->infected=true;
                                }
                            }
                        }
                    }
                }
            }
        }
        Pig*q;
        for(int i=0; i<PigFarm::totalPigStyNums; i++)
        {
            for(Pig*p=this->pigStys[i].first(); p!=this->pigStys[i].last()->succ; p=p->succ)
            {
                if(p->infected)
                {
                    p->infectedDay++;
                    if(p->infectedDay>=7)
                    {
                        q=p;
                        p=p->pred;
                        q=this->pigStys[i].removePig(q);
                        delete q;
                        deadPigNum++;

                    }
                }


            }
        }
        day++;

    }

    return day;
}
void PigFarm::eachBreedDis(PigBreed::Type breed,int lo,int hi)
{
    DrawGraph * draw = new DrawGraph;
    switch(breed) {
    case 0:
        draw->drawMap.insert("黑猪",this->totalBlackPigNums);
        break;
    case 1:
        draw->drawMap.insert("小花猪",this->totalSmallFlowerPigNums);

        break;
    case 2:
        draw->drawMap.insert("大白猪",this->totalBigWhitePigNums);
        break;
    }
    int pigNum=0;
    for(int i=lo; i<hi; i++) {
        pigNum+=this->pigStys[i].countPigNumOfWeight(breed,20,49);
    }
    draw->drawMap.insert("[20-50)kg", pigNum);
    pigNum=0;

    for(int i=lo; i<hi; i++) {
        pigNum+=this->pigStys[i].countPigNumOfWeight(breed,50,75);
    }
    draw->drawMap.insert("[50-75]kg", pigNum);

    pigNum=0;

    for(int i=lo; i<hi; i++) {
        pigNum+=this->pigStys[i].countPigNumOfWeight(breed,75,1000);
    }
    draw->drawMap.insert(">75kg", pigNum);

    pigNum=0;

    for(int i=lo; i<hi; i++) {
        pigNum+=this->pigStys[i].countPigNumOfGrowTime(breed,0,3);
    }
    draw->drawMap.insert("<3月", pigNum);

    pigNum=0;

    for(int i=lo; i<hi; i++) {
        pigNum+=this->pigStys[i].countPigNumOfGrowTime(breed,3,9);
    }
    draw->drawMap.insert("[3,9)月", pigNum);
    pigNum=0;

    for(int i=lo; i<hi; i++) {
        pigNum+=this->pigStys[i].countPigNumOfGrowTime(breed,9,12);
    }
    draw->drawMap.insert("[9,12)月", pigNum);

    draw->update();
    draw->show();



}
void PigFarm::clearPigFarm()
{
    for(int i=0;i<PigFarm::totalPigStyNums;i++)
    {
        this->pigStys[i].clear();
    }
    this->totalPigNums=0;
    this->totalBlackPigNums=0;
    this->totalSmallFlowerPigNums=0;
    this->totalBigWhitePigNums=0;
    this->flowerPigStyIndex=0;

}
