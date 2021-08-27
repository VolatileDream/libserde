#ifndef __LIB_SERDE__
#define __LIB_SERDE__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//
// Lib serde
//
// All functions return true _on failure_, so that they can
// be chained together as:
//
// > bool fail = false;
// > fail = fail || serde_write(...);
// > fail = fail || serde_write(...);
// > fail = fail || serde_write(...);
// > return !fail; // ie: success


// read_/Write signed data.

bool serde_write_8(FILE *f, int8_t i);
bool serde_write_16(FILE *f, int16_t i);
bool serde_write_32(FILE *f, int32_t i);
bool serde_write_64(FILE *f, int64_t i);
bool serde_read_8(FILE *f, int8_t *i);
bool serde_read_16(FILE *f, int16_t *i);
bool serde_read_32(FILE *f, int32_t *i);
bool serde_read_64(FILE *f, int64_t *i);

// read_/Write unsigned data.

bool serde_write_u8(FILE *f, uint8_t i);
bool serde_write_u16(FILE *f, uint16_t i);
bool serde_write_u32(FILE *f, uint32_t i);
bool serde_write_u64(FILE *f, uint64_t i);
bool serde_read_u8(FILE *f, uint8_t *i);
bool serde_read_u16(FILE *f, uint16_t *i);
bool serde_read_u32(FILE *f, uint32_t *i);
bool serde_read_u64(FILE *f, uint64_t *i);

#define serde_read(fp, var) \
    _Generic((var),\
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
        uint8_t: serde_write_u8,\
        uint16_t: serde_write_u16,\
        uint32_t: serde_write_u32,\
        uint64_t: serde_write_u64,\
        int8_t: serde_write_8,\
        int16_t: serde_write_16,\
        int32_t: serde_write_32,\
        int64_t: serde_write_64\
    )(fp, var)


#define serde_start() bool serde_fail = false

#define serde_return() return !serde_fail;

#define serde_do(rw, filep, var) \
    (serde_fail = serde_fail || serde_##rw(filep, var))

#define serde_failure() (serde_fail)

#endif /* __LIB_SERDE__ */
