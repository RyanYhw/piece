#ifndef _ONEPIECE_BASE_TIME_TIME_H_
#define _ONEPIECE_BASE_TIME_TIME_H_

#include <stdint.h>

#include <chrono>

#include <sys/time.h>

#include "base/noncopyable.h"

class Time : public noncopyable {
public:
    static int64_t NowNano() noexcept { 
        return std::chrono::duration_cast<std::chrono::nanoseconds>
        (getTick().time_since_epoch()).count();
    }

    static int64_t NowMilli() noexcept {
        struct timeval val;
        gettimeofday(&val, nullptr);

        return val.tv_sec * 1e3 + val.tv_usec / 1e3;
    }
private:
    static auto getTick() noexcept -> 
        decltype(std::chrono::high_resolution_clock::now()) {
        return std::chrono::high_resolution_clock::now();
    }
};

#endif  // _ONEPIECE_BASE_TIME_TIME_H_