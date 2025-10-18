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

cc_test(
    name = "test-hashmap",
    srcs = glob([
        "tests/lru_cache/test_hash_map.cc",
    ]),
    deps = [
        ":cpp-dependencies",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test-doubly-linked-list",
    srcs = glob([
        "tests/lru_cache/test_doubly_linked_list.cc",
    ]),
    deps = [
        ":cpp-dependencies",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
