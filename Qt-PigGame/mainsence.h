#ifndef MAINSENCE_H
#define MAINSENCE_H

#include <QMainWindow>
#include "gamemenu.h"
#include "pigfarm.h"
namespace Ui {
class MainSence;
}

class MainSence : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainSence(QWidget *parent = 0);
    ~MainSence();
    GameMenu * gameMenu = NULL;
    PigFarm * pigFarm = NULL;
private:
    Ui::MainSence *ui;
};

#endif // MAINSENCE_H
