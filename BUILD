cc_library(
  name = "serde",
  srcs = ["libserde.c"],
  hdrs = ["libserde.h"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "serde_test",
  srcs = ["serde_test.c"],
  deps = [
    ":serde",
    "//testing/minunit",
  ],
)
