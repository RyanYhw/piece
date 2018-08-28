#include "base/ext/file.h"

#include <unistd.h>
#include <errno.h>

#include "base/common.h"

ssize_t FileBase::write(int fd, uint8_t *buf, size_t size, off_t offset) {
    if (unlikely(!buf)) {
        return -1;
    }
    ssize_t n = 0;
    ssize_t written = 0;
    int err;
    for ( ;; ) {
        n = pwrite(fd,(void*) (buf + written), size, offset);

        if (n == -1) {
            err = errno;
            if (err == EINTR) { 
                // ("pwrite() was interrupted");
                continue;
            }
            return -1;
        }
        written += n;
        if ((size_t) n == size) {
            return written;
        }
        offset += n;
        size -= n;
    }
#if 0 // 通用方案
    // 判断是否已经为这个位置了, 这样不必重复调用lseek
    if (/*sys_offset != offset*/true) {
        if (lseek(fd, offset, SEEK_SET) == -1) {
            return -1;
        }
    }
    for ( ;; ) {
        n = write(fd, buf + written, size);
        if (n == -1) {
            err = errno;

            if (err == EINTR) {
                continue;
            }
            return -1;
        }
        written += n;

        if ((size_t) n == size) {
            return written;
        }

        size -= n;
    }
#endif

}