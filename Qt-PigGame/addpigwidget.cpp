#include "addpigwidget.h"
#include "ui_addpigwidget.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QSound>
AddPigWidget::AddPigWidget(PigFarm * pigFarm,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPigWidget)
{

    qsrand(time(NULL));
    ui->setupUi(this);
    this->setWindowTitle("购入猪崽界面");
    this->setFixedSize(600,600);
    this->setWindowIcon(QPixmap(":/new/prefix1/pigIcon1.png"));
    //为按钮设置音效
    QSound *buttonSound = new QSound(":/new/prefix1/music/TapButtonSound.wav",this);
    //配置随机选择按钮
    QPushButton * randomPushButton = new QPushButton(this);
    QPixmap pix;
    pix.load(":/new/prefix1/piggame4.png");
    randomPushButton->setFixedSize( pix.width(), pix.height() );
    //设置不规则图片的样式表
    randomPushButton->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    randomPushButton->setIcon(pix);
    //设置图标大小
    randomPushButton->setIconSize(QSize(pix.width(),pix.height()));
    randomPushButton->move(this->width()*0.5-randomPushButton->width()*0.5,this->height()*0.6);

    //配置确认按钮
    QPixmap pix1;
    QPushButton * BuypushButton = new QPushButton(this);

    pix1.load(":/new/prefix1/piggame3.png");
    pix1 = pix1.scaled(pix.width(),pix.height());
    BuypushButton->setFixedSize( pix.width(), pix.height() );
    //设置不规则图片的样式表
    BuypushButton->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    BuypushButton->setIcon(pix1);
    //设置图标大小
    BuypushButton->setIconSize(QSize(pix.width(),pix.height()));
    BuypushButton->move(this->width()*0.5-BuypushButton->width()*0.5,this->height()*0.8);

    //点击确认按钮后，触发
    connect(BuypushButton,&QPushButton::clicked,[=](){
        buttonSound->play();

        this->blackPig= ui->blackPigSpinBox->value();
        this->smallFlowerPig= ui->smallFlowerPigSpinBox->value();
        this->bigWhitePig= ui->bigWhiteSpinBox->value();
        price=Pig::buyPrice[0]*this->blackPig+Pig::buyPrice[1]*this->smallFlowerPig+Pig::buyPrice[2]*this->bigWhitePig;
        QMessageBox msgBox;
        QString txt = QString("此次购买%1头黑猪,%2头小花猪,%3头大白猪").arg(this->blackPig).arg(this->smallFlowerPig).arg(this->bigWhitePig);
        msgBox.setText(txt);
        msgBox.exec();
        bool hasSpace=false;
        if(money<price)
        {
            msgBox.setText("你的钱不够,无法购买这么多猪崽");
            msgBox.exec();
        }
        else if(blackPig+smallFlowerPig+bigWhitePig<=pigFarm->getSurplus())
        {
            for(int i=1; i<=PigSty::pigNumMax; i++) {
                if((((pigFarm->getTotalSmallFlowerPigNums()+pigFarm->getTotalBigWhitePigNums()+smallFlowerPig+bigWhitePig)/i)+((pigFarm->getTotalBlackPigNums()+blackPig)/i))>PigFarm::totalPigStyNums) {
                    continue;
                } else {
                    if((pigFarm->getTotalBlackPigNums()+blackPig)%i!=0&&(pigFarm->getTotalSmallFlowerPigNums()+pigFarm->getTotalBigWhitePigNums()+smallFlowerPig+bigWhitePig)%i!=0) {
                        if((((pigFarm->getTotalSmallFlowerPigNums()+pigFarm->getTotalBigWhitePigNums()+smallFlowerPig+bigWhitePig)/i)+((pigFarm->getTotalBlackPigNums()+blackPig)/i))+2>PigFarm::totalPigStyNums) {
                            continue;
                        }
                    } else if((pigFarm->getTotalBlackPigNums()+blackPig)%i!=0||(pigFarm->getTotalSmallFlowerPigNums()+pigFarm->getTotalBigWhitePigNums()+smallFlowerPig+bigWhitePig)%i!=0) {
                        if((((pigFarm->getTotalSmallFlowerPigNums()+pigFarm->getTotalBigWhitePigNums()+smallFlowerPig+bigWhitePig)/i)+((pigFarm->getTotalBlackPigNums()+blackPig)/i))+1>PigFarm::totalPigStyNums) {
                            continue;
                        }
                    }
                    single=i;
                    hasSpace=true;
                    break;
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


        }
        else
        {
            msgBox.setText("选的猪太多了,猪圈装不下");
            msgBox.exec();
        }





    });
    //点击随机生成按钮后触发
    connect(randomPushButton,&QPushButton::clicked,[=](){

        buttonSound->play();
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
void AddPigWidget::paintEvent(QPaintEvent *event)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/new/prefix1/piggame2.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
AddPigWidget::~AddPigWidget()
{
    delete ui;
}
