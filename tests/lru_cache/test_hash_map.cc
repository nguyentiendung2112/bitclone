//
// Created by Dung on 15/10/25.
//
#include "gtest/gtest.h"
#include "src/lru_cache/HashMap.h"

namespace {

TEST(HashMap, put) {
  auto hash_map = HashMap<int>();
  hash_map.put(1, 10);
  EXPECT_EQ(hash_map.get(1), 10);
}
}
