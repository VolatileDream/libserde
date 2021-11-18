#include "libserde.h"

#include <math.h>
#include <stdlib.h>
#include <unistd.h>

// To check for floating point support.
#include <stdc-predef.h>

// Handle endian conversion.
#include <byteswap.h>
#include <endian.h>

// memcpy for bytebuffer_t functions
#include <string.h>

// FILE*

bool serde_writef_8(FILE *f, int8_t i) {
  return fwrite(&i, sizeof(int8_t), 1, f) == 1;
}
bool serde_writef_16(FILE *f, int16_t i) {
  i = htobe16(i);
  return fwrite(&i, sizeof(int16_t), 1, f) == 1;
}
bool serde_writef_32(FILE *f, int32_t i) {
  i = htobe32(i);
  return fwrite(&i, sizeof(int32_t), 1, f) == 1;
}
bool serde_writef_64(FILE *f, int64_t i) {
  i = htobe64(i);
  return fwrite(&i, sizeof(int64_t), 1, f) == 1;
}
bool serde_readf_8(FILE *f, int8_t *i) {
  size_t s = fread(i, sizeof(int8_t), 1, f);
  return s == 1;
}
bool serde_readf_16(FILE *f, int16_t *i) {
  size_t s = fread(i, sizeof(int16_t), 1, f);
  *i = be16toh(*i);
  return s == 1;
}
bool serde_readf_32(FILE *f, int32_t *i) {
  size_t s = fread(i, sizeof(int32_t), 1, f);
  *i = be32toh(*i);
  return s == 1;
}
bool serde_readf_64(FILE *f, int64_t *i) {
  size_t s = fread(i, sizeof(int64_t), 1, f);
  *i = be64toh(*i);
  return s == 1;
}

bool serde_writef_u8(FILE *f, uint8_t i) {
  return fwrite(&i, sizeof(uint8_t), 1, f) == 1;
}
bool serde_writef_u16(FILE *f, uint16_t i) {
  i = htobe16(i);
  return fwrite(&i, sizeof(uint16_t), 1, f) == 1;
}
bool serde_writef_u32(FILE *f, uint32_t i) {
  i = htobe32(i);
  return fwrite(&i, sizeof(uint32_t), 1, f) == 1;
}
bool serde_writef_u64(FILE *f, uint64_t i) {
  i = htobe64(i);
  return fwrite(&i, sizeof(uint64_t), 1, f) == 1;
}
bool serde_readf_u8(FILE *f, uint8_t *i) {
  size_t s = fread(i, sizeof(uint8_t), 1, f);
  return s == 1;
}
bool serde_readf_u16(FILE *f, uint16_t *i) {
  size_t s = fread(i, sizeof(uint16_t), 1, f);
  *i = be16toh(*i);
  return s == 1;
}
bool serde_readf_u32(FILE *f, uint32_t *i) {
  size_t s = fread(i, sizeof(uint32_t), 1, f);
  *i = be32toh(*i);
  return s == 1;
}
bool serde_readf_u64(FILE *f, uint64_t *i) {
  size_t s = fread(i, sizeof(uint64_t), 1, f);
  *i = be64toh(*i);
  return s == 1;
}

#ifdef __STDC_IEC_559__
bool serde_writef_d(FILE *f, double i) {
  return fwrite(&i, sizeof(double), 1, f) == 1;
}
bool serde_readf_d(FILE *f, double *i) {
  size_t s = fread(i, sizeof(double), 1, f);
  return s == 1;
}
#else
#error libserde requires IEEE 775 floating point number support.
#endif /*__STDC_IEC_559__ */


// bytebuffer_t*

bytebuffer_t* bb_alloc(uint64_t size) {
  void* ptr = malloc(size + sizeof(bytebuffer_t));
  if (ptr == NULL) {
    return NULL;
  }
  bytebuffer_t *b = (bytebuffer_t*) ptr;
  b->capacity = size;
  b->length = 0;
  b->index = 0;
  b->bytes = (uint8_t*) (b + 1);
  return b;
}

