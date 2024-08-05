#ifndef MULTIYAXISPLOT_H
#define MULTIYAXISPLOT_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QPainterPath>
#include <QFontDatabase>
#include "devicemanager.h"
#include "model/trend.h"
#include "model/deviceinformation.h"
#include "model/device.h"
#include "signalmanager.h"
#include <QObject>

class LineChartItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(bool showLegend READ getShowLegend WRITE setShowLegend NOTIFY showLegendChanged FINAL)
    Q_PROPERTY(int swipeCurrIndex READ swipeCurrIndex WRITE setSwipeCurrIndex NOTIFY swipeCurrIndexChanged FINAL)
public:
    LineChartItem(QQuickItem *parent = nullptr) : QQuickPaintedItem(parent)
    {
        setIndex(0);
        connect(SignalManager::getInstance(),&SignalManager::showLegend,this,&LineChartItem::setShow);
        emit SignalManager::getInstance()->showLegend();
    }
    void paint(QPainter *painter) override
    {
        painter->setRenderHint(QPainter::Antialiasing);
        // 添加外部字体
        QFontDatabase fontDb;
        int fontId = fontDb.addApplicationFont(":/fonts/SourceHanSansCN-Bold.ttf"); // 替换为你的字体文件路径
        QString fontFamily = fontDb.applicationFontFamilies(fontId).first();
        QFont font(fontFamily);

        // 定义绘图区域
        int margin = 20;
        int marginLeft = showLegend ? margin * 8 : margin * 4; // 设置左边距
        int marginRight = margin; // 设置右边距
        int marginTop = margin * 2; // 设置上边距
        int marginBottom = margin * 2; // 设置下边距
        int yAxisSpacing = 40; // y轴间隔增加一点
        int plotWidth = width() - marginLeft - marginRight;
        int plotHeight = height() - marginTop - marginBottom;
        int numXTicks = 8;
        int numYTicks = 8;
        double xScale;
        double yScale;
        struct LegendItem {
            QPen pen;
            QString label;
            bool visible;
        };
        int hei = height();
        // 绘制x轴
        QPen axisPen(QColor("#a3c7d0"), 2);
        painter->setPen(axisPen);
        painter->drawLine(marginLeft, height() - marginBottom, width() - marginRight, height() - marginBottom);

        // 设置不同颜色的画笔
        QPen yAxisPen1(QColor("#d4b888"), 2);      // 第一个y轴
        QPen yAxisPen2(QColor("#c89baa"), 2);    // 第二个y轴
        QPen yAxisPen3(QColor("#149bff"), 2);     // 第三个y轴
        QPen yAxisPen4(QColor("#d0b7fe"), 2);  // 第四个y轴


        painter->setPen(yAxisPen1);
        painter->drawLine(marginLeft, marginTop, marginLeft, height() - marginBottom); // y轴1

        painter->setPen(yAxisPen2);
        painter->drawLine(marginLeft - yAxisSpacing, marginTop, marginLeft - yAxisSpacing, height() - marginBottom); // y轴2

        if(showLegend){
            // 绘制y轴
            painter->setPen(yAxisPen3);
            painter->drawLine(marginLeft - yAxisSpacing * 2, marginTop, marginLeft - yAxisSpacing * 2, height() - marginBottom); // y轴3

            painter->setPen(yAxisPen4);
            painter->drawLine(marginLeft - yAxisSpacing * 3, marginTop, marginLeft - yAxisSpacing * 3, height() - marginBottom); // y轴4
        }

        // 设置不同颜色的画笔用于刻度线
        QPen tickPen1(QColor("#d4b888"), 1);
        QPen tickPen2(QColor("#c89baa"), 1);
        QPen tickPen3(QColor("#149bff"), 1);
        QPen tickPen4(QColor("#d0b7fe"), 1);


        // 绘制y轴3的刻度线和标签
        painter->setPen(tickPen2);
        font.setPixelSize(12);
        painter->setFont(font);
        for (int i = 0; i < numYTicks; ++i) {
            int y = marginTop + i * plotHeight / numYTicks + 6;
            painter->drawLine(marginLeft - yAxisSpacing - 5, height() - marginBottom/2 - y, marginLeft - yAxisSpacing, height() - marginBottom/2 - y);
            QString label = QString::number((m_yMax1 - m_yMin1)*(i+1)/numYTicks + m_yMin1);
            painter->drawText(marginLeft - yAxisSpacing - 30, height() - marginBottom/2 - y + 5, label);
        }

        // 绘制y轴4的刻度线和标签
        painter->setPen(tickPen1);
        for (int i = 0; i < numYTicks; ++i) {
            int y = marginTop + (i * plotHeight / numYTicks + 6);
            painter->drawLine(marginLeft - 5, height() - marginBottom/2 - y, marginLeft, height() - marginBottom/2 - y);
            QString label = QString::number((m_yMax2 - m_yMin2)*(i+1)/numYTicks + m_yMin2);
            painter->drawText(marginLeft - 30, height() - marginBottom/2 - y + 5, label);
        }
        // 绘制y轴 1  2的刻度线和标签
        if(showLegend){
            painter->setPen(tickPen4);
            for (int i = 0; i < numYTicks; ++i) {
                int y = marginTop + i * plotHeight / numYTicks + 6;
                painter->drawLine(marginLeft - yAxisSpacing * 3 - 5, height() - marginBottom/2 - y, marginLeft - yAxisSpacing * 3, height() - marginBottom/2 - y);
                QString label = QString::number((m_yMax3 - m_yMin3)*(i+1)/numYTicks + m_yMin3);
                painter->drawText(marginLeft - yAxisSpacing * 3 - 30, height() - marginBottom/2 - y + 5, label);
            }
            painter->setPen(tickPen3);
            for (int i = 0; i < numYTicks; ++i) {
                int y = marginTop + i * plotHeight / numYTicks + 6;
                painter->drawLine(marginLeft - yAxisSpacing * 2 - 5, height() - marginBottom/2 - y, marginLeft - yAxisSpacing * 2, height() - marginBottom/2 - y);
                QString label = QString::number((m_yMax4 - m_yMin4)*(i+1)/numYTicks + m_yMin4);
                painter->drawText(marginLeft - yAxisSpacing * 2 - 30, height() - marginBottom/2 - y + 5, label);
            }
        }

        // 绘制x轴标尺
        painter->setPen(Qt::white);
        for (int i = 0; i <= numXTicks; ++i) {
            xScale = marginLeft + i * plotWidth / numXTicks;
            painter->drawLine(xScale, height() - marginBottom, xScale, height() - marginBottom + 5);
            QString label = QString::number((m_xMax - m_xMin)*i/numXTicks + m_xMin);
            painter->drawText(xScale - 10, height() - marginBottom + 20, label);
        }


        //        // 设置网格线的画笔
        //        QPen gridPen(Qt::gray, 1, Qt::DotLine);
        //        painter->setPen(gridPen);

        //        // 绘制垂直网格线
        //        for (int i = 1; i < numXTicks; ++i) {
        //            int x = marginLeft + i * plotWidth / numXTicks;
        //            painter->drawLine(x, marginTop, x, height() - marginBottom);
        //        }

        //        // 绘制水平网格线
        //        for (int i = 0; i < numYTicks; ++i) {
        //            int y = marginTop + i * plotHeight / numYTicks;
        //            painter->drawLine(marginLeft, height() - marginBottom/2 - y, width() - marginRight, height() - marginBottom/2 - y);
        //        }

        // 设置折线的画笔
        QPen linePen1(QColor("#d4b888"), 2);
        QPen linePen2(QColor("#c89baa"), 2);
        QPen linePen3(QColor("#149bff"), 2);
        QPen linePen4(QColor("#d0b7fe"), 2);
        LegendItem legendItems[] = {
            {linePen1, "时间", true},
             {linePen2, "功率", true},
              {linePen3, "焊前高度", showLegend},
               {linePen4, "焊后高度", showLegend}
               };
        // 假设数据点
        QPointF points1[] = {QPointF(marginLeft, height() - marginBottom - 20), QPointF(marginLeft + plotWidth * 0.25, height() - marginBottom - 70), QPointF(marginLeft + plotWidth * 0.5, height() - marginBottom - 100), QPointF(marginLeft + plotWidth * 0.75, height() - marginBottom - 130), QPointF(marginLeft + plotWidth, height() - marginBottom - 150)};
        QPointF points2[] = {QPointF(marginLeft, height() - marginBottom - 30), QPointF(marginLeft + plotWidth * 0.25, height() - marginBottom - 80), QPointF(marginLeft + plotWidth * 0.5, height() - marginBottom - 110), QPointF(marginLeft + plotWidth * 0.75, height() - marginBottom - 140), QPointF(marginLeft + plotWidth, height() - marginBottom - 160)};
        QPointF points3[] = {QPointF(marginLeft, height() - marginBottom - 40), QPointF(marginLeft + plotWidth * 0.25, height() - marginBottom - 90), QPointF(marginLeft + plotWidth * 0.5, height() - marginBottom - 120), QPointF(marginLeft + plotWidth * 0.75, height() - marginBottom - 150), QPointF(marginLeft + plotWidth, height() - marginBottom - 170)};
        QPointF points4[] = {QPointF(marginLeft, height() - marginBottom - 50), QPointF(marginLeft + plotWidth * 0.25, height() - marginBottom - 100), QPointF(marginLeft + plotWidth * 0.5, height() - marginBottom - 130), QPointF(marginLeft + plotWidth * 0.75, height() - marginBottom - 160), QPointF(marginLeft + plotWidth, height() - marginBottom - 180)};
        dataPoints[0].append(QPointF(0 ,0));
        dataPoints[0].append(QPointF(10,10));
        dataPoints[0].append(QPointF(20,0));
        // 绘制折线
        auto drawLine = [&](QPen linePen,const QVector<QPointF> &points, bool showLine,int index) {
            if (showLine) {
                painter->setPen(linePen);
                QVector<QPointF> plotPoints;
                double scale1 = double(plotWidth / numXTicks)/ ((m_xMax - m_xMin)/numXTicks + m_xMin);
                double scale2;
                if(index == 1){
                    scale2 = double(plotHeight / numYTicks) / double(double(m_yMax1 - m_yMin1)/numYTicks + m_yMin1);
                }
                else if(index == 2){
                    scale2 = double(plotHeight / numYTicks) / double(double(m_yMax2 - m_yMin2)/numYTicks + m_yMin2);
                }
                else if(index == 3){
                    scale2 = double(plotHeight / numYTicks) / double(double(m_yMax3 - m_yMin3)/numYTicks + m_yMin3);
                }
                else if(index == 4){
                    scale2 = double(plotHeight / numYTicks) / double(double(m_yMax4 - m_yMin4)/numYTicks + m_yMin4);
                }
                for (int var = 0; var < points.size(); ++var) {
                    double x = points.at(var).x() * scale1 + marginLeft;
                    double y = height() - marginBottom - points.at(var).y() * scale2;
                    plotPoints.append(QPointF(x,y));
                }
                painter->drawPolyline(plotPoints.data(), plotPoints.size());
            }
        };


        // 绘制折线
        drawLine(linePen1, dataPoints[0], legendItems[0].visible, 1);
        drawLine(linePen2, dataPoints[1], legendItems[1].visible, 2);
        drawLine(linePen3, dataPoints[2], legendItems[2].visible, 3);
        drawLine(linePen4, dataPoints[3], legendItems[3].visible, 4);

        // 绘制图例
        int legendWidth = 60;
        int legendHeight = 20;
        int legendSpacing = 20; // 增加图例之间的间距
        int totalLegendWidth =showLegend ? (legendWidth + legendSpacing) * 4 : (legendWidth + legendSpacing) * 2;
        int legendX = (width() - totalLegendWidth) / 2 +10; // 图例居中
        int legendY = margin / 2; // 图例位置在顶部绘制区域上方

        // 设置字体并绘制文本
        font.setPixelSize(16);
        int currentX = legendX;
        for (int i = 0; i < 4; ++i) {
            if (legendItems[i].visible) {
                painter->setPen(legendItems[i].pen);
                if(i == 3){
                    painter->drawLine(currentX+20, legendY + legendHeight / 2, currentX + 40, legendY + legendHeight / 2);
                    painter->setPen(Qt::white);
                    painter->setFont(font);
                    painter->drawText(currentX + 50, legendY + legendHeight / 2 + 5, legendItems[i].label);
                    currentX += legendWidth + legendSpacing;
                }
                else{
                    painter->drawLine(currentX, legendY + legendHeight / 2, currentX + 20, legendY + legendHeight / 2);
                    painter->setPen(Qt::white);
                    painter->setFont(font);
                    painter->drawText(currentX + 30, legendY + legendHeight / 2 + 5, legendItems[i].label);
                    currentX += legendWidth + legendSpacing;
                }
            }
        }
    }
    Q_INVOKABLE bool getShowLegend() const
    {
        return showLegend;
    }

    Q_INVOKABLE void setShowLegend(bool newShowLegend)
    {
        if (showLegend == newShowLegend)
            return;
        showLegend = newShowLegend;
        emit showLegendChanged();
    }

    Q_INVOKABLE void setDataPoints(int index, const QVector<QPointF> &points) {
        if (index < 0 || index >= 4) return; // Index out of range
        dataPoints[index] = points;
    }
    Q_INVOKABLE int swipeCurrIndex() const
    {
        return m_swipeCurrIndex;
    }

    Q_INVOKABLE void setSwipeCurrIndex(int newSwipeCurrIndex)
    {
        if (m_swipeCurrIndex == newSwipeCurrIndex)
            return;
        m_swipeCurrIndex = newSwipeCurrIndex;
        setIndex(m_swipeCurrIndex);
        emit swipeCurrIndexChanged();
    }
    void setIndex(int index){
        if(index >= DeviceManager::getInstance()->deviceList().size())
            return;
        m_xMin = DeviceManager::getInstance()->deviceList().at(index)->pTrend()->idMinX();
        m_xMax = DeviceManager::getInstance()->deviceList().at(index)->pTrend()->idMaxX();
        m_yMin1 = DeviceManager::getInstance()->deviceList().at(index)->pTrend()->timeMinY();
        m_yMax1 = DeviceManager::getInstance()->deviceList().at(index)->pTrend()->timeMaxY();
        m_yMin2 = DeviceManager::getInstance()->deviceList().at(index)->pTrend()->powerMinY();
        m_yMax2 = DeviceManager::getInstance()->deviceList().at(index)->pTrend()->powerMaxY();
        m_yMin3 = DeviceManager::getInstance()->deviceList().at(index)->pTrend()->beforeMinY();
        m_yMax3 = DeviceManager::getInstance()->deviceList().at(index)->pTrend()->beforeMaxY();
        m_yMin4 = DeviceManager::getInstance()->deviceList().at(index)->pTrend()->afterMinY();
        m_yMax4 = DeviceManager::getInstance()->deviceList().at(index)->pTrend()->afterMaxY();
        //        setDataPoints(index,);
    }
public slots:
    void setShow(){
        if(m_swipeCurrIndex >= DeviceManager::getInstance()->deviceList().size())
            return;
        if(DeviceManager::getInstance()->deviceList().at(m_swipeCurrIndex)->pDeviceInformation()->heightOption() == 0){
            setShowLegend(false);
        }
        else{
            setShowLegend(true);
        }
        update();
    }
signals:
    void showLegendChanged();

    void swipeCurrIndexChanged();


private:
    // 设置图例可见性
    bool showLegend = false; // 控制图例是否显示
    int m_swipeCurrIndex = 0;
    int m_xMin = 0;
    int m_xMax = 100;
    int m_yMin1 = 0;
    int m_yMax1 = 100;
    int m_yMin2 = 0;
    int m_yMax2 = 100;
    int m_yMin3 = 0;
    int m_yMax3 = 100;
    int m_yMin4 = 0;
    int m_yMax4 = 100;
    QVector<QPointF> dataPoints[4];
};




#endif // MULTIYAXISPLOT_H
