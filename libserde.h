#ifndef __LIB_SERDE__
#define __LIB_SERDE__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// read_/Write signed data.

bool serde_write_8(FILE *f, int8_t i);
bool serde_write_16(FILE *f, int16_t i);
bool serde_write_32(FILE *f, int32_t i);
bool serde_write_64(FILE *f, int64_t i);
bool serde_read_8(FILE *f, int8_t *i);
bool serde_read_16(FILE *f, int8_t *i);
bool serde_read_32(FILE *f, int32_t *i);
bool serde_read_64(FILE *f, int64_t *i);

// read_/Write unsigned data.

bool serde_write_u8(FILE *f, uint8_t i);
bool serde_write_u16(FILE *f, uint16_t i);
bool serde_write_u32(FILE *f, uint32_t i);
bool serde_write_u64(FILE *f, uint64_t i);
bool serde_read_u8(FILE *f, uint8_t *i);
bool serde_read_u16(FILE *f, uint8_t *i);
bool serde_read_u32(FILE *f, uint32_t *i);
bool serde_read_u64(FILE *f, uint64_t *i);

#endif /* __LIB_SERDE__ */
