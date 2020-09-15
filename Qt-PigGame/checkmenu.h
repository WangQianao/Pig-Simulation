#ifndef CHECKMENU_H
#define CHECKMENU_H

#include <QMainWindow>
#include <QTextEdit>
#include<QString>
class CheckMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit CheckMenu( QWidget *parent = nullptr);
    void readSaleAndBuyInfo();
    void readInfo( QTextEdit * edit,QString filename);
    void paintEvent(QPaintEvent *event);
signals:
    void checkMenuBack();
    void checkPigSty();
    void checkPig();
    void checkPigBreedDis();
public slots:
};

#endif // CHECKMENU_H
