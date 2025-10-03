#include "languageManager.h"
#include <QCoreApplication>
#include <qdebug.h>
#include <QSettings>

LanguageManager::LanguageManager(QObject *parent)
    : QObject{parent}, m_translator(new QTranslator(this))
{

    QSettings set(QCoreApplication::applicationDirPath() + "/config.ini",QSettings::IniFormat);

    QString Language = set.value("LanguageManger/Language").toString();
    loadLanguage(Language);

}
void LanguageManager::loadLanguage(const QString &languageCode)
{
    setLanguage(languageCode);
    QSettings set(QCoreApplication::applicationDirPath() + "/config.ini",QSettings::IniFormat);

    qApp->removeTranslator(m_translator);

    const QString qmFile = QString(":/languageTranslation/%1.qm").arg(languageCode);

    if (m_translator->load(qmFile)) {
        qApp->installTranslator(m_translator);
        qDebug() << "Loaded translation:" << qmFile;
    } else {
        qDebug() << "Failed to load translation:" << qmFile;
    }

    emit translationsReloaded();
}

QString LanguageManager::language() const
{
    return m_language;
}

void LanguageManager::setLanguage(const QString &newLanguage)
{
    if (m_language == newLanguage)
        return;
    m_language = newLanguage;
    emit languageChanged();
}
