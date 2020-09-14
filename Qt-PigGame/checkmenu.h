#ifndef CHECKMENU_H
#define CHECKMENU_H

#include <QMainWindow>
#include <QTextEdit>
#include "pigfarm.h"
#include<QString>
class CheckMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit CheckMenu(PigFarm*pigFarm, QWidget *parent = nullptr);
    void readSaleAndBuyInfo();
    void readInfo( QTextEdit * edit,QString filename);

signals:
     void checkMenuBack();

public slots:
};

#endif // CHECKMENU_H
