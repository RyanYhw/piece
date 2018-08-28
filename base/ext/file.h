#ifndef ONEPIECE_BASE_EXT_FILE_H_
#define ONEPIECE_BASE_EXT_FILE_H_


#include <stdio.h>
#include <stdint.h>



class FileBase {
public:
    ~FileBase() = default;

    static ssize_t write(int fd, uint8_t *buf, size_t size, off_t offset);
protected:
    FileBase() = default;
};

#endif  // ONEPIECE_BASE_EXT_FILE_H_