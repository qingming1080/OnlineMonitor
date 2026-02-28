#include "decryption.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <openssl/evp.h>
#include <openssl/sha.h>

Decryption::Decryption(QObject *parent)
    : QObject{parent}
{
    if(getRaspberryPiSerialNumber().length() > 8)
    {
        m_strActualSN = getRaspberryPiSerialNumber().right(8);
    }
    else
    {
        m_strActualSN = "Unknown";
    }
    // qDebug() << "SN: " << m_strActualSN;
}

bool Decryption::DecryptLicenseFile()
{
    int size = 0;
    QString config_A_path = QString("/opt/%1_A.out").arg(m_strActualSN);
    QString config_B_path = QString("/opt/%1_B.out").arg(m_strActualSN);
    unsigned char DecryptedJson[DECRYPT_JSON_SIZE] = { 0 };
    unsigned char DecryptedKeyJson[DECRYPT_JSON_KEY_SIZE] = { 0 };
    decrypt(DECRYPT_KEY_PATH, "BransonTopSecret@1234#", DecryptedKeyJson, &size);
    // qDebug() << "DecryptedKeyJson: " << QString::fromUtf8(reinterpret_cast<char*>(DecryptedKeyJson), size);
    bool bResult = decrypt(config_B_path, (char*)DecryptedKeyJson, DecryptedJson, &size);
    if(bResult == true)
    {
        const QString strDecryptionJson = QString::fromUtf8(reinterpret_cast<char*>(DecryptedJson), size);
        // qDebug() << "DecryptedJson: " << strDecryptionJson;
        bResult = validate(strDecryptionJson, config_A_path);
        if (!bResult)
        {
            qDebug() << "Failed to parse license information";
            return false;
        }
    }
    return bResult;
}


bool Decryption::decrypt(const QString file_path, const QString passphrase, unsigned char *output, int *output_size)
{
    // set default output size to zero
    *output_size = 0;

    // Try to open file for decryption
    QFile in(file_path);

    // is file opened successfully
    if (!in.open(QIODevice::ReadOnly))
    {
        qDebug() << "File Open Error";
        return false;
    }

    // get salt from file
    unsigned char salt[8];
    unsigned char temp_buff[16];

    // read first 16 chars from file (size of salt signature is 8, and plus actual salt of 8)
    if (in.read(reinterpret_cast<char*>(temp_buff), 16) < 16)
    {
        qDebug() << "File Read Error";
        return false;
    }
    else
    {
        // check if salt present in file
        if (memcmp(temp_buff, "Salted__", 8) == 0)
        {
            //copy salt
            memcpy(salt, temp_buff + 8, 8);
        }
        else
        {
            qDebug() << "No salt in file";
            return false;
        }

        // get key & IV pair
        const EVP_CIPHER* cipher = EVP_aes_256_cbc();
        int iklen = EVP_CIPHER_key_length(cipher);
        int ivlen = EVP_CIPHER_iv_length(cipher);
        int blocksize = EVP_CIPHER_block_size(cipher);
        unsigned char* key = reinterpret_cast<unsigned char*>(malloc(iklen));
        unsigned char* iv = reinterpret_cast<unsigned char*>(malloc(ivlen));
        unsigned char* keyivpair = reinterpret_cast<unsigned char*>(malloc(iklen + ivlen));
        unsigned char* decrypt_buff = reinterpret_cast<unsigned char*>(malloc(blocksize * 2));
        unsigned char* inbuff = reinterpret_cast<unsigned char*>(malloc(blocksize));
        int output_size_local = 0;

        QByteArray byteArray = passphrase.toUtf8();
        const char* _strPassphrase = byteArray.constData();
        PKCS5_PBKDF2_HMAC(_strPassphrase, -1, salt, 8, 10000, EVP_sha256(), iklen + ivlen, keyivpair);
        memcpy(key, keyivpair, iklen);
        memcpy(iv, keyivpair + iklen, ivlen);

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

        // setup decryption parameters
        if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        {
            free(key);
            free(iv);
            free(keyivpair);
            free(decrypt_buff);
            free(inbuff);
            qDebug() << "Decrypt init failed";
            return false;
        }

        int inlen, outlen;
        // read from file
        while ((inlen = static_cast<int>(in.read(reinterpret_cast<char*>(inbuff), blocksize))) > 0)
        {
            // decrypt the read data block
            if (!EVP_DecryptUpdate(ctx, decrypt_buff, &outlen, inbuff, inlen))
            {
                free(key);
                free(iv);
                free(keyivpair);
                free(decrypt_buff);
                free(inbuff);
                qDebug() << "Decrypt update failed";
                return -1;
            }
            memcpy(output, decrypt_buff, outlen);
            output = output + outlen;
            output_size_local = output_size_local + outlen;
        }
        // finalize the decryption
        if (!EVP_DecryptFinal_ex(ctx, output, &outlen))
        {
            free(key);
            free(iv);
            free(keyivpair);
            free(decrypt_buff);
            free(inbuff);
            qDebug() << "Decrypt final failed";
            return false;
        }
        else
        {
            output_size_local = output_size_local + outlen;
        }

        // update the output size
        (*output_size) = output_size_local;

        free(key);
        free(iv);
        free(keyivpair);
        free(decrypt_buff);
        free(inbuff);
        return true;
    }
}

