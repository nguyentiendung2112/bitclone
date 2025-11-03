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
  hash_map.put(2, 20);
  EXPECT_EQ(hash_map.get(2), 20);
  hash_map.put(2, 30);
  EXPECT_EQ(hash_map.get(2), 30);
}

TEST(HashMap, get) {
  auto hash_map = HashMap<int>();
  hash_map.put(1, 10);
  EXPECT_EQ(hash_map.get(1), 10);
  hash_map.put(2, 20);
  EXPECT_EQ(hash_map.get(2), 20);
}


TEST(HashMap, remove) {
  auto hash_map = HashMap<int>();
  hash_map.put(1, 10);
  EXPECT_EQ(hash_map.get(1), 10);
  hash_map.put(2, 20);
  EXPECT_EQ(hash_map.get(2), 20);
  hash_map.remove(2);
  EXPECT_FALSE(hash_map.has(2));
}


TEST(HashMap, has) {
  auto hash_map = HashMap<int>();
  hash_map.put(1, 10);
  hash_map.put(2, 20);
  EXPECT_TRUE(hash_map.has(1));
  EXPECT_TRUE(hash_map.has(2));
  hash_map.remove(2);
  EXPECT_FALSE(hash_map.has(2));
}
}
