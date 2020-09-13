#ifndef CHECKMENU_H
#define CHECKMENU_H

#include <QMainWindow>

class CheckMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit CheckMenu(QWidget *parent = nullptr);

signals:
     void checkMenuBack();
public slots:
};

#endif // CHECKMENU_H
