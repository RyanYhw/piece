#include "base/encoding/hex.h"

namespace base {

// fromHexChar converts a hex character into its value.
static  bool fromHexChar(const char c, char & v) {
    bool ret = true;
    if ('0' <= c && c <= '9') {
        v =  c - '0';
    } else if  ('a' <= c && c <= 'f') {
        v = c - 'a' + 10;
    } else if ('A' <= c && c <= 'F') {
        v = c - 'A' + 10;
    } else {
        ret = false;
    }
    return ret;
  }

std::string Hex::encodeToString(const StringPiece &input) {
    std::string output;
    output.reserve(2 * input.size());
    for (int i = 0; i < input.size(); ++i) {
        const unsigned char v = input.data()[i];
        output.push_back(hexTable_[v >> 4]);
        output.push_back(hexTable_[v & 0x0f]);
    }
    return output;
}

// decodeString expects that src contain only hexadecimal
// characters and that src should have an even length.
bool Hex::decodeString(const StringPiece& input, std::string* output) {
    int size = input.size();
    if (size % 2 == 1) return false;

    std::string tmp;
    tmp.reserve(input.size()/2);
    char p, s;
    const char * src = input.data();
    for (int i = 0; i < size/2; ++i) {
        if (!fromHexChar(src[i*2], p)) {
            return false;
        }
        if (!fromHexChar(src[i*2+1], s)) {
            return false;
        }
        tmp.push_back(((p << 4) | s));
    }
    output->swap(tmp);
    return true;
}

const char* const Hex::hexTable_ = "0123456789abcdef";

}
