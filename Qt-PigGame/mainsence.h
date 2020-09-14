#ifndef MAINSENCE_H
#define MAINSENCE_H

#include <QMainWindow>
#include "gamemenu.h"
#include "pigfarm.h"
#include <QString>
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
    PigFarm * pigFarm = new PigFarm;
    //void initializeGameByFile(QString filename,PigFarm*pigFarm);
    bool initializeGameByFileAndPrint(QString filename,PigFarm*pigFarm);
    void initializeGameByFile(QString filename,PigFarm*pigFarm);
    void clearFile(QString filename);
    void feverSimulation(PigFarm*pigFarm);
     void copySaleFile();
     void saveGameInfo(QString filename,PigFarm*pigFarm);
private:
    Ui::MainSence *ui;
};

#endif // MAINSENCE_H