bool Decryption::calculateSHA512(const QString inJsonString, QString& outSHA512)
{
    int status = 0;
    unsigned char HashValue[SHA512_DIGEST_LENGTH];

    // Allocate an sha512_ctx
    SHA512_CTX sha512_ctx;

    // Initializes a SHA512_CTX structure
    status = SHA512_Init(&sha512_ctx);
    if (status < 0)
    {
        qDebug() << "Failed to Initializes a SHA512_CTX";
        return false;
    }

    // Run over the data
    QByteArray byteArray = inJsonString.toUtf8();
    const char* _JsonString= byteArray.constData();
    status = SHA512_Update(&sha512_ctx, _JsonString, inJsonString.size());
    if (status < 0)
    {
        qDebug() << "Failed to update a SHA512_CTX";
        return false;
    }

    //  Finally extract the result and erase the SHA512_CTX
    status = SHA512_Final(HashValue, &sha512_ctx);
    if (status < 0)
    {
        qDebug() << "Failed to extract / erase a SHA512_CTX";
        return false;
    }

    char HashHexValue[2 * SHA512_DIGEST_LENGTH + 1];

    for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i)
    {
        sprintf(HashHexValue + (i * 2), "%02x", HashValue[i]);
    }

    outSHA512 = QString(HashHexValue);

    return true;
}

bool Decryption::getLicenseInfo(const QString strDecryptionJSON)
{
    QJsonParseError parseError;
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(strDecryptionJSON.toUtf8(), &parseError);
    if (parseError.error != QJsonParseError::NoError || !jsonDoc.isObject())
    {
        qDebug() << "License JSON parse failed:" << parseError.errorString();
        return false;
    }

    const QJsonObject jsonObject = jsonDoc.object();

    m_stLicenseInfo.MachineSerialNumber = jsonObject.value("Machine Serial Number").toString();
    m_stLicenseInfo.CreateTime = QDateTime::fromString(
        jsonObject.value("Date Time").toString(),
        "yyyy-MM-dd HH:mm:ss");
    m_stLicenseInfo.Version = jsonObject.value("Version").toString();
    m_stLicenseInfo.MachineType = jsonObject.value("Welder Model").toInt(-1);
    m_stLicenseInfo.ExpiredTimeType = jsonObject.value("Expire Time").toInt(-1);

    if (m_stLicenseInfo.MachineSerialNumber.isEmpty() ||
        !m_stLicenseInfo.CreateTime.isValid() ||
        m_stLicenseInfo.Version.isEmpty() ||
        m_stLicenseInfo.MachineType < 0 ||
        m_stLicenseInfo.ExpiredTimeType < 0)
    {
        qDebug() << "License JSON missing required fields";
        return false;
    }

    // qDebug() << "LicenseInfo parsed:" << m_stLicenseInfo.MachineSerialNumber
    //          << m_stLicenseInfo.CreateTime.toString("yyyy-MM-dd HH:mm:ss")
    //          << m_stLicenseInfo.Version
    //          << m_stLicenseInfo.MachineType
    //          << m_stLicenseInfo.ExpiredTimeType;
    return true;
}

bool Decryption::validate(const QString strDecryptionJSON, QString pathconfig_A)
{
    QFile hashFile(pathconfig_A);
    if (!hashFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open the hash file";
        return false;
    }

    QString strConfigHash = QString::fromUtf8(hashFile.readAll());
    // qDebug() << "strConfigHash: " << strConfigHash;
    hashFile.close();
    
    QString strCalculatedHash;
    // Calculate the SHA-512 hash of the JSON content
    if(calculateSHA512(strDecryptionJSON, strCalculatedHash) == false)
        return false;
    // qDebug() << "strCalculatedHash: " << strCalculatedHash;

    if(strConfigHash != strCalculatedHash)
    {
        qDebug() << "Hash verification failed.";
        return false;
    }

    qDebug() << "Hash verification successful.";

    if(getLicenseInfo(strDecryptionJSON) == false)
        qDebug() << "License Info Getting failed.";

    bool bResult = false;
    if(m_stLicenseInfo.MachineSerialNumber == m_strActualSN)
    {
        bResult = true;
    }
    qDebug() << "ActualSN: " << m_strActualSN;
    return bResult;
}

QString Decryption::getRaspberryPiSerialNumber()
{
    QFile cpuinfo("/proc/cpuinfo");
    if (!cpuinfo.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open cpuinfo";
        return "";
    }
    
    QString content = cpuinfo.readAll();
    cpuinfo.close();
    
    QStringList lines = content.split('\n');
    for (const QString& line : lines)
    {
        if (line.startsWith("Serial"))
        {
            return line.split(':').last().trimmed();
        }
    }
    
    return "";
}
