#include "gtest/gtest.h"

#include "base/encoding/hex.h"
using namespace base;
TEST(HEX, hex) {
    std::string str("hello world ~~~*%$ 你好！");

    std::string output = Hex::encodeToString(str);

    std::string dec;
    ASSERT_EQ(Hex::decodeString(output, &dec), true);

    EXPECT_EQ(str, dec);
}

TEST(HEX, hexString) {
    std::string str("7f4E387e");
    std::string dec;
    ASSERT_EQ(Hex::decodeString(str, &dec), true);

    EXPECT_EQ(4, (int)dec.size());

    EXPECT_EQ(0x7f, (int)dec[0]);
    EXPECT_EQ(0x4e, (int)dec[1]);
    EXPECT_EQ(0x38, (int)dec[2]);
    EXPECT_EQ(0x7e, (int)dec[3]);
}
