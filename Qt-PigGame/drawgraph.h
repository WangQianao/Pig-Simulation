#ifndef DRAWGRAPH
#define DRAWGRAPH

#include <QMainWindow>
#include <QMap>
#include "pigfarm.h"
#include "pigbreed.h"
class PigFarm;
class DrawGraph : public QMainWindow
{
    Q_OBJECT

public:

   DrawGraph( QWidget *parent = 0);
    ~DrawGraph();
     QMap<QString, int> m_answerMap;

protected:
    void paintEvent(QPaintEvent *e);

private:
    int getMaxVal(QList<int> list);

private:

    QList<int> m_numList;
    QList<QString> m_answerStrList;
    int m_nPeopleCount;


};

#endif // DRAWGRAPH
