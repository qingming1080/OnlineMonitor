#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <QObject>
#include <QTranslator>

class LanguageEnum : public QObject
{
    Q_OBJECT
public:
    enum LANGUAGE_INDEX
    {
        SIMPLIFIED_CHINESE = 0,
        ENGLISH
    };
    Q_ENUM(LANGUAGE_INDEX)

public:
    explicit LanguageEnum(QObject *parent = nullptr){}
};

class LanguageManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int LanguageIndex READ getLanguageIndex WRITE setLanguageIndex NOTIFY notifyLanguageIndexChanged FINAL)
public:
    explicit LanguageManager(QObject *parent = nullptr);
    Q_INVOKABLE void loadLanguage(const QString &languageCode);

    int getLanguageIndex() const;
    void setLanguageIndex(int languageIndex);
private:
    QTranslator *translator;
signals:
    void notifyLanguageIndexChanged();
private:
    int m_iLanguageIndex;
};
#endif // LANGUAGEMANAGER_H
