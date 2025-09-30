#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <QObject>
#include <QTranslator>


class LanguageManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged FINAL)
public:
    explicit LanguageManager(QObject *parent = nullptr);

    Q_INVOKABLE void loadLanguage(const QString &languageCode);

    Q_INVOKABLE QString language() const;
    Q_INVOKABLE void setLanguage(const QString &newLanguage);

signals:

    void languageChanged();

    void translationsReloaded();

private:

    QString m_language;

    QTranslator *m_translator;

};


#endif // LANGUAGEMANGER_H
