#include "datavalidator.h"
#include "modbus/hbmodbusclient.h"

DataValidator::DataValidator(QObject *parent)
    : QObject{parent}
{}

bool DataValidator::isValidForDatabase(const QVector<quint16> &inputs)

{
        if (inputs.size() < 10) return false; // 假设至少有10个寄存器

        if (inputs[HBModbusClient::DEV_ENERGY] < MIN_ENERGY             || inputs[HBModbusClient::DEV_ENERGY] > MAX_ENERGY)     return false;
        if (inputs[HBModbusClient::DEV_AMPLITUDE] < MIN_AMPLITUDE       || inputs[HBModbusClient::DEV_AMPLITUDE] > MAX_AMPLITUDE)  return false;
        if (inputs[HBModbusClient::DEV_TP] < MIN_TP                     || inputs[HBModbusClient::DEV_TP] > MAX_TP)         return false;
        if (inputs[HBModbusClient::DEV_WP] < MIN_WP                     || inputs[HBModbusClient::DEV_WP] > MAX_WP)         return false;
        if (inputs[HBModbusClient::DEV_TIME] < MIN_TIME                 || inputs[HBModbusClient::DEV_TIME] > MAX_TIME)       return false;
        if (inputs[HBModbusClient::DEV_POWER] < MIN_POWER               || inputs[HBModbusClient::DEV_POWER] > MAX_POWER)      return false;
        if (inputs[HBModbusClient::DEV_PRE_HEIGHT] < MIN_PREHEIGHT      || inputs[HBModbusClient::DEV_PRE_HEIGHT] > MAX_PREHEIGHT)  return false;
        if (inputs[HBModbusClient::DEV_POST_HEIGHT] < MIN_POSTHEIGHT    || inputs[HBModbusClient::DEV_POST_HEIGHT] > MAX_POSTHEIGHT) return false;

        return true;

}


void DataValidator::sanitizeInputs(QVector<quint16> &inputs, quint16 maxValue) {
    for (int i = 0; i < inputs.size(); ++i)
    {
        inputs[i] = sanitizeValue(inputs[i], maxValue);
    }
}

quint16 DataValidator::sanitizeValue(quint16 value, quint16 maxValue) {
    return (value <= maxValue) ? value : 0;
}

