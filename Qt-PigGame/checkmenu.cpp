#include "checkmenu.h"
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QWidget>
#include <QTextEdit>
#include <QPainter>
#include <QPixmap>
CheckMenu::CheckMenu(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口固定大小
    this->setFixedSize(600,600);
    this->setWindowIcon(QPixmap(":/new/prefix1/PigIcon.png"));
    //设置标题
    this->setWindowTitle("查询窗口");
    //设置查询某一猪圈的猪的数量和种类的按钮
    QPushButton * checkStyButton=new QPushButton("查询某一猪圈的猪的数量和种类",this);
    checkStyButton->setFixedSize(200,60);
    checkStyButton->move(this->width()*0.5-checkStyButton->width()*0.5,this->height()*0.1);
    connect(checkStyButton,&QPushButton::clicked,[=](){
            emit checkPigSty();
    });

    //设置查询某一猪圈某一头猪的按钮
    QPushButton * checkPigButton=new QPushButton("查询某一猪圈某一头猪",this);
    checkPigButton->setFixedSize(200,60);
    checkPigButton->move(this->width()*0.5-checkPigButton->width()*0.5,this->height()*0.25);
    connect(checkPigButton,&QPushButton::clicked,[=](){
            emit checkPig();

    });
    //设置统计猪场每个品种猪的数量和该品种猪的体重、饲养时间分布情况按钮
    QPushButton * checkDisButton=new QPushButton("查看猪的体重,饲养时间分布",this);
    checkDisButton->setFixedSize(200,60);
    checkDisButton->move(this->width()*0.5-checkDisButton->width()*0.5,this->height()*0.4);
    connect(checkDisButton,&QPushButton::clicked,[=](){
        emit checkPigBreedDis();

    });
    //设置查询销售和购入记录的按钮
    QPushButton * checkSaleAndBuyButton=new QPushButton("查询销售和购入记录",this);
    checkSaleAndBuyButton->setFixedSize(200,60);
    checkSaleAndBuyButton->move(this->width()*0.5-checkSaleAndBuyButton->width()*0.5,this->height()*0.55);
    connect(checkSaleAndBuyButton,&QPushButton::clicked,[=](){

        readSaleAndBuyInfo();
    });


    //设置返回游戏主界面的按钮
    QPushButton * exitButton=new QPushButton("返回上一界面",this);
    exitButton->setFixedSize(200,60);
    exitButton->move(this->width()*0.5-exitButton->width()*0.5,this->height()*0.7);
    connect(exitButton,&QPushButton::clicked,[=](){
        this->hide();
        //触发自定义信号，关闭自身，该信号写到 signals下做声明
        emit this->checkMenuBack();

    });

}
void CheckMenu::paintEvent(QPaintEvent *event)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/new/prefix1/piggame1.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
void CheckMenu::readSaleAndBuyInfo()
{
    QWidget * wid = new QWidget;
    wid->setFixedSize(320,500);
    QTextEdit * edit = new QTextEdit(wid);
    edit->setFixedSize(wid->width(),wid->height());
    readInfo(edit,"PigSaleAndBuyInfo.txt");
    readInfo(edit,"TemporaryPigSaleAndBuyInfo.txt");
    wid->show();
    edit->show();

}
void CheckMenu::readInfo( QTextEdit * edit,QString filename)
{
    QFile ifs(filename);
    if(!ifs.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("打开文件失败");
        msgBox.exec();
        exit(0);
    }
    int day,blackPig,smallFlowerPig,bigWhitePig;
    double price;
    QTextStream in(&ifs);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(line[0]=='+')
        {
            line.remove(0,2);
            QStringList list2 = line.split(' ', QString::SkipEmptyParts);

            QString s= list2[0];
            day=s.toInt(0);
            s= list2[1];
            blackPig=s.toInt();
            s= list2[2];
            smallFlowerPig=s.toInt();
            s= list2[3];
            bigWhitePig=s.toInt();
            s=list2[4];
            price=s.toDouble();

            s=QString("在第%1天,卖出%2头黑猪,%3头小花猪,%4头大白猪,总售价%5元").arg(day).arg(blackPig).arg(smallFlowerPig).arg(bigWhitePig).arg(QString::number(price,'f',1));
            edit->append(s);

        }
        else
        {
            line.remove(0,2);
            QStringList list2 = line.split(' ', QString::SkipEmptyParts);

            QString s= list2[0];
            day=s.toInt(0);
            s= list2[1];
            blackPig=s.toInt();
            s= list2[2];
            smallFlowerPig=s.toInt();
            s= list2[3];
            bigWhitePig=s.toInt();
            s=list2[4];
            price=s.toDouble();

            s=QString("在第%1天,购入%2头黑猪,%3头小花猪,%4头大白猪,共花费%5元").arg(day).arg(blackPig).arg(smallFlowerPig).arg(bigWhitePig).arg(QString::number(price,'f',1));
            edit->append(s);
        }



    }
    ifs.close();
}
