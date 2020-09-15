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
    drawCount = 0;

    drawStrList = drawMap.keys();
    drawList = drawMap.values();
    foreach (int num, drawList) {
        drawCount += num;
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine,
                        Qt::FlatCap, Qt::MiterJoin));


    if(drawList.isEmpty())
    {
        return;
    }

    int lineWidth = 460;   //设置坐标轴的宽度
    int lineX = this->width()/2 - lineWidth/2;
    int lineY = 670;
    painter.drawLine(lineX, lineY, lineX + lineWidth, lineY);//画出坐标轴

    int keyCount = drawStrList.count();   //键的个数
    int maxWidth = 45;
    int maxHeight = 1000;

    int axiWidth = maxWidth - (keyCount - 1)*3;//柱状图的宽度
    int unitWidth = lineWidth/keyCount; //每个部件的宽度

    //获取选项中值最大的那个，以这个为基准高度，来计算其他值的高度
    int maxVal = getMax(drawList);
    int unitHeight = 0;
    if(maxVal)
    {
        unitHeight = maxHeight/maxVal;
    }

    QFont ft;
    ft.setPixelSize(13);
    for(int i = 0; i < drawStrList.count(); i++)
    {
        QString keyStr = drawStrList.at(i);//取出键
        int valueNum = drawList.at(i);//取出值
        QString valueNumStr = QString::number(valueNum);//将值化成string类型

        int x = lineX + i*unitWidth + unitWidth/2 - axiWidth/2;
        //绘制柱状图
        int GraphHight = valueNum*unitHeight*0.6;  //柱状图的高度
        QRect r = QRect(x, lineY - GraphHight, axiWidth, GraphHight);//柱状图的矩形
        QPainterPath path;
        path.addRect(r);
        painter.fillPath(path, QColor(Qt::cyan));//在矩形里填充颜色

        //绘制文字
        QFontMetrics metrics(ft);
        int charWidth = metrics.width(keyStr);//得到键的宽度
        QRect keyRect;
        /*
       对比文字长度和柱状图的宽度，比柱状图宽的以文字的长度为基准画，反之以
       柱状图的宽度来画，保证显示全并居中.主要用来绘制键和值
        */
        if(charWidth < axiWidth)
        {
            keyRect = QRect(x, lineY, axiWidth, 30);//以柱状图的宽度画
        }
        else
        {
            keyRect = QRect(x - (charWidth - axiWidth)/2, lineY, charWidth, 30);//以文字宽度画
        }
        painter.drawText(keyRect, Qt::AlignCenter, keyStr);

        //绘制每个选项对应的值
        QRect valueRect;
        charWidth = metrics.width(valueNumStr);//得到值的宽度
        if(charWidth < axiWidth)
        {
            valueRect = QRect(x, lineY - GraphHight - 30, axiWidth, 30);
        }
        else
        {
            valueRect = QRect(x - (charWidth - axiWidth)/2, lineY - GraphHight - 40, charWidth, 30);
        }
        painter.drawText(valueRect, Qt::AlignCenter, valueNumStr);

    }
}

int DrawGraph::getMax(QList<int> list)
{
    qSort(list.begin(), list.end());
    return list.last();
}
