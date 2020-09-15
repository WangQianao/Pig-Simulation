#ifndef DRAWGRAPH
#define DRAWGRAPH

#include <QMainWindow>
#include <QMap>
class DrawGraph : public QMainWindow
{
    Q_OBJECT

public:

    DrawGraph( QWidget *parent = 0);
    ~DrawGraph();
    QMap<QString, int> drawMap;

protected:
    void paintEvent(QPaintEvent *e);

private:
    int getMax(QList<int> list);

private:

    QList<int> drawList;
    QList<QString> drawStrList;
    int drawCount;


};

#endif // DRAWGRAPH
