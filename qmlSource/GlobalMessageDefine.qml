pragma Singleton //we indicate that this QML Type is a singleton
import QtQuick 2.12
import QmlEnum 1.0
import DeviceInfoEnum 1.0
QtObject
{
    id: globalMessageDefine
    
    function getGlobalMessage(messageType, time, welderID)
    {
        var str = time + GlobalLanguageDefine.strDevice + welderID
        switch(messageType)
        {
        case QmlEnum.MESSAGE_suspicious:
            str += GlobalLanguageDefine.strSuspiciousAppeared;
            break;
        case QmlEnum.MESSAGE_defective:
            str += GlobalLanguageDefine.strDefectiveAppeared;
            break;
        case QmlEnum.MESSAGE_noConnect:
            str += GlobalLanguageDefine.strDisConnected;
            break;
        case QmlEnum.MESSAGE_lowerValue:
            str += GlobalLanguageDefine.strYieldDropToLimit;
            break;
        case QmlEnum.MESSAGE_defectiveOften:
            str += GlobalLanguageDefine.strFrequentDefective;
            break;
        case QmlEnum.MESSAGE_suspiciousOften:
            str += GlobalLanguageDefine.strFrequentSuspicious;
            break;
        case QmlEnum.MESSAGE_upperValue:
            str += GlobalLanguageDefine.strAutoLearnExceedLimit;
            break;
        //TODO definition needs to be changed
        case QmlEnum.MESSAGE_studyOver:
            str += GlobalLanguageDefine.strAutoLearnCompleted;
            break;
        //TODO Need to do a double check
        case QmlEnum.MESSAGE_touchSuccess:
            str += GlobalLanguageDefine.strModelCreationCompleted;
            break;
        case QmlEnum.MESSAGE_setupComplete:
            str += GlobalLanguageDefine.strModelCreationCompleted;
            break;
        default:
            break;
        }
        return str;
    }

    function getConnectState(state)
    {
        var strState = GlobalLanguageDefine.strDisconnected
        switch(state)
        {
        case DeviceInfoEnum.FAILED:
            strState = GlobalLanguageDefine.strConnectFailed
            break;
        case DeviceInfoEnum.DISCONNECTED:
            strState = GlobalLanguageDefine.strDisconnected
            break;
        case DeviceInfoEnum.CONNECTING:
            strState = GlobalLanguageDefine.strConnecting
            break;
        case DeviceInfoEnum.CONNECTED:
            strState = GlobalLanguageDefine.strConnected
            break;
        default:
            strState = GlobalLanguageDefine.strDisconnected
            break;
        }
        return strState
    }
}
