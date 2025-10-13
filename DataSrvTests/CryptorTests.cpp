#include "pch.h"
#include "Utilities/Crypto/Cryptor.h"

namespace DataSrv::Cryptor
{
    TEST(Cryptor, PasswordHash)
    {
        const auto password1 = std::string("Test password");
        const auto password2 = password1;

        CCryptorFactorty factory;
        auto spCoder = CCryptorFactorty::TCryptorPtr{};
        ASSERT_NO_THROW(spCoder = factory.Create(CCryptorFactorty::CodecType::AES256CBC));

        auto passwordHash1 = std::vector<std::uint8_t>();
        auto passwordHash2 = std::vector<std::uint8_t>();
        ASSERT_NO_THROW(spCoder->BuildPasswordHash(password1, nullptr, passwordHash1));
        ASSERT_NO_THROW(spCoder->BuildPasswordHash(password2, nullptr, passwordHash2));

        ASSERT_EQ(passwordHash1, passwordHash2);
    }

    TEST(Cryptor, AES256CBC_Encode_Decode)
    {
        const auto password = std::string("Test password");

        constexpr const auto chunkCount = 1000UL;
        constexpr const auto chunkSize = 10000UL;
        constexpr const auto wholeSize = chunkCount * chunkSize;
        auto ethalon = std::vector<std::uint8_t>(wholeSize);
        for (auto index = 0; index < ethalon.size(); index++)
        {
            ethalon[index] = index % 0xFF;
        }

        CCryptorFactorty factory;
        auto spCoder = CCryptorFactorty::TCryptorPtr{};
        ASSERT_NO_THROW(spCoder = factory.Create(CCryptorFactorty::CodecType::AES256CBC));

        auto passwordHash = std::vector<std::uint8_t>();
        auto encoded = std::vector<std::uint8_t>();
        auto decoded = std::vector<std::uint8_t>();
        auto chunk = std::vector<std::uint8_t>(chunkSize, 0);

        auto spStatus = CCryptor::TStatusPtr{};
        spCoder->BuildPasswordHash(password, nullptr, passwordHash);

        for (auto chunkIndex = 0; chunkIndex < chunkCount; chunkIndex++)
        {
            std::memcpy(chunk.data(), ethalon.data() + chunkIndex * chunkSize, chunkSize);

            if (chunkIndex == 0)
            {
                ASSERT_NO_THROW(spStatus = spCoder->StartEncrypt(passwordHash, chunk, encoded));
            }
            else if (chunkIndex == chunkCount - 1)
            {
                ASSERT_NO_THROW(spCoder->EndEncrypt(std::move(spStatus), chunk, encoded));
            }
            else
            {
                ASSERT_NO_THROW(spCoder->NextEncrypt(spStatus, chunk, encoded));
            }
        }

        for (auto chunkIndex = 0; chunkIndex < chunkCount; chunkIndex++)
        {
            const auto currentChunkSize = (chunkIndex == chunkCount - 1) ? encoded.size() - chunkIndex * chunkSize : chunkSize;
            chunk.resize(currentChunkSize);
            std::memcpy(chunk.data(), encoded.data() + chunkIndex * chunkSize, currentChunkSize);

            if (chunkIndex == 0)
            {
                ASSERT_NO_THROW(spStatus = spCoder->StartDecrypt(passwordHash, chunk, decoded));
            }
            else if (chunkIndex == chunkCount - 1)
            {
                ASSERT_NO_THROW(spCoder->EndDecrypt(std::move(spStatus), chunk, decoded));
            }
            else
            {
                ASSERT_NO_THROW(spCoder->NextDecrypt(spStatus, chunk, decoded));
            }
        }

        ASSERT_EQ(decoded, ethalon);
    }
}