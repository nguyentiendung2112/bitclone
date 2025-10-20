//
// Created by Dung on 14/9/25.
//

#include "LRUCache.h"
#include "../byte_buffer/BytesBuffer.h"

template<typename V>
V LRUCache<V>::get(uint64_t key) {
  if (this->hashmap->has(key)) {
    auto node = this->hashmap->get(key);
    doublyLinkedList->moveToHead(node);
    return node->data;
  }
  throw std::out_of_range("Key not found");
}
template<typename V>
void LRUCache<V>::put(uint64_t key, V value) {
  if (this->hashmap->has(key)) {
    auto doublyLinkedListNode = hashmap->get(key);
    doublyLinkedListNode->data = value;
    doublyLinkedList->moveToHead(doublyLinkedListNode);
  } else {
    auto doublyLinkedListNode = doublyLinkedList->addHead(value, key);
    hashmap->put(key, doublyLinkedListNode);
    if (size == capacity) {
      this -> evict();
    } else {
      ++ size;
    }
  }
}


template<typename V>
void LRUCache<V>::remove(uint64_t key) {
  auto doublyLinkedListNode = hashmap->get(key);
  hashmap->remove(key);
  doublyLinkedList->moveToHead(doublyLinkedListNode);
  doublyLinkedList->removeHead();
  size-- ;
}

template<typename V>
void LRUCache<V>::evict() {
    auto currentTail = doublyLinkedList->getTail();
    hashmap->remove(currentTail->key);
    doublyLinkedList->removeTail();
}

template<typename V>
std::string LRUCache<V>::str() {
  return doublyLinkedList->str();
}

template<typename V>
bool LRUCache<V>::has(uint64_t key) {
  return this->hashmap->has(key);
}

template class LRUCache<BytesBuffer>;
template class LRUCache<int>;
