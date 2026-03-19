#include <QDebug>
#include "modbus/servers.h"
#include "modbus/hbclient.h"
#include "app/ethernetapp.h"
#include "app/serialapp.h"
#include "app/interfaceapp.h"
#include "app/systemclock.h"
#include "hardware/serial.h"
#include "hardware/rtc_ds3231.h"
#include "decryption/decryption.h"
#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include <QThread>
#include <QDateTime>

#include "protocol/tcpip2000x.h"
static ModbusServers* _servers = nullptr;
static bool bResult = false;
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    // SystemClock::GetInstance()->SyncSystemClock();

    // _servers = new ModbusServers(nullptr);
    // _servers->Init();

    // Decryption* _decryption = new Decryption(nullptr);

    // if(_decryption->DecryptLicenseFile() == false)
    // {
    //     QTimer::singleShot(600000, &app, &QCoreApplication::quit); //it will be running 10min
    // }

    // if(_decryption->DecryptLicenseFile() == false)
    // {
    //     QTimer::singleShot(60000, [&app]() {
    //         qDebug() << "Timer triggered at" << QDateTime::currentDateTime().toString();
    //         if(bResult == false)
    //         {
    //             delete _servers;
    //             _servers = nullptr;
    //         }
    //     });
    // }

    qDebug()<< "Modbus Server Application Running ";

    /***********************Test Code******************************/
    QString m_strBuffer;
    unsigned char _Recv_buffer[2048];
    memset(_Recv_buffer, 0, 2048);
    // 10 02 00 76 00 1A 00 00 00 1C 
    // 00 0F 02 1D 00 1A 03 09 00 00 
    // 01 61 00 00 00 96 00 00 2E 82 
    // 00 00 00 19 00 00 00 19 00 00 
    // 4E 1C 00 00 4E 31 00 00 00 15 
    // 00 00 4E 17 00 00 4E 31 00 00 
    // 01 27 00 00 2E 69 00 00 00 00 
    // 00 00 00 00 00 00 00 00 00 00 
    // 00 00 00 00 00 00 00 00 00 00 
    // 00 00 01 00 00 00 00 00 00 00 
    // 00 0F 00 00 00 64 02 05 00 0E 
    // 01 1D 05 CF 05 CF 00 00 05 5D 
    // 02 00 10 03 05 

    _Recv_buffer[0] = 0x10;
    _Recv_buffer[1] = 0x02;
    _Recv_buffer[2] = 0x00;
    _Recv_buffer[3] = 0x76;
    _Recv_buffer[4] = 0x00;
    _Recv_buffer[5] = 0x1A;
    _Recv_buffer[6] = 0x00;
    _Recv_buffer[7] = 0x00;
    _Recv_buffer[8] = 0x00;
    _Recv_buffer[9] = 0x1C;

    _Recv_buffer[10] = 0x00;
    _Recv_buffer[11] = 0x0F;
    _Recv_buffer[12] = 0x02;
    _Recv_buffer[13] = 0x1D;
    _Recv_buffer[14] = 0x00;
    _Recv_buffer[15] = 0x1A;
    _Recv_buffer[16] = 0x03;
    _Recv_buffer[17] = 0x09;
    _Recv_buffer[18] = 0x00;
    _Recv_buffer[19] = 0x00;

    _Recv_buffer[20] = 0x01;
    _Recv_buffer[21] = 0x61;
    _Recv_buffer[22] = 0x00;
    _Recv_buffer[23] = 0x00;
    _Recv_buffer[24] = 0x00;
    _Recv_buffer[25] = 0x96;
    _Recv_buffer[26] = 0x00;
    _Recv_buffer[27] = 0x00;
    _Recv_buffer[28] = 0x2E;
    _Recv_buffer[29] = 0x82;

    _Recv_buffer[30] = 0x00;
    _Recv_buffer[31] = 0x00;
    _Recv_buffer[32] = 0x00;
    _Recv_buffer[33] = 0x19;
    _Recv_buffer[34] = 0x00;
    _Recv_buffer[35] = 0x00;
    _Recv_buffer[36] = 0x00;
    _Recv_buffer[37] = 0x19;
    _Recv_buffer[38] = 0x00;
    _Recv_buffer[39] = 0x00;

    _Recv_buffer[40] = 0x4E;
    _Recv_buffer[41] = 0x1C;
    _Recv_buffer[42] = 0x00;
    _Recv_buffer[43] = 0x00;
    _Recv_buffer[44] = 0x4E;
    _Recv_buffer[45] = 0x31;
    _Recv_buffer[46] = 0x00;
    _Recv_buffer[47] = 0x00;
    _Recv_buffer[48] = 0x00;
    _Recv_buffer[49] = 0x15;

    _Recv_buffer[50] = 0x00;
    _Recv_buffer[51] = 0x00;
    _Recv_buffer[52] = 0x4E;
    _Recv_buffer[53] = 0x17;
    _Recv_buffer[54] = 0x00;
    _Recv_buffer[55] = 0x00;
    _Recv_buffer[56] = 0x4E;
    _Recv_buffer[57] = 0x31;
    _Recv_buffer[58] = 0x00;
    _Recv_buffer[59] = 0x00;

    _Recv_buffer[60] = 0x01;
    _Recv_buffer[61] = 0x27;
    _Recv_buffer[62] = 0x00;
    _Recv_buffer[63] = 0x00;
    _Recv_buffer[64] = 0x2E;
    _Recv_buffer[65] = 0x69;
    _Recv_buffer[66] = 0x00;
    _Recv_buffer[67] = 0x00;
    _Recv_buffer[68] = 0x00;
    _Recv_buffer[69] = 0x00;

    _Recv_buffer[70] = 0x00;
    _Recv_buffer[71] = 0x00;
    _Recv_buffer[72] = 0x00;
    _Recv_buffer[73] = 0x00;
    _Recv_buffer[74] = 0x00;
    _Recv_buffer[75] = 0x00;
    _Recv_buffer[76] = 0x00;
    _Recv_buffer[77] = 0x00;
    _Recv_buffer[78] = 0x00;
    _Recv_buffer[79] = 0x00;

    _Recv_buffer[80] = 0x00;
    _Recv_buffer[81] = 0x00;
    _Recv_buffer[82] = 0x00;
    _Recv_buffer[83] = 0x00;
    _Recv_buffer[84] = 0x00;
    _Recv_buffer[85] = 0x00;
    _Recv_buffer[86] = 0x00;
    _Recv_buffer[87] = 0x00;
    _Recv_buffer[88] = 0x00;
    _Recv_buffer[89] = 0x00;

    _Recv_buffer[90] = 0x00;
    _Recv_buffer[91] = 0x00;
    _Recv_buffer[92] = 0x01;
    _Recv_buffer[93] = 0x00;
    _Recv_buffer[94] = 0x00;
    _Recv_buffer[95] = 0x00;
    _Recv_buffer[96] = 0x00;
    _Recv_buffer[97] = 0x00;
    _Recv_buffer[98] = 0x00;
    _Recv_buffer[99] = 0x00;

    _Recv_buffer[100] = 0x00;
    _Recv_buffer[101] = 0x0F;
    _Recv_buffer[102] = 0x00;
    _Recv_buffer[103] = 0x00;
    _Recv_buffer[104] = 0x00;
    _Recv_buffer[105] = 0x64;
    //Weld Mode
    _Recv_buffer[106] = 0x02;
    _Recv_buffer[107] = 0x05;
    //Peak Power
    _Recv_buffer[108] = 0x00;
    _Recv_buffer[109] = 0x0E;

    _Recv_buffer[110] = 0x01;
    _Recv_buffer[111] = 0x1D;

    _Recv_buffer[112] = 0x05;
    _Recv_buffer[113] = 0xCF;

    _Recv_buffer[114] = 0x05;
    _Recv_buffer[115] = 0xCF;

    //Total Cycle Time, 
    _Recv_buffer[116] = 0x00;
    _Recv_buffer[117] = 0x00;
    _Recv_buffer[118] = 0x05;
    _Recv_buffer[119] = 0x5D;

    // 02 00 10 03 05 
    _Recv_buffer[120] = 0x02;
    _Recv_buffer[121] = 0x00;
    _Recv_buffer[122] = 0x10;
    _Recv_buffer[123] = 0x03;
    _Recv_buffer[124] = 0x05;

    m_strBuffer.clear();
    m_strBuffer = QString::fromLatin1(reinterpret_cast<const char*>(_Recv_buffer), 125);

    TcpIp2000x* _ptr2000x = new TcpIp2000x();
    _ptr2000x->ParseWeldResult(m_strBuffer);


    /*************************************************************/
    return app.exec();

    // if(_servers != nullptr)
    //     delete _servers;
    // delete _decryption;
}
