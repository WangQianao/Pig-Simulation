#include "drawgraph.h"
#include <QPainter>

DrawGraph::DrawGraph(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(500, 700);
    this->setWindowTitle("该品种猪的总数量，及体重饲养时间分布图");
}


DrawGraph::~DrawGraph()
{

}

void DrawGraph::paintEvent(QPaintEvent *e)
{
    m_nPeopleCount = 0;

    m_answerStrList = m_answerMap.keys();
    m_numList = m_answerMap.values();
    foreach (int num, m_numList) {
        m_nPeopleCount += num;
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);

    if(m_numList.isEmpty())
    {
        return;
    }

    painter.setPen(Qt::black);

    int lineWidth = 450;
    int lineX = this->width()/2 - lineWidth/2;
    int lineY = 670;
    painter.drawLine(lineX, lineY, lineX + lineWidth, lineY);

    int answerCount = m_answerStrList.count();
    int maxWidth = 45;
    int maxHeight = 1000;

    int curWidth = maxWidth - (answerCount - 1)*3;
    int unitWidth = lineWidth/answerCount;

    //获取选项中值最大的那个，以这个为基准高度，来计算其他值的高度
    int maxVal = getMaxVal(m_numList);
    int unitHeight = 0;
    if(maxVal)
    {
        unitHeight = maxHeight/maxVal;
    }

    QFont ft;
    ft.setPixelSize(13);
    for(int i = 0; i < m_answerStrList.count(); ++i)
    {
        QString answerStr = m_answerStrList.at(i);
        int selectNum = m_numList.at(i);
        QString selectNumStr = QString::number(selectNum);

        int x = lineX + i*unitWidth + unitWidth/2 - curWidth/2;
        //绘制柱状图
        int GraphHight = selectNum*unitHeight*0.6;
        QRect r = QRect(x, lineY - GraphHight, curWidth, GraphHight);
        QPainterPath path;
        path.addRect(r);
        painter.fillPath(path, QColor(185, 185, 185));

        //绘制答案
        QFontMetrics metrics(ft);
        int charWitdh = metrics.width(answerStr);
        QRect answerRect;
        /*
/**     对比文字长度和柱状图的宽度，比柱状图宽的以文字的长度为基准会画，反之以
 *      柱状图的宽度来画，保证显示全并居中，下面的也是一样
 */
        if(charWitdh < curWidth)
        {
            answerRect = QRect(x, lineY, curWidth, 30);
        }
        else
        {
            answerRect = QRect(x - (charWitdh - curWidth)/2, lineY, charWitdh, 30);
        }
        painter.drawText(answerRect, Qt::AlignCenter, answerStr);

        //绘制每个选项对应的值
        QRect percentRect;
        charWitdh = metrics.width(selectNumStr);
        if(charWitdh < curWidth)
        {
            percentRect = QRect(x, lineY - GraphHight - 30, curWidth, 30);
        }
        else
        {
            percentRect = QRect(x - (charWitdh - curWidth)/2, lineY - GraphHight - 40, charWitdh, 30);
        }
        painter.drawText(percentRect, Qt::AlignCenter, selectNumStr);

    }
}

int DrawGraph::getMaxVal(QList<int> list)
{
    qSort(list.begin(), list.end());
    return list.last();
}
