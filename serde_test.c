#include "libserde.h"
#include "testing/minunit/minunit.h"

#include <stdio.h>

#define COMPARE(type, got, want)    \
  do {                              \
    type _g = (got);         \
    type _w = (want);       \
    if (_g != _w) {                 \
      mu_assert_error(              \
          "Found '%Lf' but expected: %Lf", \
           (long double)_g, (long double) _w);     \
    }                               \
  } while (0)

#define NO_ERR(expr)                        \
  do {                                      \
    bool __val = (expr);                    \
    (void) __val;                           \
    if (serde_error()) {                    \
      mu_assert_error("error: %s", #expr);  \
      goto cleanup;                         \
    }                                       \
  } while (0)

mu_test(generics_supported_and_correct) {
  char buf[1024] = {0};
  FILE* mem = fmemopen(buf, sizeof(buf), "r+");

  mu_expect(mem != NULL);

  int8_t three = 3;
  int16_t two_twelve = 1 << 12;
  int32_t two_twentythree = 1 << 23;
  int64_t two_fourtyfour = 1ll << 44;
  double almost_two = 2.1f;
  uint8_t seven = 7;
  uint16_t two_fourteen = 1 << 14;
  uint32_t two_nineteen = 1 << 19;
  uint64_t two_fiftythree = 1ll << 53;

  serde_start();
  NO_ERR(serde_do(write, mem, three));
  NO_ERR(serde_do(write, mem, two_twelve));
  NO_ERR(serde_do(write, mem, two_twentythree));
  NO_ERR(serde_do(write, mem, two_fourtyfour));
  NO_ERR(serde_write_d(mem, almost_two));
  NO_ERR(serde_do(write, mem, seven));
  NO_ERR(serde_do(write, mem, two_fourteen));
  NO_ERR(serde_do(write, mem, two_nineteen));
  NO_ERR(serde_do(write, mem, two_fiftythree));
  if (serde_error()) {
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
  double got_almost_two = 0;
  uint8_t got_seven = 0;
  uint16_t got_two_fourteen = 0;
  uint32_t got_two_nineteen = 0;
  uint64_t got_two_fiftythree = 0;
  NO_ERR(serde_do(read, mem, &got_three));
  NO_ERR(serde_do(read, mem, &got_two_twelve));
  NO_ERR(serde_do(read, mem, &got_two_twentythree));
  NO_ERR(serde_do(read, mem, &got_two_fourtyfour));
  NO_ERR(serde_read_d(mem, &got_almost_two));
  NO_ERR(serde_do(read, mem, &got_seven));
  NO_ERR(serde_do(read, mem, &got_two_fourteen));
  NO_ERR(serde_do(read, mem, &got_two_nineteen));
  NO_ERR(serde_do(read, mem, &got_two_fiftythree));
  if (serde_error()) {
    mu_assert_error("Failed to read data back.");
    goto cleanup;
  }

  COMPARE(int8_t, got_three, three);
  COMPARE(int16_t, got_two_twelve, two_twelve);
  COMPARE(int32_t, got_two_twentythree, two_twentythree);
  COMPARE(int64_t, got_two_fourtyfour, two_fourtyfour);
  COMPARE(double, got_almost_two, almost_two);
  COMPARE(uint8_t, got_seven, seven);
  COMPARE(uint16_t, got_two_fourteen, two_fourteen);
  COMPARE(uint32_t, got_two_nineteen, two_nineteen);
  COMPARE(uint64_t, got_two_fiftythree, two_fiftythree);

cleanup:
  fclose(mem);
}
