#include "decryption.h"
#include <QFile>
#include <QDebug>
#include <openssl/evp.h>

Decryption::Decryption(QObject *parent)
    : QObject{parent}
{}

int Decryption::DecryptLicenseFile()
{
    int size = 0;
    QString config_A_path = ":/miscellaneous/33595419_A.out";
    QString config_B_path = ":/miscellaneous/33595419_B.out";
    unsigned char DecryptedJson[DECRYPT_JSON_SIZE] = { 0 };
    unsigned char DecryptedKeyJson[DECRYPT_JSON_KEY_SIZE] = { 0 };

}


int Decryption::decrypt(const QString file_path, const QString passphrase, unsigned char *output, int *output_size)
{
    // set default output size to zero
    *output_size = 0;

    // Try to open file for decryption
    QFile in(file_path);

    // is file opened successfully
    if (!in.open(QIODevice::ReadOnly))
    {
        qDebug() << "File Open Error";
        return -1;
    }

    // get salt from file
    unsigned char salt[8];
    unsigned char temp_buff[16];

    // read first 16 chars from file (size of salt signature is 8, and plus actual salt of 8)
    if (in.read(reinterpret_cast<char*>(temp_buff), 16) < 16)
    {
        qDebug() << "File Read Error";
        return -1;
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
            return -1;
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

        PKCS5_PBKDF2_HMAC(passphrase, -1, salt, 8, 10000, EVP_sha256(), iklen + ivlen, keyivpair);
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
            return -1;
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
            return -1;
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
        return 0;
    }
}

int LicenseProcessing::CalculateSHA512(std::string* inJsonString, std::string* outSHA512)
{
    int status = 0;
    unsigned char HashValue[SHA512_DIGEST_LENGTH];

    // Allocate an sha512_ctx
    SHA512_CTX sha512_ctx;

    // Initializes a SHA512_CTX structure
    status = SHA512_Init(&sha512_ctx);
    if (status < 0)
    {
        cout << "Failed to Initializes a SHA512_CTX" << endl;
        return -1;
    }

    // Run over the data
    status = SHA512_Update(&sha512_ctx, inJsonString->c_str(), inJsonString->size());
    if (status < 0)
    {
        cout << "Failed to update a SHA512_CTX" << endl;
        return -1;
    }

    //  Finally extract the result and erase the SHA512_CTX
    status = SHA512_Final(HashValue, &sha512_ctx);
    if (status < 0)
    {
        cout << "Failed to extract / erase a SHA512_CTX" << endl;
        return -1;
    }

    char HashHexValue[2 * SHA512_DIGEST_LENGTH + 1];

    for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i)
    {
        sprintf(HashHexValue + (i * 2), "%02x", HashValue[i]);
    }

    *outSHA512 = HashHexValue;

    return status;
}
