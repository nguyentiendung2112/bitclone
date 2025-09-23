//
// Created by Dung on 14/9/25.
//

#ifndef LRUCACHE_H
#define LRUCACHE_H
#include "../byte_buffer/BytesBuffer.h"

// LRU can be created by doubly linked listt

class LRUCache {
  public:
    BytesBuffer get(uint64_t key);
    void put(uint64_t key, BytesBuffer value);
    void remove(uint64_t key);
};



#endif //LRUCACHE_H