void bb_free(bytebuffer_t *b) {
  free(b);
}

uint64_t bb_remaining_data(bytebuffer_t *b) {
  return b->length - b->index;
}
uint64_t bb_remaining_capacity(bytebuffer_t *b) {
  return b->capacity - b->index;
}

static bool b_write(bytebuffer_t *b, void* v, uint64_t count) {
  if (bb_remaining_capacity(b) < count) {
    return false;
  }
  memcpy(&b->bytes[b->index], v, count);
  b->index += count;
  if (b->index > b->length) {
    b->length = b->index;
  }
  return true;
}

static bool b_read(bytebuffer_t *b, void* v, uint64_t count) {
  if (bb_remaining_data(b) < count) {
    return false;
  }
  memcpy(v, &b->bytes[b->index], count);
  b->index += count;
  return true;
}

bool serde_writeb_8(bytebuffer_t *f, int8_t i) {
  return b_write(f, &i, sizeof(int8_t));
}
bool serde_writeb_16(bytebuffer_t *f, int16_t i) {
  i = htobe16(i);
  return b_write(f, &i, sizeof(int16_t));
}
bool serde_writeb_32(bytebuffer_t *f, int32_t i) {
  i = htobe32(i);
  return b_write(f, &i, sizeof(int32_t));
}
bool serde_writeb_64(bytebuffer_t *f, int64_t i) {
  i = htobe64(i);
  return b_write(f, &i, sizeof(int64_t));
}
bool serde_readb_8(bytebuffer_t *f, int8_t *i) {
  bool ok = b_read(f, i, sizeof(int8_t));
  return ok;
}
bool serde_readb_16(bytebuffer_t *f, int16_t *i) {
  bool ok = b_read(f, i, sizeof(int16_t));
  *i = be16toh(*i);
  return ok;
}
bool serde_readb_32(bytebuffer_t *f, int32_t *i) {
  bool ok = b_read(f, i, sizeof(int32_t));
  *i = be32toh(*i);
  return ok;
}
bool serde_readb_64(bytebuffer_t *f, int64_t *i) {
  bool ok = b_read(f, i, sizeof(int64_t));
  *i = be64toh(*i);
  return ok;
}

bool serde_writeb_u8(bytebuffer_t *f, uint8_t i) {
  return b_write(f, &i, sizeof(uint8_t));
}
bool serde_writeb_u16(bytebuffer_t *f, uint16_t i) {
  i = htobe16(i);
  return b_write(f, &i, sizeof(uint16_t));
}
bool serde_writeb_u32(bytebuffer_t *f, uint32_t i) {
  i = htobe32(i);
  return b_write(f, &i, sizeof(uint32_t));
}
bool serde_writeb_u64(bytebuffer_t *f, uint64_t i) {
  i = htobe64(i);
  return b_write(f, &i, sizeof(uint64_t));
}
bool serde_readb_u8(bytebuffer_t *f, uint8_t *i) {
  bool ok = b_read(f, i, sizeof(uint8_t));
  return ok;
}
bool serde_readb_u16(bytebuffer_t *f, uint16_t *i) {
  bool ok = b_read(f, i, sizeof(uint16_t));
  *i = be16toh(*i);
  return ok;
}
bool serde_readb_u32(bytebuffer_t *f, uint32_t *i) {
  bool ok = b_read(f, i, sizeof(uint32_t));
  *i = be32toh(*i);
  return ok;
}
bool serde_readb_u64(bytebuffer_t *f, uint64_t *i) {
  bool ok = b_read(f, i, sizeof(uint64_t));
  *i = be64toh(*i);
  return ok;
}

#ifdef __STDC_IEC_559__
bool serde_writeb_d(bytebuffer_t *f, double i) {
  return b_write(f, &i, sizeof(double));
}
bool serde_readb_d(bytebuffer_t *f, double *i) {
  return b_read(f, i, sizeof(double));
}
#else
#error libserde requires IEEE 775 floating point number support.
#endif /*__STDC_IEC_559__ */
