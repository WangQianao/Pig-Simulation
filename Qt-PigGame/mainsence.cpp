#include "mainsence.h"
#include "ui_mainsence.h"
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include "addpigwidget.h"
MainSence::MainSence(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainSence)
{
    ui->setupUi(this);
    this->setFixedSize(400,600);
    this->setWindowTitle("养猪游戏");
    //设置游戏退出按钮
    QPushButton * exitButton=new QPushButton("退出",this);
    exitButton->move(this->width()*0.5-exitButton->width()*0.5,this->height()*0.7);
    connect(exitButton,&QPushButton::clicked,[=](){
        this-close();
    });
    //设置开始游戏按钮
    QPushButton * newBeginButton=new QPushButton("新的开始",this);
    newBeginButton->move(this->width()*0.5-newBeginButton->width()*0.5,this->height()*0.3);
    connect(newBeginButton,&QPushButton::clicked,[=](){

        delete this->pigFarm;
        pigFarm=new PigFarm;
        delete this->gameMenu;
        gameMenu = new GameMenu(pigFarm);
        this->hide();
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        QString txt ="欢迎开始新的游戏，现在请为养猪场添加第一批猪崽";
         msgBox.setText(txt);
         msgBox.exec();
        pigFarm->addPigs(gameMenu->gameDay);
        connect(pigFarm,&PigFarm::addSuccess,[=](){//这个函数运行完后一定会将购买窗口关闭
            QTimer::singleShot(500,this,[=](){

                 gameMenu->show();
            });
        });



    });
    //设置读取存档按钮
    QPushButton * readOldButton=new QPushButton("读取存档",this);
    readOldButton->move(this->width()*0.5-exitButton->width()*0.5,this->height()*0.5);
    connect(readOldButton,QPushButton::clicked,[=](){
        this-close();
    });
    //监听选择场景的返回按钮
    connect(gameMenu,&GameMenu::gameMenuBack,[=](){
                    this->show();
               });
}

MainSence::~MainSence()
{
    delete ui;
}
