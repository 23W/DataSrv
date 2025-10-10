#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class CCryptorStatus
{
public:
    virtual ~CCryptorStatus() {};
};

class CEncryptor
{
public:
    using TBuffer = std::vector<std::uint8_t>;
    using TStatusPtr = std::unique_ptr<CCryptorStatus>;

    virtual ~CEncryptor() {};

    virtual TStatusPtr StartEncrypt(const TBuffer& passwordHash, const TBuffer& sourceChunk, TBuffer& encodedChunk) = 0;
    virtual void NextEncrypt(const TStatusPtr& spStatus, const TBuffer& sourceChunk, TBuffer& encodedChunk) = 0;
    virtual void EndEncrypt(TStatusPtr&& spStatus, const TBuffer& sourceChunk, TBuffer& encodedChunk) = 0;
};

class CDecryptor
{
public:
    using TBuffer = std::vector<std::uint8_t>;
    using TStatusPtr = std::unique_ptr<CCryptorStatus>;

    virtual ~CDecryptor() {};

    virtual TStatusPtr StartDecrypt(const TBuffer& passwordHash, const TBuffer& encodedChunk, TBuffer& decodedChunk) = 0;
    virtual void NextDecrypt(const TStatusPtr& spStatus, const TBuffer& encodedChunk, TBuffer& decodedChunk) = 0;
    virtual void EndDecrypt(TStatusPtr&& spStatus, const TBuffer& encodedChunk, TBuffer& decodedChunk) = 0;
};

class CCryptor : public CEncryptor
               , public CDecryptor
{
public:
    using TBuffer = CEncryptor::TBuffer;
    using TStatusPtr = CEncryptor::TStatusPtr;

    virtual ~CCryptor() {};

    virtual void BuildPasswordHash(const std::string& utf8Password, const TBuffer* pSalt /*= nullptr*/, TBuffer& passwordHash) = 0;
};


class CCryptorFactorty
{
public:
    using TCryptorPtr = std::unique_ptr<CCryptor>;

    enum class CodecType
    {
        AES256CBC,
    };

    TCryptorPtr Create(CodecType codec);
};
