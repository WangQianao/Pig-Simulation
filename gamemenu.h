#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QMainWindow>
#include <QString>
#include "checkmenu.h"
#include "pigfarm.h"
class GameMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameMenu( PigFarm*pigFarm, QWidget *parent = nullptr);
    ~GameMenu();
    CheckMenu * checkMenu=NULL;
    int gameDay=1;
    int lastSalePigDay=1;
    void paintEvent(QPaintEvent *event);


signals:
    void gameMenuBack();
    void feverSimulation();
    void saveGame();
public slots:
};

#endif // GAMEMENU_H
