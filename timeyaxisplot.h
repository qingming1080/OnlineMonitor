#ifndef TIMEYAXISPLOT_H
#define TIMEYAXISPLOT_H

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


class TimeChartItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int swipeCurrIndex READ swipeCurrIndex WRITE setSwipeCurrIndex NOTIFY swipeCurrIndexChanged FINAL)

public:
    TimeChartItem(QQuickItem *parent = nullptr) : QQuickPaintedItem(parent)
    {
        setIndex(0);
        // 初始化数据点（使用时间戳）
        setDataPoints({
            QPointF(QDateTime::fromString("2023-01-01 00:00:00", Qt::ISODate).toMSecsSinceEpoch(), 20.0),
            QPointF(QDateTime::fromString("2023-01-01 01:00:00", Qt::ISODate).toMSecsSinceEpoch(), 40.0),
            QPointF(QDateTime::fromString("2023-01-01 02:00:00", Qt::ISODate).toMSecsSinceEpoch(), 50.0),
            QPointF(QDateTime::fromString("2023-01-01 03:00:00", Qt::ISODate).toMSecsSinceEpoch(), 60.0),
            QPointF(QDateTime::fromString("2023-01-01 04:00:00", Qt::ISODate).toMSecsSinceEpoch(), 100.0)
        });
    }
    void paint(QPainter *painter) override
    {
        painter->setRenderHint(QPainter::Antialiasing);
        // 添加外部字体
        QFontDatabase fontDb;
        int fontId = fontDb.addApplicationFont(":/fonts/SourceHanSansCN-Bold.ttf"); // 替换为你的字体文件路径
        QString fontFamily = fontDb.applicationFontFamilies(fontId).first();
        QFont font(fontFamily);
        painter->setFont(font);
        // 定义绘图区域
        int margin = 25;
        int marginLeft = margin * 2; // 设置左边距
        int marginRight = margin * 2; // 设置右边距
        int marginTop = margin ; // 设置上边距
        int marginBottom = margin * 2; // 设置下边距
        int plotWidth = width() - marginLeft - marginRight;
        int plotHeight = height() - marginTop - marginBottom;

        // 绘制x轴
        QPen axisPen(QColor("#b1d5db"), 2);
        painter->setPen(axisPen);
        painter->drawLine(marginLeft, height() - marginBottom, width() - marginRight, height() - marginBottom);

        // 绘制y轴和刻度线
        painter->setPen(axisPen);
        font.setPixelSize(25);
        int numYTicks = 5;
        for (int i = 0; i < numYTicks; ++i) {
            double y = marginTop + i * plotHeight / numYTicks;
            QString label = QString("%1%2").arg(QString::number((i+1) * 20)).arg("%");
            painter->drawText(marginLeft - 30, height() - marginBottom - y + 5, label);
        }

        // 绘制垂直网格线和时间刻度
        int numXTicks = 6;
        QDateTime a = QDateTime::fromString(DeviceManager::getInstance()->deviceList().at(m_swipeCurrIndex)->pTrend()->startTime()
                                            , Qt::ISODate);
        QDateTime b = QDateTime::fromString(DeviceManager::getInstance()->deviceList().at(m_swipeCurrIndex)->pTrend()->endTime()
                                            , Qt::ISODate);
        qint64 minTime = QDateTime::fromString(DeviceManager::getInstance()->deviceList().at(m_swipeCurrIndex)->pTrend()->startTime()
                                               , Qt::ISODate).toMSecsSinceEpoch();
        qint64 maxTime = QDateTime::fromString(DeviceManager::getInstance()->deviceList().at(m_swipeCurrIndex)->pTrend()->endTime()
                                               , Qt::ISODate).toMSecsSinceEpoch();
        qint64 timeRange = maxTime - minTime;

        for (int i = 0; i <= numXTicks; ++i) {
            int x = marginLeft + i * plotWidth / numXTicks + 10;

            qint64 currentTime = minTime + i * timeRange / numXTicks;
            QString timeLabel = QDateTime::fromMSecsSinceEpoch(currentTime).toString("hh:mm");

            painter->drawText(x - 20, height() - marginBottom + 20, timeLabel);
        }
        // 设置网格线的画笔
        QPen gridPen(Qt::gray, 1, Qt::DotLine);
        painter->setPen(gridPen);
        // 绘制水平网格线
        for (int i = 0; i < numYTicks; ++i) {
            int y = marginTop + i * plotHeight / numYTicks;
            painter->drawLine(marginLeft, height() - marginBottom - y, width() - marginRight, height() - marginBottom - y);
        }

        // 坐标转换函数
        auto mapToPlotCoordinates = [&](const QPointF & point) -> QPointF {
            float x = marginLeft + ((point.x() - minTime) / static_cast<float>(timeRange)) * plotWidth;
            float y = height() - marginBottom - ((point.y() / 100.0) * plotHeight); // y坐标的转换 (假设数据点y的范围是0到100)
            return QPointF(x, y);
        };

        // 绘制折线
        painter->setPen(QPen(QColor("#1398fa"), 2));
        QVector<QPointF> plotPoints;
        for (const QPointF &point : dataPoints) {
            plotPoints.append(mapToPlotCoordinates(point));
        }
        painter->drawPolyline(plotPoints.data(), plotPoints.size());

        // 绘制标记
        painter->setPen(QPen(QColor("#1398fa"), 2));
        painter->setBrush(QColor("#2b70ad"));
        for (const QPointF &point : plotPoints) {
            painter->drawEllipse(point, 4, 4); // 在数据点位置绘制一个半径为4的圆形标记
        }
    }
    void setDataPoints(const QVector<QPointF> &points) {
        dataPoints = points;
    }
    Q_INVOKABLE void setIndex(int index){
        setDataPoints(DeviceManager::getInstance()->deviceList().at(index)->pTrend()->getYieldData());
        update();
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
public slots:

signals:
    void swipeCurrIndexChanged();

private:
    QVector<QPointF> dataPoints;
    int m_swipeCurrIndex = 0;
};



#endif // TIMEYAXISPLOT_H
