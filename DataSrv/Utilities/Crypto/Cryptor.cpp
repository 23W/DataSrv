#include "pch.h"

#include "Cryptor.h"
#include "AES256Cryptor.h"


CCryptorFactorty::TCryptorPtr CCryptorFactorty::Create(CodecType codec)
{
    auto spRes = TCryptorPtr{};

    switch (codec)
    {
    case CodecType::AES256CBC:
        spRes = std::make_unique<CAES256Cryptor>();
        break;
    }

    return spRes;
}
