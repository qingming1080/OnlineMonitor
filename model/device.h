#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

// Forward declarations to avoid recursive includes in headers and reduce
// precompiled-preamble recursion. Include concrete headers in the .cpp.
class DeviceInformation;
class IO;
class Trend;
class Manual;
class System;
class Production;

// class DeviceInformation;
// class IO;
// class IOModel;
// class Manual;
// class System;
// class Trend;

///
/// \brief The Device class : 单个设备
///
class Device : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DeviceInformation* DevInfoObject READ getDevInfoObject   WRITE setDevInfoObject  NOTIFY notifyDevInfoObjectChanged FINAL)    // 设备信息
    Q_PROPERTY(Manual* ManualObj                READ getManualObj       WRITE setManualObj      NOTIFY notifyManualObjChanged FINAL)        // Manual表格
    Q_PROPERTY(Production* ProductionObj        READ getProductionObj   WRITE setProductionObj  NOTIFY notifyProductionObjChanged FINAL)
    Q_PROPERTY(System* SystemObj                READ getSystemObj       WRITE setSystemObj      NOTIFY notifySystemObjChanged FINAL)        // System表格
    Q_PROPERTY(Trend *pTrend                    READ pTrend CONSTANT)               // 折线
public:
    explicit Device(int welderID = 0, QObject *parent = nullptr);
    ~Device();

    DeviceInformation* getDevInfoObject() const;
    void setDevInfoObject(const DeviceInformation* object);
    Manual* getManualObj() const;
    void setManualObj(const Manual* object);
    Production* getProductionObj() const;
    void setProductionObj(const Production* object);
    System* getSystemObj() const;
    void setSystemObj(const System* object);
    bool SaveDevice();
    bool UpdateDevice();

    // Q_INVOKABLE IO *pIO() const;
    Q_INVOKABLE Trend *pTrend() const;

    // Q_INVOKABLE void test();

    //获取和更新 plotIndex
    int getPlotIndex() const;
    void incrementPlotIndex();

signals:
    void notifyProductionObjChanged();
    void notifyDevInfoObjectChanged();
    void notifyManualObjChanged();
    void notifySystemObjChanged();

    void pYieldTrendChanged();

    void pTrendChanged();

private:
    int m_WelderID;
    DeviceInformation*m_ptrDevInfo;   // 设备信息
    Manual* m_ptrManual;
    Production* m_ptrProduction;
    System* m_ptrSystem;

    Trend* m_ptrTrend;
    int plotIndex;  // 每个设备独有的 plotIndex

};

#endif // DEVICE_H
