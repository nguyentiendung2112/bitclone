//
// Created by Dung on 14/9/25.
//

#ifndef LRUCACHE_H
#define LRUCACHE_H
#include "DoublyLinkedList.h"
#include "HashMap.h"
#include "../byte_buffer/BytesBuffer.h"


#define DEFAULT_CAPACITY 64
// LRU can be created by doubly linked listt
template<typename V>
class LRUCache {
  size_t size = 0;
  size_t capacity;
  HashMap<DoublyLinkedListNode<V>*> hashmap;
  DoublyLinkedList<V> doublyLinkedList;
  void evict();

  public:
    explicit LRUCache(size_t capacity = DEFAULT_CAPACITY) {
      this->capacity = capacity;
      this->hashmap = HashMap<DoublyLinkedListNode<V>*>();
      this->doublyLinkedList = DoublyLinkedList<V>();
    }

    V get(int key);
    void put(int key, V value);
    void remove(int key);

    // debug
    std::string str();
};



#endif //LRUCACHE_H
