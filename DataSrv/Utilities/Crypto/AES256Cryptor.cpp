#include "pch.h"
#include <cassert>
#include <cstring>

#include "status_error.h"
#include "AES256Cryptor.h"

#pragma comment(lib, "Bcrypt.lib")

// CAES256Cryptor::CStatus

CAES256Cryptor::CStatus::CStatus(BCRYPT_ALG_HANDLE hAlg, BCRYPT_ALG_HANDLE hRndAlg, const TBuffer& passwordHash)
{
    assert(hAlg != NULL &&
           hRndAlg != NULL);
    static_assert(sizeof(UCHAR) == sizeof(TBuffer::value_type), "UCHAR must be equal with uint8_t");

    ULONG objectSize = 0, blockSize = 0, resSize = 0;

    auto res = BCryptGetProperty(hAlg, BCRYPT_OBJECT_LENGTH, reinterpret_cast<PUCHAR>(&objectSize), sizeof(objectSize), &resSize, 0);
    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorStatus);
    }

    res = BCryptGetProperty(hAlg, BCRYPT_BLOCK_LENGTH, reinterpret_cast<PUCHAR>(&blockSize), sizeof(blockSize), &resSize, 0);
    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorStatus);
    }

    Iv.resize(blockSize);
    KeyObject.resize(objectSize);

    res = BCryptGenRandom(hRndAlg,
                          static_cast<PUCHAR>(Iv.data()),
                          static_cast<ULONG>(Iv.size()),
                          0);
    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorStatus);
    }

    res = BCryptGenerateSymmetricKey(hAlg, &Key,
                                     static_cast<PUCHAR>(KeyObject.data()),
                                     static_cast<ULONG>(KeyObject.size()),
                                     static_cast<PUCHAR>(const_cast<TBuffer::value_type*>(passwordHash.data())),
                                     static_cast<ULONG>(passwordHash.size()), 0);
    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorStatus);
    }
}

CAES256Cryptor::CStatus::~CStatus()
{
    if (Key != NULL)
    {
        BCryptDestroyKey(Key);
        Key = NULL;
    }
}

// CAES256Cryptor

CAES256Cryptor::CAES256Cryptor()
    : m_hAlg(NULL)
{
    auto res = BCryptOpenAlgorithmProvider(&m_hAlg, BCRYPT_AES_ALGORITHM, nullptr, 0);
    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorNotInited);
    }

    res = BCryptSetProperty(m_hAlg, BCRYPT_CHAINING_MODE,
                            reinterpret_cast<PUCHAR>(const_cast<wchar_t*>(BCRYPT_CHAIN_MODE_CBC)),
                            sizeof(BCRYPT_CHAIN_MODE_CBC), 0);
    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorNotInited);
    }

    res = BCryptOpenAlgorithmProvider(&m_hRndAlg, BCRYPT_RNG_ALGORITHM, nullptr, 0);
    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorNotInited);
    }
}

CAES256Cryptor::~CAES256Cryptor()
{
    if (m_hAlg != NULL)
    {
        BCryptCloseAlgorithmProvider(m_hAlg, 0);
        m_hAlg = NULL;
    }

    if (m_hRndAlg != NULL)
    {
        BCryptCloseAlgorithmProvider(m_hRndAlg, 0);
        m_hRndAlg = NULL;
    }
}

