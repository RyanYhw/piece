#ifndef ONEPIECE_BASE_CRYPTO_AES_H_
#define ONEPIECE_BASE_CRYPTO_AES_H_

#include "stringpiece.h"

#include <string>
/*
enum class AESError {
   SUCCESS = 0,
   UNSUPPORTED_MODE = -1,
   UNSUPPORTED_DIRECTION = -2,
   UNSUPPORTED_KEY_LENGTH = -3,
   RIJNDAEL_BAD_KEY = -4,
   NOT_INITIALIZED = -5,
   RIJNDAEL_BAD_DIRECTION = -6,
   RIJNDAEL_CORRUPTED_DATA = -7,
   BADPARMA = -8
};
*/

/**
 * @brief The AES class
 * ErrCode
 * SUCCESS = 0,
 * UNSUPPORTED_MODE = -1,
 * UNSUPPORTED_DIRECTION = -2,
 * UNSUPPORTED_KEY_LENGTH = -3,
 * RIJNDAEL_BAD_KEY = -4,
 * NOT_INITIALIZED = -5,
 * RIJNDAEL_BAD_DIRECTION = -6,
 * RIJNDAEL_CORRUPTED_DATA = -7,
 * BADPARMA = -8
 */

namespace base {

class AES {
public:
    AES() = default;
    ~AES() = default;

    // Returns the encrypted buffer length in BYTES or
    // an error code < 0 in case of error
    static int aesCBC16Encypt(const StringPiece& input,
                              const StringPiece& key,
							  std::string* output);

    // Returns the decrypted buffer length in BYTES and 
    // an error code < 0 in case of error
    static int aesCBC16Decrypt(const StringPiece& input,
                               const StringPiece& key,
                               std::string* output);
    
    static int aesCBC32Encypt(const StringPiece& input,
                              const StringPiece& key,
                              std::string* output);

    static int aesCBC32Decrypt(const StringPiece& input,
                               const StringPiece& key,
                               std::string* output);

    static int aesECB16Encypt(const StringPiece& input,
                              const StringPiece& key,
							  std::string* output);

    static int aesECB16Decrypt(const StringPiece& input,
                               const StringPiece& key,
                               std::string* output);
    
};
}  // end base
#endif  // ONEPIECE_BASE_CRYPTO_AES_H_
