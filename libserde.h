#ifndef __LIB_SERDE__
#define __LIB_SERDE__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Lib serde
//
// All functions return true on success,
// so that they can be chained together as:
//
// > bool ok = true;
// > ok = ok && serde_write(...);
// > ok = ok && serde_write(...);
// > ok = ok && serde_write(...);
// > return ok; // ie: success
//
// Prefer using `serde_read` and `serde_write` over raw type functions.
//
// This library provides the following macros for convenience:
//  * serde_start - defines boolean
//  * serde_do
//    - conditionally executed based on serde error status
//    - invokes the correct read/write function based on variable type
//  * serde_error - check for error
//  * serde_return - return the serde success state

#define serde_read(fp, var) \
    _Generic((var),\
        double*: serde_read_d,\
        uint8_t*: serde_read_u8,\
        uint16_t*: serde_read_u16,\
        uint32_t*: serde_read_u32,\
        uint64_t*: serde_read_u64,\
        int8_t*: serde_read_8,\
        int16_t*: serde_read_16,\
        int32_t*: serde_read_32,\
        int64_t*: serde_read_64\
    )(fp, var)

#define serde_write(fp, var) \
    _Generic((var),\
        double: serde_write_d,\
        uint8_t: serde_write_u8,\
        uint16_t: serde_write_u16,\
        uint32_t: serde_write_u32,\
        uint64_t: serde_write_u64,\
        int8_t: serde_write_8,\
        int16_t: serde_write_16,\
        int32_t: serde_write_32,\
        int64_t: serde_write_64\
    )(fp, var)


#define serde_start() bool serde_ok = true
#define serde_return() return serde_ok;
#define serde_error() (!serde_ok)

#define serde_do(rw, filep, var) \
    (serde_ok = serde_ok && serde_##rw(filep, var))

// read/write signed data.

bool serde_write_8(FILE *f, int8_t i);
bool serde_write_16(FILE *f, int16_t i);
bool serde_write_32(FILE *f, int32_t i);
bool serde_write_64(FILE *f, int64_t i);
bool serde_read_8(FILE *f, int8_t *i);
bool serde_read_16(FILE *f, int16_t *i);
bool serde_read_32(FILE *f, int32_t *i);
bool serde_read_64(FILE *f, int64_t *i);

// read/write unsigned data.

bool serde_write_u8(FILE *f, uint8_t i);
bool serde_write_u16(FILE *f, uint16_t i);
bool serde_write_u32(FILE *f, uint32_t i);
bool serde_write_u64(FILE *f, uint64_t i);
bool serde_read_u8(FILE *f, uint8_t *i);
bool serde_read_u16(FILE *f, uint16_t *i);
bool serde_read_u32(FILE *f, uint32_t *i);
bool serde_read_u64(FILE *f, uint64_t *i);

bool serde_write_d(FILE *f, double i);
bool serde_read_d(FILE *f, double *i);

#endif /* __LIB_SERDE__ */
