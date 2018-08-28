#ifndef ONEPIECE_BASE_CRYPTO_SHA2_H_
#define ONEPIECE_BASE_CRYPTO_SHA2_H_

#include <string>
#include <base/stringpiece.h>

namespace base {
class SHA2 {
public:
    SHA2() = default;
    ~SHA2() = default;

    static void sha2(const StringPiece& input, std::string* output);
};

}

#endif  // ONEPIECE_BASE_CRYPTO_SHA2_H_
