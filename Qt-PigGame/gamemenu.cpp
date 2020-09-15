#include "gamemenu.h"
#include <QTimer>
#include<QPushButton>
#include<QDebug>
#include<QLabel>
#include<QPainter>
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
#include <QPixmap>
#include <QInputDialog>
GameMenu::GameMenu(QWidget *parent) : QMainWindow(parent)
{
    checkMenu = new CheckMenu;
    this->setWindowIcon(QPixmap(":/new/prefix1/PigIcon.png"));
    //设置窗口固定大小
    this->setFixedSize(600,600);
    //设置标题
    this->setWindowTitle("养猪场");
    //设置返回游戏主界面的按钮
    QPushButton * exitButton=new QPushButton("退回游戏主界面(不会自动保存)",this);
    exitButton->setFixedSize(200,60);
    exitButton->move(this->width()*0.5-exitButton->width()*0.5,this->height()*0.85);
    connect(exitButton,&QPushButton::clicked,[=](){

        this->hide();
        //触发自定义信号，关闭自身，该信号写到 signals下做声明
        emit this->gameMenuBack();


    });

    //设置去到查询窗口的按钮
    QPushButton * checkButton=new QPushButton("查询猪场相关信息",this);
    checkButton->setFixedSize(200,60);
    checkButton->move(this->width()*0.5-checkButton->width()*0.5,this->height()*0.1);
    connect(checkButton,&QPushButton::clicked,[=](){


        this->hide();
        checkMenu->setGeometry(this->geometry());//保持窗口位置不发生变化
        checkMenu->show();


    });
    //监听查询场景的返回按钮
    connect(checkMenu,&CheckMenu::checkMenuBack,[=](){
        this->setGeometry(checkMenu->geometry());//保持窗口位置不发生变化
        this->show();
    });
    //设置进入下一天的按钮
    //并且实现按下按钮后刷新左下角的天数
    QPushButton * nextDayButton=new QPushButton("进入下一天",this);
    nextDayButton->setFixedSize(200,60);
    nextDayButton->move(this->width()*0.5-nextDayButton->width()*0.5,this->height()*0.25);
    connect(nextDayButton,QPushButton::clicked,[=](){
        emit nextDay();

    });
    //设置进入下一月的按钮
    //并且实现按下按钮后刷新左下角的天数,其他同上下一天
    QPushButton * nextMonthButton=new QPushButton("进入下一月",this);
    nextMonthButton->setFixedSize(200,60);
    nextMonthButton->move(this->width()*0.5-nextMonthButton->width()*0.5,this->height()*0.4);
    connect(nextMonthButton,QPushButton::clicked,[=](){
        emit nextMonth();
    });
    //设置保存按钮
    QPushButton * saveButton=new QPushButton("保存游戏",this);
    saveButton->setFixedSize(200,60);
    saveButton->move(this->width()*0.5-saveButton->width()*0.5,this->height()*0.7);
    connect(saveButton,QPushButton::clicked,[=](){
        emit saveGame();
    });
    //设置猪瘟模拟按钮
    QPushButton * feverSimulationButton=new QPushButton("猪瘟模拟",this);
    feverSimulationButton->setFixedSize(200,60);
    feverSimulationButton->move(this->width()*0.5-feverSimulationButton->width()*0.5,this->height()*0.55);
    connect(feverSimulationButton,QPushButton::clicked,[=](){
        emit feverSimulation();
    });

    connect(checkMenu,&CheckMenu::checkPigSty,[=](){
        emit gameCheckPigSty();

    });
    connect(checkMenu,&CheckMenu::checkPig,[=](){
        emit gameCheckPig();

    });
    connect(checkMenu,&CheckMenu::checkPigBreedDis,[=](){
        emit gameCheckPigBreedDis();

    });
}

void GameMenu::paintEvent(QPaintEvent *event)
{
    //显示当前游戏天数
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/new/prefix1/piggame1.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(22);
    painter.setFont(font);
    QString str = QString("第 %1 天").arg(this->gameDay);
    painter.drawText(QRect(30, this->height() - 50,120, 50),str);

}


GameMenu::~GameMenu()
{
    delete checkMenu;
}
