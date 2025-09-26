#ifndef UTILITYAPPLAUNCHER_H
#define UTILITYAPPLAUNCHER_H

#include <QObject>
#include <QProcess>

class UtilityAppLauncher : public QObject
{
    Q_OBJECT
public:
    static UtilityAppLauncher* instance();


    Q_INVOKABLE void startUtilityApp();
    Q_INVOKABLE void stopUtilityApp();

    void onProcessError(QProcess::ProcessError error);
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:

    explicit UtilityAppLauncher(QObject *parent = nullptr);
    ~UtilityAppLauncher();

    UtilityAppLauncher(const UtilityAppLauncher&) = delete;
    UtilityAppLauncher& operator=(const UtilityAppLauncher&) = delete;

    QProcess *m_process = nullptr;
};

#endif // UTILITYAPPLAUNCHER_H
