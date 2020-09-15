#include "mainsence.h"
#include "ui_mainsence.h"
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>
#include "addpigwidget.h"
#include <QFile>
#include <QWidget>
#include <QTextEdit>
#include <QTextStream>
#include <QInputDialog>
#include <QFont>
#include <QPainter>
#include <QPixmap>
MainSence::MainSence(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainSence)
{

    ui->setupUi(this);
    this->setFixedSize(600,600);
    this->setWindowTitle("养猪游戏");
    this->setWindowIcon(QPixmap(":/new/prefix1/pigIcon1.png"));
    //设置游戏退出按钮
    QPushButton * exitButton=new QPushButton("退出",this);
    exitButton->setFixedSize(200,60);
    exitButton->move(this->width()*0.5-exitButton->width()*0.5,this->height()*0.7);
    connect(exitButton,&QPushButton::clicked,[=](){
        this-close();
    });
    //设置开始游戏按钮
    QPushButton * newBeginButton=new QPushButton("新的开始",this);
    newBeginButton->setFixedSize(200,60);
    newBeginButton->move(this->width()*0.5-newBeginButton->width()*0.5,this->height()*0.3);
    connect(newBeginButton,&QPushButton::clicked,[=](){
        pigFarm->clearPigFarm();  //每次开始新的游戏都需要清空养猪场
        gameMenu->gameDay=1;       //每次开始新的游戏将游戏天数初始化
        gameMenu->lastSalePigDay=1;
        gameMenu->money=1000000;
        clearFile("TemporaryPigSaleAndBuyInfo.txt");//开始新的游戏，清空文件内容
        clearFile("PigSaleAndBuyInfo.txt");
        clearFile("PigGameInfo.txt");
        this->hide();
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        QString txt ="欢迎开始新的游戏，现在请为养猪场添加第一批猪崽";
        msgBox.setText(txt);
        msgBox.exec();
        pigFarm->addPigs(gameMenu,gameMenu->gameDay); //刚进入游戏，为养猪场分配第一批猪崽
        connect(pigFarm,&PigFarm::addSuccess,[=](){ //分配猪崽成功，就打开下一个窗口，进入游戏界面

            gameMenu->setGeometry(this->geometry());//使下一个窗口打开时其位置不发生变化
            gameMenu->show();

        });



    });
    //设置读取存档按钮
    QPushButton * readOldButton=new QPushButton("读取存档",this);
    readOldButton->setFixedSize(200,60);
    readOldButton->move(this->width()*0.5-exitButton->width()*0.5,this->height()*0.5);
    connect(readOldButton,QPushButton::clicked,[=](){
        clearFile("TemporaryPigSaleAndBuyInfo.txt");
        pigFarm->clearPigFarm();//读取存档之前也要先将农场初始化
        if(initializeGameByFileAndPrint("PigGameInfo.txt",pigFarm))//如果读取存档成功，则打开下一个窗口，进入游戏界面
        {
            this->hide();
            gameMenu->setGeometry(this->geometry());
            gameMenu->show();

        }


    });
    //监听游戏场景的返回
    connect(gameMenu,&GameMenu::gameMenuBack,[=](){
        this->setGeometry(gameMenu->geometry());//从上一个窗口返回时保持窗口位置不变
        this->show();
    });
    //监听猪瘟模拟的信号
    connect(gameMenu,&GameMenu::feverSimulation,[=]()
    {
        feverSimulation(pigFarm);
    });
    //监听保存游戏的信号
    connect(gameMenu,&GameMenu::saveGame,[=](){
        copySaleFile();
        saveGameInfo("pigGameInfo.txt",pigFarm);
    });
    //监听进入下一天的信号
    connect(gameMenu,&GameMenu::nextDay,[=](){
        nextTime(1);
    });
    //监听进入下一个月的信号
    connect(gameMenu,&GameMenu::nextMonth,[=](){
        nextTime(30);
    });
    //监听从游戏界面返回的查询一个猪圈信息的信号
    connect(gameMenu,&GameMenu::gameCheckPigSty,[=](){
        int Styindex=QInputDialog::getInt(this,"查询猪圈状态","请输入猪圈的编号(0-99)",0,0,99);
        //使用QMessageBox来显示猪圈信息
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText(pigFarm->pigStys[Styindex].print(Styindex));
        msgBox.exec();
    });
    //监听从游戏界面返回的查询一个猪信息的信号
    connect(gameMenu,&GameMenu::gameCheckPig,[=](){
        int styIndex=QInputDialog::getInt(this,"查询某一头猪的状态","请输入猪圈的编号(0-99)",0,0,99);
        if(pigFarm->pigStys[styIndex].getPigNum()==0)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("该猪圈一头猪都没有,故无法查询");
            msgBox.exec();
        }
        else
        {
            QString t = QString("请输入猪的编号(0- %1 )").arg(pigFarm->pigStys[styIndex].getPigNum()-1);
            int pigIndex=QInputDialog::getInt(this,"查询某一头猪的状态",t,0,0,pigFarm->pigStys[styIndex].getPigNum()-1);
            //使用QMessageBox来显示猪的信息
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText(pigFarm->pigStys[styIndex][pigIndex].pigPrint());
            msgBox.exec();
        }
    });
    //监听从游戏界面返回的查询一个猪品种分布信息的信号
    connect(gameMenu,&GameMenu::gameCheckPigBreedDis,[=](){
        //让用户选择查询哪个品种猪的分布
        QStringList items;
        items << "黑猪" << "小花猪" << "大白猪";
        bool ok;
        QInputDialog in ;

        QString item = in.getItem(this, "请选择品种",
                                  "品种:", items, 0, false, &ok);
        if (ok && !item.isEmpty())
        {

            if(item==items[0])
            {
                pigFarm->eachBreedDis(PigBreed::black,0,pigFarm->flowerPigStyIndex);

            }
            else if(item==items[1])
            {

                pigFarm->eachBreedDis(PigBreed::smallFlower,pigFarm->flowerPigStyIndex,PigFarm::totalPigStyNums);
            }else
            {

                pigFarm->eachBreedDis(PigBreed::bigWhite,pigFarm->flowerPigStyIndex,PigFarm::totalPigStyNums);
            }

        }

    });
}
void MainSence::paintEvent(QPaintEvent *event)
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
void MainSence::nextTime(int day)
{
    gameMenu->gameDay+=day;
    pigFarm->pigFarmNextTime(day);//调用函数使养猪场里的每一头猪体重增长
    gameMenu->update();     //刷新窗口
    if(( gameMenu->gameDay- gameMenu->lastSalePigDay)/30>=3) {//如果离上一次购入猪崽的时间已经过去了三个月，就再一次购入
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("现在到了出圈一批猪的时间");
        msgBox.exec();
        pigFarm->salePigs(gameMenu,gameMenu->gameDay);
        msgBox.setText("同时也要为养猪场购入一批猪崽");
        msgBox.exec();
        pigFarm->addPigs( gameMenu, gameMenu->gameDay);
        gameMenu->lastSalePigDay= gameMenu->gameDay;
    }
}
void MainSence::copySaleFile()
{
    QFile ifs("TemporaryPigSaleAndBuyInfo.txt");
    QFile ofs("PigSaleAndBuyInfo.txt");
    if(!ifs.open(QIODevice::ReadOnly|QIODevice::Text)||!ofs.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("打开文件失败");
        msgBox.exec();
        exit(0);
    }
    QByteArray arr=ifs.readAll();
    ofs.write(arr);
    ifs.close();
    ofs.close();
    clearFile("TemporaryPigSaleAndBuyInfo.txt");

}
void MainSence::saveGameInfo(QString filename,PigFarm*pigFarm)
{

    QFile ofs(filename);
    if(!ofs.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("打开文件失败");
        msgBox.exec();
        exit(0);
    }
    QTextStream out(&ofs);

    out<<'#'<<" ";
    out<<gameMenu->gameDay<<" "<<gameMenu->lastSalePigDay<<" "<<gameMenu->money<<"\n";
    out<<pigFarm->getTotalPigNums()<<" "<<pigFarm->getTotalBlackPigNums()<<" "<<pigFarm->getTotalSmallFlowerPigNums()<<" "<<pigFarm->getTotalBigWhitePigNums()<<" "<<pigFarm->getFlowerPigStyIndex()<<"\n";
    for(int i=0; i<PigFarm::totalPigStyNums; i++) {
        out<<pigFarm->pigStys[i].getPigNum()<<" "<<pigFarm->pigStys[i].getBlackPigNum()<<" "<<pigFarm->pigStys[i].getSmallFlowerPigNum()<<" "<<pigFarm->pigStys[i].getBigWhitePigNum()<<"\n";
        for(Pig*p=pigFarm->pigStys[i].first(); p!=pigFarm->pigStys[i].last()->succ; p=p->succ) {
            out<<p->getWeight()<<" "<<p->getGrowDay()<<" "<<p->getBreed()<<"\n";
        }
    }
    ofs.close();
}
void MainSence::clearFile(QString filename)
{

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("打开文件失败");
        msgBox.exec();
        exit(0);
    }
    file.close();
}
void MainSence::feverSimulation(PigFarm*pigFarm)
{
    QWidget * wid = new QWidget;
    wid->setWindowTitle("猪瘟模拟");
    wid->setFixedSize(320,500);
    QTextEdit * edit = new QTextEdit(wid);
    edit->setFixedSize(wid->width(),wid->height());
    saveGameInfo("TemporaryPigGameInfo.txt",pigFarm);
    int styIndex=QInputDialog::getInt(this,"猪瘟模拟","请输入猪圈的编号(0-99)",0,0,99);
    if(pigFarm->pigStys[styIndex].getPigNum()==0)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("该猪圈一头猪都没有");
        msgBox.exec();
    }
    else
    {
        QString t = QString("请输入猪的编号(0- %1 )").arg(pigFarm->pigStys[styIndex].getPigNum()-1);
        int pigIndex=QInputDialog::getInt(this,"猪瘟模拟",t,0,0,pigFarm->pigStys[styIndex].getPigNum()-1);
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("现在开始模拟,刚才选择的猪已患上猪瘟");
        msgBox.exec();
        t="模拟状态下:猪瘟的扩展几率为:\n1.同一个猪圈的猪每天被传染几率是50%\n2.相邻猪圈的猪每天被传染的几率是15%\n3.不相邻的猪圈的猪不传染\n假定一只猪从感染猪瘟到死亡需要7天\n";
        QString s=QString("经过模拟,该猪的猪瘟后,如果不采取任何措施,%1天后养猪场里的猪便会死光").arg(pigFarm->fever(styIndex,pigIndex));
        t.append(s);
        QFont fon;
        fon.setFamily("华文新魏");
        fon.setPointSize(15);
        edit->setTextColor(QColor(255,0,0));
        edit->setFont(fon);
        edit->setText(t);
        wid->show();
        edit->show();
        initializeGameByFile("TemporaryPigGameInfo.txt",pigFarm);
    }
}
void  MainSence::initializeGameByFile(QString filename,PigFarm*pigFarm)
{

    QFile ifs(filename);
    if(!ifs.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("打开文件失败");
        msgBox.exec();
        exit(0);
    }
    QTextStream in(&ifs);


    QString line = in.readLine();
    line.remove(0,2);
    QStringList list2 = line.split(' ', QString::SkipEmptyParts);
    QString s= list2[0];
    gameMenu->gameDay=s.toInt();
    s= list2[1];
    gameMenu->lastSalePigDay=s.toInt();

    s= list2[2];
    gameMenu->money=s.toDouble();
    line = in.readLine();
    list2.clear();
    list2 = line.split(' ', QString::SkipEmptyParts);
    s= list2[0];
    pigFarm->setTotalPigNums(s.toInt());

    s= list2[1];
    pigFarm->setTotalBlackPigNums(s.toInt());

    s= list2[2];
    pigFarm->setTotalSmallFlowerPigNums(s.toInt());

    s= list2[3];
    pigFarm->setTotalBigWhitePigNums(s.toInt());
    s= list2[4];
    pigFarm->setFlowerPigStyIndex(s.toInt());

    for(int i=0; i<PigFarm::totalPigStyNums; i++) {

        line = in.readLine();
        list2.clear();
        list2 = line.split(' ', QString::SkipEmptyParts);

        s=list2[0];
        int a=s.toInt();
        int index=0;

        while(a--)
        {

            Pig*p=new Pig;
            line = in.readLine();
            list2.clear();
            list2 = line.split(' ', QString::SkipEmptyParts);
            s=list2[0];

            p->setWeight(s.toDouble());
            s=list2[1];
            p->setGrowDay(s.toInt());
            s=list2[2];
            int c=s.toInt();
            switch(c) {
            case 0:
                p->setBreed(PigBreed::black);
                break;
            case 1:
                p->setBreed(PigBreed::smallFlower);
                break;
            case 2:
                p->setBreed(PigBreed::bigWhite);
                break;
            }

            pigFarm->pigStys[i].insert(p);
            index++;
        }

    }

    ifs.close();

}

