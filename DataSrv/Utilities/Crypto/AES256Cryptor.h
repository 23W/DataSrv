#pragma once

#include <array>
#include <vector>
#include <bcrypt.h>

#include "Cryptor.h"

class CAES256Cryptor : public CCryptor
{
public:
    using TBase = CCryptor;

    // Constructiom

    CAES256Cryptor();
    ~CAES256Cryptor() override;

    // Methods

    void BuildPasswordHash(const std::string& utf8Password, const TBuffer* pSalt /*= nullptr*/, TBuffer& passwordHash) override;

    TStatusPtr StartEncrypt(const TBuffer& passwordHash, const TBuffer& sourceChunk, TBuffer& encodedChunk) override;
    void NextEncrypt(const TStatusPtr& spStatus, const TBuffer& sourceChunk, TBuffer& encodedChunk) override;
    void EndEncrypt(TStatusPtr&& spStatus, const TBuffer& sourceChunk, TBuffer& encodedChunk) override;

    TStatusPtr StartDecrypt(const TBuffer& passwordHash, const TBuffer& encodedChunk, TBuffer& decodedChunk) override;
    void NextDecrypt(const TStatusPtr& spStatus, const TBuffer& encodedChunk, TBuffer& decodedChunk) override;
    void EndDecrypt(TStatusPtr&& spStatus, const TBuffer& encodedChunk, TBuffer& decodedChunk) override;

public:

    // Constants

    constexpr static const unsigned int c_algBitness = 256;
    constexpr static const unsigned int c_hashSize = c_algBitness / 8;
    constexpr static const unsigned int c_blockSize = 16;
    constexpr static const unsigned int c_hashIterations = 10000;

    constexpr static const auto c_defaultSalt = std::to_array<TBuffer::value_type>({ 23, 12, 19, 76, 76, 19 ,12, 23,
                                                                                     19, 04, 19, 77, 77, 19 ,04, 19 });

    constexpr static const char* c_errorNotInited = "AES chiper was not initialized";
    constexpr static const char* c_errorHash = "Can not generate PBKDF2 hash";
    constexpr static const char* c_errorStatus = "Can not init status";
    constexpr static const char* c_errorEncrypt = "Can not encrypt";
    constexpr static const char* c_errorDecrypt = "Can not decrypt";
    constexpr static const char* c_errorSmallChunk = "Chunk smaller than block";

private:

    // Nested classes

    class CStatus : public CCryptorStatus
    {
    public:

        std::vector<std::uint8_t> Iv;
        std::vector<std::uint8_t> KeyObject;
        BCRYPT_KEY_HANDLE Key = NULL;

        CStatus() = delete;
        CStatus(BCRYPT_ALG_HANDLE hAlg, BCRYPT_ALG_HANDLE hRndAlg, const TBuffer& passwordHash);
        virtual ~CStatus();
    };

    // Helper Methods

    bool IsValid() const { return m_hAlg != NULL; }

    void AppendEncrypt(CStatus* pStatus, const TBuffer::value_type* pSourceChunk, size_t sourceChunkSize, TBuffer& appendChunk, bool lastChunk);
    void AppendDecrypt(CStatus* pStatus, const TBuffer::value_type* pEncodedChunk, size_t encodedChunkSize, TBuffer& appendChunk, bool lastChunk);

    // Members

    BCRYPT_ALG_HANDLE m_hAlg;
    BCRYPT_ALG_HANDLE m_hRndAlg;
};
