#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <QObject>

class Decryption : public QObject
{
    Q_OBJECT
private:
    static constexpr int DECRYPT_JSON_SIZE = 1000;
    static constexpr int DECRYPT_JSON_KEY_SIZE = 100;
    static constexpr char* DECRYPT_KEY_PATH = (char*)":/miscellaneous/developer-conf-key.enc";
private:
    int decrypt(const QString file_path, const QString passphrase, unsigned char *output, int *output_size);
public:
    explicit Decryption(QObject *parent = nullptr);
    int DecryptLicenseFile();

signals:
};

#endif // DECRYPTION_H
