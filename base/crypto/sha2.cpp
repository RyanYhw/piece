#include "base/crypto/sha2.h"

#include <openssl/sha.h>

namespace base {


void SHA2::sha2(const StringPiece& input, std::string* output) {
    if (input.size() <= 0 || output == nullptr) return;

    SHA256_CTX ctx;

    SHA256_Init(&ctx);
    SHA256_Update(&ctx, (const void *)input.data(), input.size());

    unsigned char buf[32]= {'\0'};
    SHA256_Final(buf, &ctx);

    std::string tmp((const char*)buf, 32);
    output->swap(tmp);
}

}
