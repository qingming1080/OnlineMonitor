#ifndef UTILITYAPPLAUNCHER_H
#define UTILITYAPPLAUNCHER_H

#include <QObject>
#include <QProcess>

class UtilityAppLauncher : public QObject
{
    Q_OBJECT
public:
    static UtilityAppLauncher* getInstance();


    Q_INVOKABLE void startUtilityApp();
    Q_INVOKABLE void stopUtilityApp();

    bool isUtilityAppRunning() const;
    void killUtilityApp();

    void onProcessError(QProcess::ProcessError error);
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

signals:
    void utilityAppReady();

private:

    explicit UtilityAppLauncher(QObject *parent = nullptr);
    ~UtilityAppLauncher();

    UtilityAppLauncher(const UtilityAppLauncher&) = delete;
    UtilityAppLauncher& operator=(const UtilityAppLauncher&) = delete;

    QProcess *m_process = nullptr;
};

#endif // UTILITYAPPLAUNCHER_H
