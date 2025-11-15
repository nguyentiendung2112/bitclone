//
// Created by Dung on 14/9/25.
//

#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <string>

#include "DoublyLinkedList.h"
#include "HashMap.h"

inline constexpr size_t DEFAULT_CAPACITY = 64;

template<typename V>
class LRUCache {
  size_t size = 0;
  size_t capacity;
  HashMap<std::uint64_t, DoublyLinkedListNode<V>*>* hashmap;
  DoublyLinkedList<V>* doublyLinkedList;
  void evict();

  public:
    explicit LRUCache(size_t capacity = DEFAULT_CAPACITY) {
      this->capacity = capacity;
      this->hashmap = new HashMap<std::uint64_t, DoublyLinkedListNode<V>*>();
      this->doublyLinkedList = new DoublyLinkedList<V>();
    }
    ~LRUCache() {
      delete this->hashmap;
      delete this->doublyLinkedList;
    }

    V get(uint64_t key);
    void put(uint64_t key, V value);
    void remove(uint64_t key);
    bool has(uint64_t key);

    // debug
    std::string str();
};



#endif //LRUCACHE_H
