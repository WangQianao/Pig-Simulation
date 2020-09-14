#include "addpigwidget.h"
#include "ui_addpigwidget.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>
AddPigWidget::AddPigWidget(PigFarm * pigFarm,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPigWidget)
{
    qsrand(time(NULL));
    ui->setupUi(this);
    this->setWindowTitle("购入猪崽界面");
    //点击确认按钮后，触发
    connect(ui->BuypushButton,&QPushButton::clicked,[=](){
        this->blackPig= ui->blackPigSpinBox->value();
        this->smallFlowerPig= ui->smallFlowerPigSpinBox->value();
         this->bigWhitePig= ui->bigWhiteSpinBox->value();
        QMessageBox msgBox;
        QString txt = QString("此次购买%1头黑猪,%2头小花猪,%3头大白猪").arg(this->blackPig).arg(this->smallFlowerPig).arg(this->bigWhitePig);
        msgBox.setText(txt);
        msgBox.exec();
        bool hasSpace=false;
        if(blackPig+smallFlowerPig+bigWhitePig<=pigFarm->getSurplus())
        {
            for(int i=1; i<=PigSty::pigNumMax; i++) {
                if((((pigFarm->totalSmallFlowerPigNums+pigFarm->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)/i)+((pigFarm->totalBlackPigNums+blackPig)/i))>pigFarm->totalPigStyNums) {
                    continue;
                } else {
                    if((pigFarm->totalBlackPigNums+blackPig)%i!=0&&(pigFarm->totalSmallFlowerPigNums+pigFarm->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)%i!=0) {
                        if((((pigFarm->totalSmallFlowerPigNums+pigFarm->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)/i)+((pigFarm->totalBlackPigNums+blackPig)/i))+2>pigFarm->totalPigStyNums) {
                            continue;
                        }
                    } else if((pigFarm->totalBlackPigNums+blackPig)%i!=0||(pigFarm->totalSmallFlowerPigNums+pigFarm->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)%i!=0) {
                        if((((pigFarm->totalSmallFlowerPigNums+pigFarm->totalBigWhitePigNums+smallFlowerPig+bigWhitePig)/i)+((pigFarm->totalBlackPigNums+blackPig)/i))+1>pigFarm->totalPigStyNums) {
                            continue;
                        }
                    }
                    single=i;
                    hasSpace=true;
                    break;
                }
            }
        }

        if(hasSpace) {

              msgBox.setText("此次购入猪崽成功");
              msgBox.exec();
              emit AddPigWidgetBack();
        } else {

              msgBox.setText("由于猪圈中无法装下这些猪，此次购入失败，请重新进行选择");
              msgBox.exec();

        }



    });
    //点击随机生成按钮后触发
    connect(ui->randomPushButton,&QPushButton::clicked,[=](){

        blackPig=qrand()%(pigFarm->getSurplus()+1);
        smallFlowerPig=qrand()%(pigFarm->getSurplus()-blackPig+1);
       bigWhitePig=qrand()%(pigFarm->getSurplus()-blackPig-smallFlowerPig+1);
        QMessageBox msgBox;
        QString txt = QString("此次随机生成%1头黑猪,%2头小花猪,%3头大白猪").arg(this->blackPig).arg(this->smallFlowerPig).arg(this->bigWhitePig);
        msgBox.setText(txt);
        msgBox.exec();
        ui->blackPigSpinBox->setValue(blackPig);
        ui->smallFlowerPigSpinBox->setValue(smallFlowerPig);
        ui->bigWhiteSpinBox->setValue(bigWhitePig);

    });
}

AddPigWidget::~AddPigWidget()
{
    delete ui;
}
