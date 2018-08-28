#include "gtest/gtest.h"

#include <string.h>
#include <memory>
#include <iosfwd>
#include "base/crypto/md5.h"
#include "base/encoding/hex.h"
#include "base/stringpiece.h"



TEST(MD5, md5) {
    MD5_CTX * ctx = new MD5_CTX;
    MD5_Init(ctx);

    const char * data = "This is a test 1123";

    MD5_Update(ctx, (const void *)data, strlen(data));
    unsigned char output[16] = {'\0'};
    MD5_Final(output, ctx);

    base::StringPiece sp((const char *)output, 16);
    std::string out = base::Hex::encodeToString(sp);

    EXPECT_EQ("8a2804640a7072ea114a71a580c77a32", out);
}

TEST(MD5, md5_same) {
    // the data is from internet
    unsigned char md5_data1[] = {0x4d, 0xc9, 0x68, 0xff, 0x0e, 0xe3, 0x5c,
                                 0x20, 0x95, 0x72, 0xd4, 0x77, 0x7b, 0x72,
                                 0x15, 0x87, 0xd3, 0x6f, 0xa7, 0xb2, 0x1b,
                                 0xdc, 0x56, 0xb7, 0x4a, 0x3d, 0xc0, 0x78,
                                 0x3e, 0x7b, 0x95, 0x18, 0xaf, 0xbf, 0xa2,
                                 0x00, 0xa8, 0x28, 0x4b, 0xf3, 0x6e, 0x8e,
                                 0x4b, 0x55, 0xb3, 0x5f, 0x42, 0x75, 0x93,
                                 0xd8, 0x49, 0x67, 0x6d, 0xa0, 0xd1, 0x55,
                                 0x5d, 0x83, 0x60, 0xfb, 0x5f, 0x07, 0xfe, 0xa2};
    unsigned char md5_data2[] = {0x4d, 0xc9, 0x68, 0xff, 0x0e, 0xe3, 0x5c, 0x20,
                                 0x95, 0x72, 0xd4, 0x77, 0x7b, 0x72, 0x15, 0x87,
                                 0xd3, 0x6f, 0xa7, 0xb2, 0x1b, 0xdc, 0x56, 0xb7,
                                 0x4a, 0x3d, 0xc0, 0x78, 0x3e, 0x7b, 0x95, 0x18,
                                 0xaf, 0xbf, 0xa2, 0x02, 0xa8, 0x28, 0x4b, 0xf3,
                                 0x6e, 0x8e, 0x4b, 0x55, 0xb3, 0x5f, 0x42, 0x75,
                                 0x93, 0xd8, 0x49, 0x67, 0x6d, 0xa0, 0xd1, 0xd5,
                                 0x5d, 0x83, 0x60, 0xfb, 0x5f, 0x07, 0xfe, 0xa2};
    std::string out1;
    std::string out2;
    {
        MD5_CTX * ctx = new MD5_CTX;
        MD5_Init(ctx);

        MD5_Update(ctx, (const void *)md5_data1, sizeof(md5_data1)/sizeof(unsigned char));
        unsigned char output[16] = {'\0'};
        MD5_Final(output, ctx);

        base::StringPiece sp((const char *)output, 16);
        out1 = base::Hex::encodeToString(sp);
    }
    {
        MD5_CTX * ctx = new MD5_CTX;
        MD5_Init(ctx);

        MD5_Update(ctx, (const void *)md5_data2, sizeof(md5_data2)/sizeof(unsigned char));
        unsigned char output[16] = {'\0'};
        MD5_Final(output, ctx);

        base::StringPiece sp((const char *)output, 16);
        out2 = base::Hex::encodeToString(sp);
    }

    EXPECT_EQ(out1, out2);
    EXPECT_EQ(out1, "008ee33a9d58b51cfeb425b0959121c9");
}
