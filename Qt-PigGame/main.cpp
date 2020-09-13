#include "mainsence.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainSence w;
    w.show();

    return a.exec();
}