void CAES256Cryptor::BuildPasswordHash(const std::string& utf8Password, const TBuffer* pSalt, TBuffer& passwordHash)
{
    static_assert(sizeof(UCHAR) == sizeof(TBuffer::value_type), "UCHAR must be equal with uint8_t");
    static_assert(sizeof(UCHAR) == sizeof(std::string::value_type), "UCHAR must be equal with char");

    const auto pSaltData = pSalt != nullptr ? pSalt->data() : c_defaultSalt.data();
    const auto saltSize = pSalt != nullptr ? pSalt->size() : c_defaultSalt.size();

    passwordHash.resize(c_hashSize);

    auto hHashAlg = BCRYPT_ALG_HANDLE(NULL);
    auto res = BCryptOpenAlgorithmProvider(&hHashAlg, BCRYPT_SHA256_ALGORITHM, nullptr, BCRYPT_ALG_HANDLE_HMAC_FLAG);
    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorNotInited);
    }

    res = BCryptDeriveKeyPBKDF2(hHashAlg,
                                reinterpret_cast<PUCHAR>(const_cast<char*>(utf8Password.data())),
                                static_cast<ULONG>(utf8Password.size()),
                                static_cast<PUCHAR>(const_cast<TBuffer::value_type*>(pSaltData)),
                                static_cast<ULONG>(saltSize),
                                c_hashIterations,
                                passwordHash.data(),
                                static_cast<ULONG>(passwordHash.size()),
                                0);

    BCryptCloseAlgorithmProvider(hHashAlg, 0);

    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorHash);
    }
}

CAES256Cryptor::TStatusPtr CAES256Cryptor::StartEncrypt(const TBuffer& passwordHash, const TBuffer& sourceChunk, TBuffer& encodedChunk)
{
    if (!IsValid())
    {
        throw std::logic_error(c_errorNotInited);
    }

    auto spStatus = std::make_unique<CStatus>(m_hAlg, m_hRndAlg, passwordHash);

    const auto offset = encodedChunk.size();
    encodedChunk.resize(offset + spStatus->Iv.size());
    std::memcpy(encodedChunk.data() + offset, spStatus->Iv.data(), spStatus->Iv.size());

    AppendEncrypt(spStatus.get(), sourceChunk.data(), sourceChunk.size(), encodedChunk, false);

    return spStatus;
}

void CAES256Cryptor::NextEncrypt(const TStatusPtr& spStatus, const TBuffer& sourceChunk, TBuffer& encodedChunk)
{
    const auto pStatus = dynamic_cast<CStatus*>(spStatus.get());

    if (!IsValid() ||
         pStatus == nullptr)
    {
        throw std::logic_error(c_errorEncrypt);
    }

    AppendEncrypt(pStatus, sourceChunk.data(), sourceChunk.size(), encodedChunk, false);
}

void CAES256Cryptor::EndEncrypt(TStatusPtr&& spStatus, const TBuffer& sourceChunk, TBuffer& encodedChunk)
{
    const auto pStatus = dynamic_cast<CStatus*>(spStatus.get());

    if (!IsValid() ||
        pStatus == nullptr)
    {
        throw std::logic_error(c_errorEncrypt);
    }

    AppendEncrypt(pStatus, sourceChunk.data(), sourceChunk.size(), encodedChunk, true);
}

CAES256Cryptor::TStatusPtr CAES256Cryptor::StartDecrypt(const TBuffer& passwordHash, const TBuffer& encodedChunk, TBuffer& decodedChunk)
{
    if (!IsValid())
    {
        throw std::logic_error(c_errorNotInited);
    }

    auto spStatus = std::make_unique<CStatus>(m_hAlg, m_hRndAlg, passwordHash);

    const auto ivSize = spStatus->Iv.size();
    if (encodedChunk.size() < ivSize)
    {
        throw std::logic_error(c_errorSmallChunk);
    }

    std::memcpy(spStatus->Iv.data(), encodedChunk.data(), ivSize);
    AppendDecrypt(spStatus.get(), encodedChunk.data() + ivSize, encodedChunk.size() - ivSize, decodedChunk, false);

    return spStatus;
}

void CAES256Cryptor::NextDecrypt(const TStatusPtr& spStatus, const TBuffer& encodedChunk, TBuffer& decodedChunk)
{
    const auto pStatus = dynamic_cast<CStatus*>(spStatus.get());

    if (!IsValid() ||
        pStatus == nullptr)
    {
        throw std::logic_error(c_errorDecrypt);
    }

    if (encodedChunk.size() < pStatus->Iv.size())
    {
        throw std::logic_error(c_errorSmallChunk);
    }

    AppendDecrypt(pStatus, encodedChunk.data(), encodedChunk.size(), decodedChunk, false);
}

