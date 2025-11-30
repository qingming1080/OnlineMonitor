#include "subject.h"
#include "QDebug"
#include "proxy.h"
#include "app/interfaceapp.h"
#include "app/ethernetapp.h"
#include "app/serialapp.h"
#include <QThread>
QList<Proxy::MACHINE_DEVICE>        Subject::m_listDevice;
QMap<int, EthernetApp::ETHERNET_DEV>   Subject::m_mapEthernet;
QMap<int, SerialApp::SERIAL_DEV>     Subject::m_mapSerial;
Subject::Subject(QObject *parent)
    : QObject{parent}
{}

Subject::~Subject()
{
    qDebug()<< "the Subject object has been destoried";
}

void Subject::Implement(int arg)
{
    qDebug() << "current thread ID: " << QThread::currentThreadId();
    // int index = 0;
    m_listDevice.clear();
    m_mapEthernet.clear();
    m_mapSerial.clear();

    Proxy::GetInstance()->GetMachineDev(&m_listDevice);

    for(int i = 0; i < EthernetApp::ETHS; i++)
    {
        EthernetApp::GetInstance()->Close(i);

    }
    Ethernet::Reset_W5500();
    Ethernet::Reset_Route();
    // unsigned char Gateway[4]    = {192, 168, 10, 1};
    // unsigned char SubnetMask[4] = {255, 255, 255, 0};
    // unsigned char LocalIP[4]    = {192, 168, 10, 38};
    // if(m_mapEthernet.size() > 0)
    // {
    //     memcpy(LocalIP, m_mapEthernet[0].LocalAddr, 4);
    //     memcpy(Gateway, LocalIP, 4);
    //     Gateway[3] = 1;
    //     Ethernet::Set_Local_Eth0(LocalIP, Gateway, SubnetMask);
    //     QMap<int, Proxy::ETHERNET_DEVICE>::iterator iter = m_mapEthernet.begin();
    //     index = 0;
    //     while(iter != m_mapEthernet.end())
    //     {
    //         if(m_listDevice[iter.key()].IsOpen == true)
    //         {
    //             EthernetApp::TCP_PROPERTIES property;
    //             memcpy(property.m_TargeetIP, iter->ServerAddr, 4);
    //             property.m_TargetPort = iter->ServerPort;
    //             EthernetApp::GetInstance()->Open(index, &property);
    //         }
    //         iter++;
    //         index++;
    //     };
    // }

    // for(int i = 0; i < SerialApp::PORTS; i++)
    // {
    //     SerialApp::GetInstance()->Close(i);

    // }
    // if(m_mapSerial.size() > 0)
    // {
    //     QMap<int, Proxy::SERIAL_DEVICE>::iterator iter = m_mapSerial.begin();
    //     index = 0;
    //     while(iter != m_mapSerial.end())
    //     {
    //         if(m_listDevice[iter.key()].IsOpen == true)
    //         {
    //             SerialApp::SERIAL_PROPERTIES property;
    //             property.m_Bandrate = iter->Baudrate;
    //             property.m_DataBits = iter->DataBits;
    //             property.m_Parity = iter->ParityBit;
    //             property.m_StopBits = iter->StopBits;
    //             SerialApp::GetInstance()->Open(index, &property);
    //         }
    //         iter++;
    //         index++;
    //     }
    // }
    qDebug() << "Finish the work and sent the result ";
    emit signalReady(arg);
}
