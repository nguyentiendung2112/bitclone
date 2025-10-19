//
// Created by Dung on 14/9/25.
//

#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <string>

#include "DoublyLinkedList.h"
#include "HashMap.h"

#define DEFAULT_CAPACITY 64
// LRU can be created by doubly linked listt
template<typename V>
class LRUCache {
  size_t size = 0;
  size_t capacity;
  HashMap<DoublyLinkedListNode<V>*>* hashmap;
  DoublyLinkedList<V>* doublyLinkedList;
  void evict();

  public:
    explicit LRUCache(size_t capacity = DEFAULT_CAPACITY) {
      this->capacity = capacity;
      this->hashmap = new HashMap<DoublyLinkedListNode<V>*>();
      this->doublyLinkedList = new DoublyLinkedList<V>();
    }
    ~LRUCache() {
      delete this->hashmap;
      delete this->doublyLinkedList;
    }

    V get(int key);
    void put(int key, V value);
    void remove(int key);
    bool has(int key);

    // debug
    std::string str();
};



#endif //LRUCACHE_H
