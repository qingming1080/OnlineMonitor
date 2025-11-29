#include "languageManager.h"
#include <QCoreApplication>
#include <qdebug.h>
#include <QSettings>
LanguageManager::LanguageManager(QObject *parent)
    : QObject{parent}
{
    translator = new QTranslator();
    // 初始加载一个默认语言，例如英语
    QSettings configure(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    QString strLanguage = configure.value("LanguageManager/Language").toString();
    m_iLanguageIndex = -1;
    if((strLanguage == "SimplifiedChinese") || (strLanguage == "English"))
        loadLanguage(strLanguage);
    else
        loadLanguage("SimplifiedChinese");
}
void LanguageManager::loadLanguage(const QString &languageCode)
{
    // 如果之前已经加载了翻译器，则先移除
    qApp->removeTranslator(translator);
    translator->load(QString(":/languageTranslation/%1.qm").arg(languageCode));
    qApp->installTranslator(translator);

    QSettings set(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    set.setValue("LanguageManager/Language",languageCode);

    if(languageCode == "SimplifiedChinese")
        setLanguageIndex(LanguageEnum::SIMPLIFIED_CHINESE);
    else if(languageCode == "English")
        setLanguageIndex(LanguageEnum::ENGLISH);
    else
        setLanguageIndex(LanguageEnum::SIMPLIFIED_CHINESE);
}

int LanguageManager::getLanguageIndex() const
{
    return m_iLanguageIndex;
}

void LanguageManager::setLanguageIndex(int languageIndex)
{
    if (m_iLanguageIndex == languageIndex)
        return;
    m_iLanguageIndex = languageIndex;
    emit notifyLanguageIndexChanged();
}
