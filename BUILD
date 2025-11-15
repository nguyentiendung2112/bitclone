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
        "tests/cpp/lru_cache/test_hash_map.cc",
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
        "tests/cpp/lru_cache/test_doubly_linked_list.cc",
    ]),
    deps = [
        ":cpp-dependencies",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test-lru-cache",
    srcs = glob([
        "tests/cpp/lru_cache/test_lru_cache.cc",
    ]),
    deps = [
        ":cpp-dependencies",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test-log-reader",
    srcs = [
        "tests/cpp/file_handler/test_log_reader.cc",
    ],
    data = ["tests/resources/file000"],
    deps = [
        ":cpp-dependencies",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test-keydir",
    srcs = glob([
        "tests/cpp/keydir/test_keydir.cc",
    ]),
    deps = [
        ":cpp-dependencies",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test-all",
    srcs = glob([
        "tests/cpp/**/*.cc",
    ]),
    deps = [
        ":cpp-dependencies",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
