#include "utilityapplauncher.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QThread>

UtilityAppLauncher* UtilityAppLauncher::getInstance()
{
    static UtilityAppLauncher s_instance;
    return &s_instance;
}

UtilityAppLauncher::UtilityAppLauncher(QObject *parent)
    : QObject(parent)
{
    m_process = new QProcess(this);
    // connect(m_process, QOverload<QProcess::ProcessError>::of(&QProcess::errorOccurred),this, &UtilityAppLauncher::onProcessError);

    // connect(m_process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),this, &UtilityAppLauncher::onProcessFinished);

}


void UtilityAppLauncher::onProcessError(QProcess::ProcessError error)
{
#ifdef RASPBERRY
    qWarning() << "UtilityApp 进程异常，错误类型:" << error << ", errorString:" << m_process->errorString();
    qWarning() << "UtilityApp 标准输出:\n" << m_process->readAllStandardOutput();
    qWarning() << "UtilityApp 标准错误:\n" << m_process->readAllStandardError();
    QTimer::singleShot(2000, this, [this](){ startUtilityApp(); });
#else
    Q_UNUSED(error)
#endif
}

void UtilityAppLauncher::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
#ifdef RASPBERRY
    qWarning() << "UtilityApp 进程退出，exitCode:" << exitCode << ", exitStatus:" << exitStatus;
    qWarning() << "UtilityApp 标准输出:\n" << m_process->readAllStandardOutput();
    qWarning() << "UtilityApp 标准错误:\n" << m_process->readAllStandardError();
    QTimer::singleShot(2000, this, [this](){ startUtilityApp(); });
#else
    Q_UNUSED(exitCode)
    Q_UNUSED(exitStatus)
#endif
}

UtilityAppLauncher::~UtilityAppLauncher()
{
    if (m_process->state() != QProcess::NotRunning) {
        m_process->terminate();
        m_process->waitForFinished(2000);
    }
}

bool UtilityAppLauncher::isUtilityAppRunning() const
{
#ifdef RASPBERRY
    QProcess checker;
    checker.start("pgrep", {"-f", "/opt/UtilityApp/bin/UtilityApp"});
    if (!checker.waitForFinished(2000)) {
        qWarning() << "UtilityApp check failed:" << checker.errorString();
        return false;
    }

    const QString output = QString::fromLocal8Bit(checker.readAllStandardOutput()).trimmed();
    return !output.isEmpty();
#else
    return false;
#endif
}

void UtilityAppLauncher::killUtilityApp()
{
#ifdef RASPBERRY
    QProcess killer;
    killer.start("pkill", {"-f", "/opt/UtilityApp/bin/UtilityApp"});
    if (!killer.waitForFinished(2000)) {
        qWarning() << "UtilityApp kill failed:" << killer.errorString();
    } else {
        qDebug() << "UtilityApp killed";
    }
#endif
}

void UtilityAppLauncher::startUtilityApp()
{
#ifdef RASPBERRY
    bool isFirstRun = !isUtilityAppRunning();

    if (!isFirstRun) {
        qDebug() << "UtilityApp is already running; killing existing process.";
        killUtilityApp();
        // Give it a moment to fully terminate
        QThread::msleep(500);
    }

    // 仅在树莓派（Linux）下运行指定路径
    QString program = "sudo";
    QStringList arguments;
    arguments.append("/opt/UtilityApp/bin/UtilityApp");
    // arguments.append("-platform");
    // arguments.append("xcb");

    if (m_process->state() == QProcess::NotRunning) {
        m_process->start(program, arguments);
        if (!m_process->waitForStarted(5000)) {
            qWarning() << "UtilityApp launching failure" << m_process->errorString();
        } else {
            qDebug() << "UtilityApp launched";
            // Give more time for first run after boot
            int delayMs = isFirstRun ? 15000 : 10000;
            qDebug() << "Waiting" << delayMs << "ms for UtilityApp initialization";
            QTimer::singleShot(delayMs, this, [this]() {
                emit utilityAppReady();
            });
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
