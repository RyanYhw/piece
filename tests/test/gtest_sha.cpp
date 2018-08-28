#include "gtest/gtest.h"

#include "base/crypto/sha2.h"
#include "base/encoding/hex.h"

TEST(SHA, SHA256) {

    std::string output;

    base::SHA2::sha2("This is a test txt !!!!", &output);

    ASSERT_TRUE(!output.empty());


    std::string hex = base::Hex::encodeToString(output);

    EXPECT_EQ(hex, "79710926b4cad7f2f47c90ac677511ffeb348115195c272b1015d0f481471162");
}
