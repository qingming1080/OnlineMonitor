#include "signalmanager.h"

SignalManager* SignalManager::s_pSignalManager = nullptr;

SignalManager *SignalManager::getInstance()
{
    if(s_pSignalManager == nullptr)
        s_pSignalManager = new SignalManager();

    return s_pSignalManager;
}

SignalManager::SignalManager(QObject *parent)
    : QObject{parent}
{

}
