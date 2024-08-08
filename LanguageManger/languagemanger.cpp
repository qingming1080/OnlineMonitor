#include "languagemanger.h"
#include <QCoreApplication>
#include <qdebug.h>
#include <QSettings>
LanguageManger::LanguageManger(QObject *parent)
    : QObject{parent}
{
    translator = new QTranslator();
    // 初始加载一个默认语言，例如英语
    QSettings set(QCoreApplication::applicationDirPath() + "/config.ini",QSettings::IniFormat);

    QString Language = set.value("LanguageManger/Language").toString();
    loadLanguage(Language);
    // loadLanguage("SimplifiedChinese");
    //    loadLanguage("English");
}
void LanguageManger::loadLanguage(const QString &languageCode)
{
    setLanguage(languageCode);
    QSettings set(QCoreApplication::applicationDirPath() + "/config.ini",QSettings::IniFormat);
    set.setValue("LanguageManger/Language",languageCode);
    if (qApp->removeTranslator(translator)) {
        // 如果之前已经加载了翻译器，则先移除
        qDebug() << QString(":/translations/%1.qm").arg(languageCode);
        translator->load(QString(":/translations/%1.qm").arg(languageCode));
        //        translator.load("D:/OnlineMonitor/translations");
        qApp->installTranslator(translator);
    } else {
        // 否则直接加载
        translator->load(QString(":/translations/%1.qm").arg(languageCode));
        qApp->installTranslator(translator);
    }
    emit updata();
}

QString LanguageManger::language() const
{
    return m_language;
}

void LanguageManger::setLanguage(const QString &newLanguage)
{
    if (m_language == newLanguage)
        return;
    m_language = newLanguage;
    emit languageChanged();
}
