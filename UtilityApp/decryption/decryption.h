#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <QObject>
#include <QDateTime>

class Decryption : public QObject
{
    Q_OBJECT
private:
    static constexpr int DECRYPT_JSON_SIZE = 1000;
    static constexpr int DECRYPT_JSON_KEY_SIZE = 100;
    static constexpr char* DECRYPT_KEY_PATH = (char*)":/miscellaneous/developer-conf-key.enc";
    struct LICENSE_INFO
    {
        QString MachineSerialNumber;
        QDateTime CreateTime;
        QString Version;
        int MachineType;
        int ExpiredTimeType;
    };
    LICENSE_INFO m_stLicenseInfo;

private:
    bool decrypt(const QString file_path, const QString passphrase, unsigned char *output, int *output_size);
    bool validate(const QString strDecryptionJSON, QString pathconfig_A);
    bool getLicenseInfo(const QString strDecryptionJSON);
public:
    explicit Decryption(QObject *parent = nullptr);
    bool DecryptLicenseFile();

signals:
};

#endif // DECRYPTION_H
