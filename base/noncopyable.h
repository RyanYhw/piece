#ifndef _ONEPIECE_BASE_NONCOPYABLE_H_
#define _ONEPIECE_BASE_NONCOPYABLE_H_

class noncopyable {
protected:
    noncopyable() = default;
    ~noncopyable() = default;
private:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator= (const noncopyable&) = delete;
};

#endif  // _ONEPIECE_BASE_NONCOPYABLE_H_