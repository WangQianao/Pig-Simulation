#ifndef ADDPIGWIDGET_H
#define ADDPIGWIDGET_H

#include <QWidget>
#include "pigfarm.h"
class PigFarm;
namespace Ui {
class AddPigWidget;
}

class AddPigWidget : public QWidget
{
    Q_OBJECT

public:
    int blackPig=0;
    int smallFlowerPig=0;
    int bigWhitePig=0;
    int single=0;
    explicit AddPigWidget(PigFarm*pigFarm, QWidget *parent = 0);

    ~AddPigWidget();

private:
    Ui::AddPigWidget *ui;
signals:
     void AddPigWidgetBack();

};

#endif // ADDPIGWIDGET_H
