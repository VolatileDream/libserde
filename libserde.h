#ifndef __LIB_SERDE__
#define __LIB_SERDE__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// TODO: Move out of this file?
typedef struct {
  uint64_t capacity; // length of bytes
  uint64_t length; // of data in bytes
  uint64_t index; // read/write index
  uint8_t* bytes;
} bytebuffer_t;

// Returns an initialized struct.
bytebuffer_t* bb_alloc(uint64_t size);
void bb_free(bytebuffer_t* b);

// For reading out of the buffer.
// Returns length - index.
uint64_t bb_remaining_data(bytebuffer_t*);
// For writing to the buffer.
// Returns capacity - index.
uint64_t bb_remaining_capacity(bytebuffer_t*);

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
  _Generic((fp), \
    FILE*: _Generic((var),\
        double*: serde_readf_d,\
        uint8_t*: serde_readf_u8,\
        uint16_t*: serde_readf_u16,\
        uint32_t*: serde_readf_u32,\
        uint64_t*: serde_readf_u64,\
        int8_t*: serde_readf_8,\
        int16_t*: serde_readf_16,\
        int32_t*: serde_readf_32,\
        int64_t*: serde_readf_64\
    ),\
    bytebuffer_t*: _Generic((var),\
        double*: serde_readb_d,\
        uint8_t*: serde_readb_u8,\
        uint16_t*: serde_readb_u16,\
        uint32_t*: serde_readb_u32,\
        uint64_t*: serde_readb_u64,\
        int8_t*: serde_readb_8,\
        int16_t*: serde_readb_16,\
        int32_t*: serde_readb_32,\
        int64_t*: serde_readb_64\
    ) \
    )(fp, var)

#define serde_write(fp, var) \
  _Generic((fp), \
    FILE*: _Generic((var),\
        double: serde_writef_d,\
        uint8_t: serde_writef_u8,\
        uint16_t: serde_writef_u16,\
        uint32_t: serde_writef_u32,\
        uint64_t: serde_writef_u64,\
        int8_t: serde_writef_8,\
        int16_t: serde_writef_16,\
        int32_t: serde_writef_32,\
        int64_t: serde_writef_64\
    ),\
    bytebuffer_t*: _Generic((var),\
        double: serde_writeb_d,\
        uint8_t: serde_writeb_u8,\
        uint16_t: serde_writeb_u16,\
        uint32_t: serde_writeb_u32,\
        uint64_t: serde_writeb_u64,\
        int8_t: serde_writeb_8,\
        int16_t: serde_writeb_16,\
        int32_t: serde_writeb_32,\
        int64_t: serde_writeb_64\
    )\
    )(fp, var)


// Convenience macros

#define serde_start() bool serde_ok = true
#define serde_return() return serde_ok;
#define serde_error() (!serde_ok)

#define serde_do(rw, filep, var) \
    (serde_ok = serde_ok && serde_##rw(filep, var))

// Files.
// read/write signed data.

bool serde_writef_8(FILE *f, int8_t i);
bool serde_writef_16(FILE *f, int16_t i);
bool serde_writef_32(FILE *f, int32_t i);
bool serde_writef_64(FILE *f, int64_t i);
bool serde_readf_8(FILE *f, int8_t *i);
bool serde_readf_16(FILE *f, int16_t *i);
bool serde_readf_32(FILE *f, int32_t *i);
bool serde_readf_64(FILE *f, int64_t *i);

// read/write unsigned data.

bool serde_writef_u8(FILE *f, uint8_t i);
bool serde_writef_u16(FILE *f, uint16_t i);
bool serde_writef_u32(FILE *f, uint32_t i);
bool serde_writef_u64(FILE *f, uint64_t i);
bool serde_readf_u8(FILE *f, uint8_t *i);
bool serde_readf_u16(FILE *f, uint16_t *i);
bool serde_readf_u32(FILE *f, uint32_t *i);
bool serde_readf_u64(FILE *f, uint64_t *i);

bool serde_writef_d(FILE *f, double i);
bool serde_readf_d(FILE *f, double *i);

// Using the bytebuffer_t

// read/write signed data.

bool serde_writeb_8(bytebuffer_t *f, int8_t i);
bool serde_writeb_16(bytebuffer_t *f, int16_t i);
bool serde_writeb_32(bytebuffer_t *f, int32_t i);
bool serde_writeb_64(bytebuffer_t *f, int64_t i);
bool serde_readb_8(bytebuffer_t *f, int8_t *i);
bool serde_readb_16(bytebuffer_t *f, int16_t *i);
bool serde_readb_32(bytebuffer_t *f, int32_t *i);
bool serde_readb_64(bytebuffer_t *f, int64_t *i);

// read/write unsigned data.

bool serde_writeb_u8(bytebuffer_t *f, uint8_t i);
bool serde_writeb_u16(bytebuffer_t *f, uint16_t i);
bool serde_writeb_u32(bytebuffer_t *f, uint32_t i);
bool serde_writeb_u64(bytebuffer_t *f, uint64_t i);
bool serde_readb_u8(bytebuffer_t *f, uint8_t *i);
bool serde_readb_u16(bytebuffer_t *f, uint16_t *i);
bool serde_readb_u32(bytebuffer_t *f, uint32_t *i);
bool serde_readb_u64(bytebuffer_t *f, uint64_t *i);

bool serde_writeb_d(bytebuffer_t *f, double i);
bool serde_readb_d(bytebuffer_t *f, double *i);

#endif /* __LIB_SERDE__ */
