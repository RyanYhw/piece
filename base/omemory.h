#ifndef ONEPIECE_BASE_OMEMORY_H_
#define ONEPIECE_BASE_OMEMORY_H_

#include <stdlib.h>

/*!
 * \brief roundAlign
 * \param bytes
 * \param align
 * \return aligned bytes
 */
inline size_t roundAlign(size_t bytes, size_t align) {
    return  (((bytes) + (align - 1)) & ~(align - 1));
}

#endif  // ONEPIECE_BASE_OMEMORY_H_ 
