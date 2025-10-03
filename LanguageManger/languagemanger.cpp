#include "languagemanger.h"
#include <QCoreApplication>
#include <qdebug.h>
#include <QSettings>
LanguageManger::LanguageManger(QObject *parent)
    : QObject{parent}
{
    translator = new QTranslator();
    // 初始加载一个默认语言，例如英语
    QSettings configure(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    QString strLanguage = configure.value("LanguageManger/Language").toString();
    m_iLanguageIndex = -1;
    if((strLanguage == "SimplifiedChinese") || (strLanguage == "English"))
        loadLanguage(strLanguage);
    else
        loadLanguage("SimplifiedChinese");
}
void LanguageManger::loadLanguage(const QString &languageCode)
{
    // 如果之前已经加载了翻译器，则先移除
    qApp->removeTranslator(translator);
    translator->load(QString(":/languagePackages/%1.qm").arg(languageCode));
    qApp->installTranslator(translator);

    QSettings set(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    set.setValue("LanguageManger/Language",languageCode);

    if(languageCode == "SimplifiedChinese")
        setLanguageIndex(LanguageEnum::SIMPLIFIED_CHINESE);
    else if(languageCode == "English")
        setLanguageIndex(LanguageEnum::ENGLISH);
    else
        setLanguageIndex(LanguageEnum::SIMPLIFIED_CHINESE);
}

int LanguageManger::getLanguageIndex() const
{
    return m_iLanguageIndex;
}

void LanguageManger::setLanguageIndex(int languageIndex)
{
    if (m_iLanguageIndex == languageIndex)
        return;
    m_iLanguageIndex = languageIndex;
    emit notifyLanguageIndexChanged();
}
