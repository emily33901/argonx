#include "precompiled.hh"

#include "steamcrypt.hh"

#include <cryptopp/crc.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>

using namespace CryptoPP;

using namespace Argonx;

// clang-format off
static u8 PUBLIC_KEY[] = {
    0x30, 0x81, 0x9D, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01,
    0x05, 0x00, 0x03, 0x81, 0x8B, 0x00, 0x30, 0x81, 0x87, 0x02, 0x81, 0x81, 0x00, 0xDF, 0xEC, 0x1A,
    0xD6, 0x2C, 0x10, 0x66, 0x2C, 0x17, 0x35, 0x3A, 0x14, 0xB0, 0x7C, 0x59, 0x11, 0x7F, 0x9D, 0xD3,
    0xD8, 0x2B, 0x7A, 0xE3, 0xE0, 0x15, 0xCD, 0x19, 0x1E, 0x46, 0xE8, 0x7B, 0x87, 0x74, 0xA2, 0x18,
    0x46, 0x31, 0xA9, 0x03, 0x14, 0x79, 0x82, 0x8E, 0xE9, 0x45, 0xA2, 0x49, 0x12, 0xA9, 0x23, 0x68,
    0x73, 0x89, 0xCF, 0x69, 0xA1, 0xB1, 0x61, 0x46, 0xBD, 0xC1, 0xBE, 0xBF, 0xD6, 0x01, 0x1B, 0xD8,
    0x81, 0xD4, 0xDC, 0x90, 0xFB, 0xFE, 0x4F, 0x52, 0x73, 0x66, 0xCB, 0x95, 0x70, 0xD7, 0xC5, 0x8E,
    0xBA, 0x1C, 0x7A, 0x33, 0x75, 0xA1, 0x62, 0x34, 0x46, 0xBB, 0x60, 0xB7, 0x80, 0x68, 0xFA, 0x13,
    0xA7, 0x7A, 0x8A, 0x37, 0x4B, 0x9E, 0xC6, 0xF4, 0x5D, 0x5F, 0x3A, 0x99, 0xF9, 0x9E, 0xC4, 0x3A,
    0xE9, 0x63, 0xA2, 0xBB, 0x88, 0x19, 0x28, 0xE0, 0xE7, 0x14, 0xC0, 0x42, 0x89, 0x02, 0x01, 0x11,
};
// clang-format on

SteamCrypt::SteamCrypt() {
    rnd = new CryptoPP::AutoSeededRandomPool();
}

void SteamCrypt::GenerateSessionKey(Buffer &b) {
    CryptoPP::RSA::PublicKey publicKey;

    ArraySource source(PUBLIC_KEY, sizeof(PUBLIC_KEY), true);
    publicKey.Load(source);

    RSAES_OAEP_SHA_Encryptor rsa(publicKey);
    auto                     rsaSize = rsa.FixedCiphertextLength();

    rnd->GenerateBlock(sessionKey, sizeof(sessionKey));

    u8 cryptedSessionKey[128];

    rsa.Encrypt(*rnd, sessionKey, sizeof(sessionKey), cryptedSessionKey);
    b.Write(cryptedSessionKey);

    u8 crc[4];

    CRC32().CalculateDigest(crc, cryptedSessionKey, rsaSize);
    b.Write(crc);
    b.Write(0);
}

void SteamCrypt::SymetricEncrypt(Buffer &in, Buffer &out) {
    auto size = in.SizeNoBase();

    auto cryptedSize = (size / 16 + 1) * 16;

    u8 iv[16];
    u8 cryptedIv[16];
    rnd->GenerateBlock(iv, 16);
    ECB_Mode<AES>::Encryption(sessionKey, 32).ProcessData(cryptedIv, iv, sizeof(iv));

    // expand storage
    in.SetPosEnd();
    in.Fill(0, cryptedSize - size);

    in.SetPos(0);

    u8 *dataIn = in.Read(0);

    CBC_Mode<AES>::Encryption e(sessionKey, 32, iv);
    ArraySource(
        dataIn,
        size,
        true,
        new StreamTransformationFilter(e, new ArraySink(dataIn, cryptedSize)));

    // out.Write(std::make_pair((u8 *)cryptedIv, 16), std::make_pair(dataIn, cryptedSize));

    in.SetPos(0);
    in.SetBase(0);
    in.Write(cryptedIv);

    out = in;
}

void SteamCrypt::SymetricDecrypt(Buffer &in, Buffer &out) {
    in.SetPos(0);

    byte iv[16];
    ECB_Mode<AES>::Decryption(sessionKey, sizeof(sessionKey)).ProcessData(iv, in.Read(16), 16);

    auto                      cryptedData = in.Read(0);
    CBC_Mode<AES>::Decryption d(sessionKey, sizeof(sessionKey), iv);
    // I don't see any way to get the decrypted size other than to use a string
    std::string output;
    ArraySource(
        cryptedData,
        in.SizeNoBase() - 16,
        true,
        new StreamTransformationFilter(d, new StringSink(output)));

    out.Write(std::make_pair(output.data(), output.size()));
}
