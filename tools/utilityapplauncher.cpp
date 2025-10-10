#include "utilityapplauncher.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

UtilityAppLauncher* UtilityAppLauncher::getInstance()
{
    static UtilityAppLauncher s_instance;
    return &s_instance;
}

UtilityAppLauncher::UtilityAppLauncher(QObject *parent)
    : QObject(parent)
{
    m_process = new QProcess(this);
    connect(m_process, QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),this, &UtilityAppLauncher::onProcessError);

    connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),this, &UtilityAppLauncher::onProcessFinished);

}


void UtilityAppLauncher::onProcessError(QProcess::ProcessError error)
{
#ifdef RASPBERRY
    qWarning() << "UtilityApp 进程异常，错误类型:" << error << ", errorString:" << m_process->errorString();
    qWarning() << "UtilityApp 标准输出:\n" << m_process->readAllStandardOutput();
    qWarning() << "UtilityApp 标准错误:\n" << m_process->readAllStandardError();
    QTimer::singleShot(2000, this, [this](){ startUtilityApp(); });
#endif
}

void UtilityAppLauncher::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
#ifdef RASPBERRY
    qWarning() << "UtilityApp 进程退出，exitCode:" << exitCode << ", exitStatus:" << exitStatus;
    qWarning() << "UtilityApp 标准输出:\n" << m_process->readAllStandardOutput();
    qWarning() << "UtilityApp 标准错误:\n" << m_process->readAllStandardError();
    QTimer::singleShot(2000, this, [this](){ startUtilityApp(); });
#endif
}

UtilityAppLauncher::~UtilityAppLauncher()
{
    if (m_process->state() != QProcess::NotRunning) {
        m_process->terminate();
        m_process->waitForFinished(2000);
    }
}

void UtilityAppLauncher::startUtilityApp()
{
#ifdef RASPBERRY
    // // 仅在树莓派（Linux）下运行指定路径
    QString program = "sudo /opt/UtilityApp/bin/UtilityApp -platform xbc";
    if (m_process->state() == QProcess::NotRunning) {
        // m_process->start("sudo",{program,"-platform","xbc"});
        m_process->start(program);
        if (!m_process->waitForStarted(2000)) {
            qWarning() << "UtilityApp 启动失败:" << m_process->errorString();
        } else {
            qDebug() << "UtilityApp 已启动";
        }
    }
#endif
}

void UtilityAppLauncher::stopUtilityApp()
{
    if (m_process->state() != QProcess::NotRunning) {
        m_process->terminate();
        m_process->waitForFinished(2000);
        qDebug() << "UtilityApp 已关闭";
    }
}
