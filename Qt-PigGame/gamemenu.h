#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QMainWindow>
#include "checkmenu.h"
#include "pigfarm.h"
class GameMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameMenu( PigFarm*pigFarm, QWidget *parent = nullptr);
    CheckMenu * checkMenu = new CheckMenu;
    int gameDay=1;
    int lastSalePigDay=1;
    void paintEvent(QPaintEvent *event);
signals:
    void gameMenuBack();
public slots:
};

#endif // GAMEMENU_H