void CAES256Cryptor::EndDecrypt(TStatusPtr&& spStatus, const TBuffer& encodedChunk, TBuffer& decodedChunk)
{
    const auto pStatus = dynamic_cast<CStatus*>(spStatus.get());

    if (!IsValid() ||
        pStatus == nullptr)
    {
        throw std::logic_error(c_errorDecrypt);
    }

    if (encodedChunk.size() < pStatus->Iv.size())
    {
        throw std::logic_error(c_errorSmallChunk);
    }

    AppendDecrypt(pStatus, encodedChunk.data(), encodedChunk.size(), decodedChunk, true);
}

void CAES256Cryptor::AppendEncrypt(CStatus* pStatus, const TBuffer::value_type* pSourceChunk, size_t sourceChunkSize, TBuffer& appendChunk, bool /*lastChunk*/)
{
    assert(pSourceChunk != nullptr);
    static_assert(sizeof(UCHAR) == sizeof(TBuffer::value_type), "UCHAR must be equal with uint8_t");

    //const auto flags = lastChunk ? BCRYPT_BLOCK_PADDING : 0U;
    const auto flags = 0;

    ULONG encodedSize = 0;
    auto res = BCryptEncrypt(pStatus->Key,
                             static_cast<PUCHAR>(const_cast<TBuffer::value_type*>(pSourceChunk)),
                             static_cast<ULONG>(sourceChunkSize),
                             nullptr,
                             static_cast<PUCHAR>(pStatus->Iv.data()),
                             static_cast<ULONG>(pStatus->Iv.size()),
                             nullptr,
                             0UL,
                             &encodedSize,
                             flags);
    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorEncrypt);
    }

    const auto offset = appendChunk.size();
    appendChunk.resize(offset + encodedSize);
    res = BCryptEncrypt(pStatus->Key,
                        static_cast<PUCHAR>(const_cast<TBuffer::value_type*>(pSourceChunk)),
                        static_cast<ULONG>(sourceChunkSize),
                        nullptr,
                        static_cast<PUCHAR>(pStatus->Iv.data()),
                        static_cast<ULONG>(pStatus->Iv.size()),
                        static_cast<PUCHAR>(appendChunk.data() + offset),
                        static_cast<ULONG>(appendChunk.size()),
                        &encodedSize,
                        flags);
    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorEncrypt);
    }
}

void CAES256Cryptor::AppendDecrypt(CStatus* pStatus, const TBuffer::value_type* pEncodedChunk, size_t encodedChunkSize, TBuffer& appendChunk, bool /*lastChunk*/)
{
    assert(pEncodedChunk != nullptr);
    static_assert(sizeof(UCHAR) == sizeof(TBuffer::value_type), "UCHAR must be equal with uint8_t");

    //const auto flags = lastChunk ? BCRYPT_BLOCK_PADDING : 0U;
    const auto flags = 0;

    ULONG encodedSize = 0;
    auto res = BCryptDecrypt(pStatus->Key,
                             static_cast<PUCHAR>(const_cast<TBuffer::value_type*>(pEncodedChunk)),
                             static_cast<ULONG>(encodedChunkSize),
                             nullptr,
                             static_cast<PUCHAR>(pStatus->Iv.data()),
                             static_cast<ULONG>(pStatus->Iv.size()),
                             nullptr,
                             0UL,
                             &encodedSize,
                             flags);
    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorEncrypt);
    }

    const auto offset = appendChunk.size();
    appendChunk.resize(offset + encodedSize);
    res = BCryptDecrypt(pStatus->Key,
                        static_cast<PUCHAR>(const_cast<TBuffer::value_type*>(pEncodedChunk)),
                        static_cast<ULONG>(encodedChunkSize),
                        nullptr,
                        static_cast<PUCHAR>(pStatus->Iv.data()),
                        static_cast<ULONG>(pStatus->Iv.size()),
                        static_cast<PUCHAR>(appendChunk.data() + offset),
                        static_cast<ULONG>(appendChunk.size()),
                        &encodedSize,
                        flags);
    if (!BCRYPT_SUCCESS(res))
    {
        throw status_runtime_error(res, c_errorEncrypt);
    }
}
