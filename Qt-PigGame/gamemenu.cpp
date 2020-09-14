#include "gamemenu.h"
#include <QTimer>
#include<QPushButton>
#include<QDebug>
#include<QLabel>
#include<QPainter>
#include<QFile>
#include<QFileInfo>
#include<QFileDialog>
#include<QDir>
#include<QMessageBox>
GameMenu::GameMenu(PigFarm*pigFarm,QWidget *parent) : QMainWindow(parent)
{
     checkMenu = new CheckMenu(pigFarm);
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("养猪场");
    //设置返回游戏主界面的按钮
    QPushButton * exitButton=new QPushButton("退回游戏主界面(不会自动保存)",this);
    exitButton->setFixedSize(200,50);
    exitButton->move(this->width()*0.5-exitButton->width()*0.5,this->height()*0.8);
    connect(exitButton,&QPushButton::clicked,[=](){

                   this->hide();
                   //触发自定义信号，关闭自身，该信号写到 signals下做声明
                   emit this->gameMenuBack();


    });

     //设置去到查询窗口的按钮
    QPushButton * checkButton=new QPushButton("查询猪场相关信息",this);
    checkButton->move(this->width()*0.5-checkButton->width()*0.5,this->height()*0.1);
    connect(checkButton,&QPushButton::clicked,[=](){


            this->hide();
            checkMenu->show();


    });
    //监听查询场景的返回按钮
    connect(checkMenu,&CheckMenu::checkMenuBack,[=](){
                    this->show();
               });
    //设置进入下一天的按钮
    //并且实现按下按钮后刷新左下角的天数
    QPushButton * nextDayButton=new QPushButton("进入下一天",this);
    nextDayButton->move(this->width()*0.5-nextDayButton->width()*0.5,this->height()*0.25);
    connect(nextDayButton,QPushButton::clicked,[=](){
        this->gameDay++;
        pigFarm->pigFarmNextTime(1);
        this->update();
        if((gameDay-lastSalePigDay)/30>=3) {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Information);
                 msgBox.setText("现在到了出圈一批猪的时间");
                 msgBox.exec();
                pigFarm->salePigs(gameDay);
                msgBox.setText("同时也要为养猪场购入一批猪崽");
                msgBox.exec();
                pigFarm->addPigs(gameDay);
                lastSalePigDay=gameDay;
        }
    });
    //设置进入下一月的按钮
     //并且实现按下按钮后刷新左下角的天数
    QPushButton * nextMonthButton=new QPushButton("进入下一月",this);
    nextMonthButton->move(this->width()*0.5-nextMonthButton->width()*0.5,this->height()*0.4);
    connect(nextMonthButton,QPushButton::clicked,[=](){
        this->gameDay+=30;
        pigFarm->pigFarmNextTime(30);
        this->update();
        if((gameDay-lastSalePigDay)/30>=3) {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Information);
                 msgBox.setText("现在到了出圈一批猪的时间");
                 msgBox.exec();
                pigFarm->salePigs(gameDay);
                msgBox.setText("同时也要为养猪场购入一批猪崽");
                msgBox.exec();
                pigFarm->addPigs(gameDay);
                lastSalePigDay=gameDay;
        }
    });
    //设置保存按钮
    QPushButton * saveButton=new QPushButton("保存游戏",this);
    saveButton->move(this->width()*0.5-saveButton->width()*0.5,this->height()*0.7);
    connect(saveButton,QPushButton::clicked,[=](){
           emit saveGame();
    });
    //设置猪瘟模拟按钮
    QPushButton * feverSimulationButton=new QPushButton("猪瘟模拟",this);
    feverSimulationButton->move(this->width()*0.5-feverSimulationButton->width()*0.5,this->height()*0.55);
    connect(feverSimulationButton,QPushButton::clicked,[=](){
                emit feverSimulation();
    });
}


 void GameMenu::paintEvent(QPaintEvent *event)
 {
     //显示当前游戏天数
     QPainter painter(this);
     QFont font;
     font.setFamily("华文新魏");
      font.setPointSize(15);
     painter.setFont(font);
     QString str = QString("第 %1 天").arg(this->gameDay);
     painter.drawText(QRect(30, this->height() - 50,120, 50),str);


 }


GameMenu::~GameMenu()
{
    delete checkMenu;
}
