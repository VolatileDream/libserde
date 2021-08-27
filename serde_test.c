#include "libserde.h"
#include "libs/c/minunit/minunit.h"

#include <stdio.h>

#define COMPARE(type, got, want)    \
  do {                              \
    type _g = (got);         \
    type _w = (want);       \
    if (_g != _w) {                 \
      mu_assert_error(              \
          "Found '%ld' but expected: %ld", \
           (int64_t)_g, (int64_t) _w);     \
    }                               \
  } while (0)


mu_test(generics_supported_and_correct) {
  char buf[1024] = {0};
  FILE* mem = fmemopen(buf, sizeof(buf), "r+");

  mu_expect(mem != NULL);

  int8_t three = 3;
  int16_t two_twelve = 1 << 12;
  int32_t two_twentythree = 1 << 23;
  int64_t two_fourtyfour = 1ll << 44;
  uint8_t seven = 7;
  uint16_t two_fourteen = 1 << 14;
  uint32_t two_nineteen = 1 << 19;
  uint64_t two_fiftythree = 1ll << 53;

  serde_start();
  serde_do(write, mem, three);
  serde_do(write, mem, two_twelve);
  serde_do(write, mem, two_twentythree);
  serde_do(write, mem, two_fourtyfour);
  serde_do(write, mem, seven);
  serde_do(write, mem, two_fourteen);
  serde_do(write, mem, two_nineteen);
  serde_do(write, mem, two_fiftythree);
  if (serde_failure()) {
    mu_assert_error("Failed to write out data.");
    goto cleanup;
  }

  if (fseek(mem, 0, SEEK_SET)) {
    mu_assert_error("Could not seek to start of test buffer.");
    goto cleanup;
  }
  int8_t got_three = 0;
  int16_t got_two_twelve = 0;
  int32_t got_two_twentythree = 0;
  int64_t got_two_fourtyfour = 0;
  uint8_t got_seven = 0;
  uint16_t got_two_fourteen = 0;
  uint32_t got_two_nineteen = 0;
  uint64_t got_two_fiftythree = 0;
  serde_do(read, mem, &got_three);
  serde_do(read, mem, &got_two_twelve);
  serde_do(read, mem, &got_two_twentythree);
  serde_do(read, mem, &got_two_fourtyfour);
  serde_do(read, mem, &got_seven);
  serde_do(read, mem, &got_two_fourteen);
  serde_do(read, mem, &got_two_nineteen);
  serde_do(read, mem, &got_two_fiftythree);
  if (serde_failure()) {
    mu_assert_error("Failed to read data back.");
    goto cleanup;
  }

  COMPARE(int8_t, got_three, three);
  COMPARE(int16_t, got_two_twelve, two_twelve);
  COMPARE(int32_t, got_two_twentythree, two_twentythree);
  COMPARE(int64_t, got_two_fourtyfour, two_fourtyfour);
  COMPARE(uint8_t, got_seven, seven);
  COMPARE(uint16_t, got_two_fourteen, two_fourteen);
  COMPARE(uint32_t, got_two_nineteen, two_nineteen);
  COMPARE(uint64_t, got_two_fiftythree, two_fiftythree);

cleanup:
  fclose(mem);
}
