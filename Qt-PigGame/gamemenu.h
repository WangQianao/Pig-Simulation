#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <QMainWindow>
#include "checkmenu.h"
class GameMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameMenu(  QWidget *parent = nullptr);
    ~GameMenu();
    CheckMenu * checkMenu=NULL;
    int gameDay=1;    //游戏进行天数
    int lastSalePigDay=1; //上一次出售以及购入猪的时间
    double money=900000;// 游戏钱数
    void paintEvent(QPaintEvent *event);


signals:
    void gameMenuBack();
    void feverSimulation();
    void saveGame();
    void nextDay();
    void nextMonth();
    void gameCheckPigSty();
     void gameCheckPig();
     void gameCheckPigBreedDis();
public slots:
};

#endif // GAMEMENU_H
