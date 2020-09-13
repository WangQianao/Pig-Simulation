#include "checkmenu.h"
#include <QPushButton>
#include <QTimer>
CheckMenu::CheckMenu(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle("查询窗口");
    //设置返回游戏主界面的按钮
    QPushButton * exitButton=new QPushButton("返回上一界面",this);
    exitButton->setFixedSize(200,50);
    exitButton->move(this->width()*0.5-exitButton->width()*0.5,this->height()*0.7);
    connect(exitButton,&QPushButton::clicked,[=](){
        QTimer::singleShot(500, this,[=](){
                   this->hide();
                   //触发自定义信号，关闭自身，该信号写到 signals下做声明
                   emit this->checkMenuBack();
                    }
               );
    });

}
