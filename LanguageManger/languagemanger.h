#ifndef LANGUAGEMANGER_H
#define LANGUAGEMANGER_H

#include <QObject>
#include <QTranslator>


class LanguageManger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged FINAL)
public:
    explicit LanguageManger(QObject *parent = nullptr);

    Q_INVOKABLE void loadLanguage(const QString &languageCode);

    Q_INVOKABLE QString language() const;
    Q_INVOKABLE void setLanguage(const QString &newLanguage);

private:
    QTranslator *translator;

signals:
    void updata();

    void languageChanged();

private:
    QString m_language;

};


#endif // LANGUAGEMANGER_H
