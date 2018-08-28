#include "gtest/gtest.h"

#include <string.h>
#include <memory>

#include "base/crypto/aes.h"
#include "base/stringpiece.h"
#include "base/encoding/base64.h"
#include "base/omemory.h"

using namespace base;

/**
 * see http://www.devglan.com/online-tools/aes-encryption-decryption
 */

TEST(AESTEST, CBC_16) {
    
    std::string input ("for testing, aaaaes");
    std::string output;
    base::StringPiece key("1234567890123456");

    int rsize = roundAlign(input.size(), 16); 

    ASSERT_TRUE(AES::aesCBC16Encypt(input, key, &output) == rsize);
    std::string b64;
    base::Base64Encode(output, &b64);
    
    EXPECT_EQ("4dfGgyPA0YKCLEqq209UrA1s5XL5DP1LzlyrrTx0mxY=", b64);


    std::string org_output;
    int ret = AES::aesCBC16Decrypt(output, key, &org_output);
    ASSERT_TRUE(ret == (int)input.size());
    EXPECT_EQ(org_output, input);
}

TEST(AESTEST, CBC_32) {
    
    std::string input ("for testing, aaaaes, this is 12345678990");
    std::string output;
    base::StringPiece key("12345678901234561234567890123456");

    int rsize = roundAlign(input.size(), 16); 

    ASSERT_TRUE(AES::aesCBC32Encypt(input, key, &output) == rsize);
    std::string b64;
    base::Base64Encode(output, &b64);
    
    EXPECT_EQ("uJQQ0ZOI6YH3dlub08An0i2wZs2Fw63yC0MjXRUTxWQap4xysKQNsy8fEsNsjyjC", b64);


    std::string org_output;
    int ret = AES::aesCBC32Decrypt(output, key, &org_output);
    ASSERT_TRUE(ret == (int)input.size());
    EXPECT_EQ(org_output, input);
}