bool MainSence::initializeGameByFileAndPrint(QString filename,PigFarm*pigFarm)
{
    QWidget * wid = new QWidget;
    wid->setWindowTitle("存档信息");
    wid->setFixedSize(320,500);
    QTextEdit * edit = new QTextEdit(wid);
    edit->setFixedSize(wid->width(),wid->height());
    QFile ifs(filename);
    if(!ifs.open(QIODevice::ReadOnly|QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("打开文件失败");
        msgBox.exec();
        exit(0);
    }

    bool flag=true;

    QTextStream in(&ifs);

    if(in.atEnd())
    {
        flag=false;
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("当前无存档可读取");
        msgBox.exec();

    }
    else
    {
        QString line = in.readLine();
        line.remove(0,2);
        QStringList list2 = line.split(' ', QString::SkipEmptyParts);
        QString s= list2[0];
        gameMenu->gameDay=s.toInt();
        s= list2[1];
        gameMenu->lastSalePigDay=s.toInt();
        s= list2[2];
        gameMenu->money=s.toDouble();
        s=QString("游戏进行到第%1天,余额%2元").arg(gameMenu->gameDay).arg(QString::number( gameMenu->money,'f',1));
        edit->append(s);

        line = in.readLine();
        list2.clear();
        list2 = line.split(' ', QString::SkipEmptyParts);
        s= list2[0];
        pigFarm->setTotalPigNums(s.toInt());

        s= list2[1];
        pigFarm->setTotalBlackPigNums(s.toInt());

        s= list2[2];
        pigFarm->setTotalSmallFlowerPigNums(s.toInt());

        s= list2[3];
        pigFarm->setTotalBigWhitePigNums(s.toInt());
        s= list2[4];
        pigFarm->setFlowerPigStyIndex(s.toInt());

        edit->append(pigFarm->print());
        for(int i=0; i<PigFarm::totalPigStyNums; i++) {

            line = in.readLine();
            list2.clear();
            list2 = line.split(' ', QString::SkipEmptyParts);
            s=QString("===========猪圈编号%1==========\n共%2头猪,%3头黑猪,%4头小花猪,%5头大白猪").arg(i).arg(list2[0]).arg(list2[1]).arg(list2[2]).arg(list2[3]);
            edit->append(s);
            s=list2[0];
            int a=s.toInt();
            int index=0;

            while(a--)
            {

                Pig*p=new Pig;
                line = in.readLine();
                list2.clear();
                list2 = line.split(' ', QString::SkipEmptyParts);
                s=list2[0];

                p->setWeight(s.toDouble());
                s=list2[1];
                p->setGrowDay(s.toInt());
                s=list2[2];
                int c=s.toInt();
                switch(c) {
                case 0:
                    p->setBreed(PigBreed::black);
                    break;
                case 1:
                    p->setBreed(PigBreed::smallFlower);
                    break;
                case 2:
                    p->setBreed(PigBreed::bigWhite);
                    break;
                }
                s=QString("编号%1 ").arg(index);
                s.append(p->pigPrint());
                edit->append(s);
                pigFarm->pigStys[i].insert(p);
                index++;
            }

        }
        int ret = QMessageBox::question(this, "存档", "存档已经读取完成\n" "你想要查看存档的养猪场信息吗?",QMessageBox::Ok | QMessageBox::No);
        if(ret==QMessageBox::Ok)
        {
            wid->show();
            edit->show();
        }


    }
    ifs.close();
    return flag;
}
MainSence::~MainSence()
{
    delete ui;
    delete gameMenu;
    delete pigFarm;
}
