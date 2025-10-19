//
// Created by Dung on 18/10/25.
//

#include "gtest/gtest.h"
#include "src/lru_cache/LRUCache.h"

namespace {

  TEST(LRUCache, put_and_get) {
    auto lru_cache = LRUCache<int>();

    lru_cache.put(1, 2);
    lru_cache.put(2, 1);

    EXPECT_EQ(2, lru_cache.get(1));
    EXPECT_EQ(1, lru_cache.get(2));
    EXPECT_EQ(lru_cache.str(), "2:1 -> 1:2");
  }

  TEST(LRUCache, put_and_remove) {
    auto lru_cache = LRUCache<int>();
    lru_cache.put(1, 2);
    lru_cache.put(2, 1);
    lru_cache.remove(1);
    EXPECT_EQ(lru_cache.str(), "2:1");
  }

TEST(LRUCache, test_evict) {
    auto lru_cache = LRUCache<int>(3);
    lru_cache.put(1, 2);
    lru_cache.put(2, 1);
    lru_cache.put(3, 3);
    lru_cache.put(4, 4);
    EXPECT_EQ(lru_cache.str(), "4:4 -> 3:3 -> 2:1");
    EXPECT_FALSE(lru_cache.has(1));
  }

TEST(LRUCache, test_recent_used) {
    auto lru_cache = LRUCache<int>(3);
    lru_cache.put(1, 2);
    lru_cache.put(2, 1);
    lru_cache.put(3, 3);
    lru_cache.put(4, 4);
    lru_cache.get(2);
    EXPECT_EQ(lru_cache.str(), "2:1 -> 4:4 -> 3:3");
  }
}
