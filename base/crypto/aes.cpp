#include "aes.h"

#include <memory>

#include "omemory.h"
#include "rijndael.h"
#include "crypto.h"

namespace base {

static int aes_rijndael_encrypt(Rijndael::Mode mode, 
                                const StringPiece& input,
                                const StringPiece& key,
                                Rijndael::KeyLength keyLen,
                                std::string* output); 

static int aes_rijndael_decrypt(Rijndael::Mode mode, 
                                const StringPiece& input,
                                const StringPiece& key,
                                Rijndael::KeyLength keyLen,
                                std::string* output);

static int aes_rijndael(Rijndael::Mode mode,
                        Rijndael::Direction direction,
                        const StringPiece& input,
                        const StringPiece& key,
                        Rijndael::KeyLength keyLen,
                        std::string* output);
 
int AES::aesCBC16Encypt(const StringPiece& input,
                        const StringPiece& key,
                        std::string* output) {
    return aes_rijndael(Rijndael::CBC, Rijndael::Encrypt,
                        input, key, Rijndael::Key16Bytes, output);
}

int AES::aesCBC16Decrypt( const StringPiece &input,
                          const StringPiece &key, std::string *output ) {
    return aes_rijndael(Rijndael::CBC, Rijndael::Decrypt,
                        input, key, Rijndael::Key16Bytes, output);
}

int AES::aesCBC32Encypt(const StringPiece& input,
                        const StringPiece& key,
                        std::string* output) {
    return aes_rijndael(Rijndael::CBC, Rijndael::Encrypt,
                        input, key, Rijndael::Key32Bytes, output);
}

int AES::aesCBC32Decrypt( const StringPiece &input,
                          const StringPiece &key, std::string *output ) {
    return aes_rijndael(Rijndael::CBC, Rijndael::Decrypt,
                        input, key, Rijndael::Key32Bytes, output);
}

int AES::aesECB16Encypt(const StringPiece& input,
                        const StringPiece& key,
                        std::string* output) {
    return aes_rijndael(Rijndael::ECB, Rijndael::Encrypt, 
                        input, key, Rijndael::Key16Bytes, output);
}

int AES::aesECB16Decrypt(const StringPiece& input,
                        const StringPiece& key,
                        std::string* output) {
    return aes_rijndael(Rijndael::ECB, Rijndael::Decrypt, 
                        input, key, Rijndael::Key16Bytes, output);               
}

// --------------------------------
//
int aes_rijndael_encrypt(Rijndael::Mode mode, 
                         const StringPiece& input,
                         const StringPiece& key,
                         Rijndael::KeyLength keyLen,
                         std::string* output) {
    int ret = (int) RIJNDAEL_SUCCESS;
    std::unique_ptr<Rijndael> rijndael(new Rijndael);
    ret = rijndael->init(mode, Rijndael::Encrypt, 
            reinterpret_cast<const UINT8*> (key.data()), keyLen);
    if (ret != RIJNDAEL_SUCCESS) { return ret; }
    
    int sOutput = (int)roundAlign(input.size(), key.size());
    UINT8 outBuffer[sOutput] = {'\0'};
    ret = rijndael->padEncrypt(reinterpret_cast<const UINT8 *>(input.data()), 
            input.size(), outBuffer);
    if (ret >  0) {
        std::string tmp(reinterpret_cast<const char*>(outBuffer), ret);
        output->swap(tmp);
    }
    return ret;
}

int aes_rijndael_decrypt(Rijndael::Mode mode, 
                        const StringPiece& input,
                        const StringPiece& key,
                        Rijndael::KeyLength keyLen,
                        std::string* output) {
    int ret = (int) RIJNDAEL_SUCCESS;
    std::unique_ptr<Rijndael> rijndael(new Rijndael);
    ret = rijndael->init(mode, Rijndael::Decrypt, 
            reinterpret_cast<const UINT8*> (key.data()), keyLen);
    if (ret != RIJNDAEL_SUCCESS) { return ret; }
    
    UINT8 outBuffer[input.size()] = {'\0'};
    ret = rijndael->padDecrypt(reinterpret_cast<const UINT8 *>(input.data()), 
            input.size(), outBuffer);
    if (ret > 0) {
        std::string tmp(reinterpret_cast<const char*>(outBuffer), ret);
        output->swap(tmp);
    }
    return ret;
}

int aes_rijndael(Rijndael::Mode mode,
                 Rijndael::Direction direction,
                 const StringPiece& input,
                 const StringPiece& key,
                 Rijndael::KeyLength keyLen,
                 std::string* output) {
    if (output == nullptr) return AES_BADPARMA;
    switch (direction) {
        case Rijndael::Encrypt:
            return aes_rijndael_encrypt(mode, input, key, keyLen, output);
        default:
            return aes_rijndael_decrypt(mode, input, key, keyLen, output);
    }
}
}
