#include "libserde.h"

#include <math.h>
#include <stdlib.h>
#include <unistd.h>

// Handle endian conversion.
#include <byteswap.h>
#include <endian.h>

bool serde_write_8(FILE *f, int8_t i) {
  return fwrite(&i, sizeof(int8_t), 1, f) != 1;
}
bool serde_write_16(FILE *f, int16_t i) {
  i = htobe16(i);
  return fwrite(&i, sizeof(int16_t), 1, f) != 1;
}
bool serde_write_32(FILE *f, int32_t i) {
  i = htobe32(i);
  return fwrite(&i, sizeof(int32_t), 1, f) != 1;
}
bool serde_write_64(FILE *f, int64_t i) {
  i = htobe64(i);
  return fwrite(&i, sizeof(int64_t), 1, f) != 1;
}
bool serde_read_8(FILE *f, int8_t *i) {
  size_t s = fread(i, sizeof(int8_t), 1, f);
  return s != 1;
}
bool serde_read_16(FILE *f, int16_t *i) {
  size_t s = fread(i, sizeof(int16_t), 1, f);
  *i = be16toh(*i);
  return s != 1;
}
bool serde_read_32(FILE *f, int32_t *i) {
  size_t s = fread(i, sizeof(int32_t), 1, f);
  *i = be32toh(*i);
  return s != 1;
}
bool serde_read_64(FILE *f, int64_t *i) {
  size_t s = fread(i, sizeof(int64_t), 1, f);
  *i = be64toh(*i);
  return s != 1;
}

bool serde_write_u8(FILE *f, uint8_t i) {
  return fwrite(&i, sizeof(uint8_t), 1, f) != 1;
}
bool serde_write_u16(FILE *f, uint16_t i) {
  i = htobe16(i);
  return fwrite(&i, sizeof(uint16_t), 1, f) != 1;
}
bool serde_write_u32(FILE *f, uint32_t i) {
  i = htobe32(i);
  return fwrite(&i, sizeof(uint32_t), 1, f) != 1;
}
bool serde_write_u64(FILE *f, uint64_t i) {
  i = htobe64(i);
  return fwrite(&i, sizeof(uint64_t), 1, f) != 1;
}
bool serde_read_u8(FILE *f, uint8_t *i) {
  size_t s = fread(i, sizeof(uint8_t), 1, f);
  return s != 1;
}
bool serde_read_u16(FILE *f, uint16_t *i) {
  size_t s = fread(i, sizeof(uint16_t), 1, f);
  *i = be16toh(*i);
  return s != 1;
}
bool serde_read_u32(FILE *f, uint32_t *i) {
  size_t s = fread(i, sizeof(uint32_t), 1, f);
  *i = be32toh(*i);
  return s != 1;
}
bool serde_read_u64(FILE *f, uint64_t *i) {
  size_t s = fread(i, sizeof(uint64_t), 1, f);
  *i = be64toh(*i);
  return s != 1;
}

