cc_binary(
    name = "graph-db",
    srcs = glob([
        "src/**/*.h",
        "src/**/*.cc",
    ]),
)

cc_library(
    name = "cpp-dependencies",
    srcs = glob([
        "src/**/*.h",
        "src/**/*.cc",
    ]),
    hdrs = glob([
        "src/**/*.h",
    ]),
    visibility = ["//visibility:public"],
    deps = [],
)

cc_library(
    name = "hashmap",
    hdrs = [
        "src/lru_cache/HashMap.h",
    ],
    deps = [],
)

cc_test(
    name = "test-hashmap",
    srcs = glob([
        "tests/lru_cache/test_hash_map.cc",
    ]),
    deps = [
        ":hashmap",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
