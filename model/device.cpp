#include "device.h"

#include "model/deviceinformation.h"
#include "model/io.h"
#include "model/manual.h"
#include "model/system.h"
#include "model/trend.h"

#include "signalmanager.h"
#include <QDebug>
#include <QElapsedTimer>
#include "log/localrecord.h"

/// TEST 2024_08_18
#include "message.h"
#include "define.h"
#include <QPointF>
/// TEST 2024_08_18

Device::Device(int welderID, QObject *parent)
    : QObject{parent}, m_welderID(welderID),plotIndex(0)
{
    QElapsedTimer timer;
    timer.start();

    m_pDeviceInformation  = new DeviceInformation(m_welderID);
    m_pIO                 = new IO(m_welderID);
    m_pManual             = new Manual(m_welderID);
    m_pSystem             = new System(m_welderID);
    m_pTrend              = new Trend(m_welderID);

    QString text = QString("%1号设备_Device_初始化共耗时:%2ms").arg(welderID).arg(timer.elapsed());
                       emit SignalManager::getInstance()->signalAddRecord(QDateTime::currentDateTime(), text);
}

Device::~Device()
{
    delete m_pDeviceInformation;
    delete m_pIO;
    delete m_pManual;
    delete m_pSystem;
    delete m_pTrend;
}

DeviceInformation *Device::pDeviceInformation() const
{
    return m_pDeviceInformation;
}

System *Device::pSystem() const
{
    return m_pSystem;
}

IO *Device::pIO() const
{
    return m_pIO;
}

Trend *Device::pTrend() const
{
    return m_pTrend;
}

// void Device::test()
// {
//     /// 实时良率
//     int hegeNum   = qrand() % 100;
//     int keyiNum   = qrand() % 100;
//     int cipingNum = qrand() % 100;

//     this->pDeviceInformation()->setGoodCycles(hegeNum);
//     this->pDeviceInformation()->setSuspectCycles(keyiNum);
//     this->pDeviceInformation()->setNotDefinite(cipingNum);
//     this->pDeviceInformation()->setGoodRate((double)hegeNum/(hegeNum+keyiNum+cipingNum)*100);
//     qDebug() << QString("I_WANT_TEST 实时良率修改  合格产品：%1  可疑产品：%2  次品：%3").arg(hegeNum).arg(keyiNum).arg(cipingNum);

//                 /// 焊接结果
//                 int power        = qrand() % 100;
//     int time         = qrand() % 100;
//     int energy       = qrand() % 100;
//     int heightPre    = qrand() % 100;
//     int heightPost   = qrand() % 100;

//     this->pDeviceInformation()->setPower(power);
//     this->pDeviceInformation()->setTime(time);
//     this->pDeviceInformation()->setEnergy(energy);
//     this->pDeviceInformation()->setHeightPre(heightPre);
//     this->pDeviceInformation()->setHeightPost(heightPost);
//     //    qDebug() << QString("I_WANT_TEST 焊接结果修改  功率:%1  时间:%2  能量:%3  焊前高度:%1  焊后高度:%2").arg(power).arg(time).arg(energy).arg(heightPre).arg(heightPost);

//     /// 系统消息
//     for(int i = 0; i < 10; ++i)
//     {
//         QmlEnum::MESSAGE messageType = static_cast<QmlEnum::MESSAGE>(qrand()%9);
//         Message::getInstance()->addMessage(m_welderID, messageType);
//         //        qDebug() << QString("I_WANT_TEST 设备警告添加消息 ： %1").arg(messageType);
//     }

//     /// 良率折线
//     this->pTrend()->m_yieldData.endTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//     QDateTime endTime = QDateTime::fromString(this->pTrend()->m_yieldData.endTime, "yyyy-MM-dd hh:mm:ss");
//     int interVal;
//     switch(this->pTrend()->yieldType())
//     {
//     case 0:
//         interVal = 0-60*60;
//         break;
//     case 1:
//         interVal = 0-60*60*24;
//         break;
//     case 2:
//         interVal = 0-60*60*24*7;
//         break;
//     case 3:
//         interVal = 0-60*60*24*30;
//         break;
//     }
//     QDateTime startTime = endTime.addSecs(interVal);
//     this->pTrend()->m_yieldData.startTime = startTime.toString("yyyy-MM-dd hh:mm:ss");
//     int timeInterVal = -interVal / 60;

//     this->pTrend()->m_yieldData.points.clear();
//     for(int i = 0; i < 60; ++i)
//     {
//         QPointF pos;
//         pos.rx() = startTime.addSecs(timeInterVal * i).toMSecsSinceEpoch();
//         pos.ry() = qrand() % 100;
//         this->pTrend()->m_yieldData.points.push_back(pos);
//     }
//     this->pTrend()->setYieldTrendData();
//     //    qDebug() << QString("I_WANT_TEST 良率折线图刷新");

//     /// 焊接折线
//     this->pTrend()->setIdMaxX(150);
//     this->pTrend()->setIdMinX(0);
//     this->pTrend()->setBeforeMaxY(150);
//     this->pTrend()->setBeforeMinY(0);
//     this->pTrend()->setAfterMaxY(150);
//     this->pTrend()->setAfterMinY(0);
//     this->pTrend()->setTimeMaxY(150);
//     this->pTrend()->setTimeMinY(0);
//     this->pTrend()->setPowerMaxY(150);
//     this->pTrend()->setPowerMinY(0);
//     this->pTrend()->m_frontData.clear();
//     this->pTrend()->m_backData.clear();
//     this->pTrend()->m_timeData.clear();
//     this->pTrend()->m_powerData.clear();
//     for(int i = 0; i < 150; ++i){
//         QPointF pos;
//         pos.setX(i+1);
//         pos.setY(qrand() % 100);
//         this->pTrend()->m_frontData.push_back(pos);
//         pos.setY(qrand() % 100);
//         this->pTrend()->m_backData.push_back(pos);
//         pos.setY(qrand() % 100);
//         this->pTrend()->m_timeData.push_back(pos);
//         pos.setY(qrand() % 100);
//         this->pTrend()->m_powerData.push_back(pos);
//     }
//     this->pTrend()->upWeldData();
// }

int Device::getPlotIndex() const {
    return plotIndex;
}

void Device::incrementPlotIndex() {
    plotIndex++;
}

Manual *Device::pManual() const
{
    return m_pManual;
}
