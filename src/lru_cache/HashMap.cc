//
// Created by Dung on 25/9/25.
//

#include "HashMap.h"

#include <stdexcept>

template<typename V>
void HashMap<V>::put(int key, V value) {
  int hash = key % number_of_buckets;
  Node<V> node;
  node.data = value;
  node.next = this->buckets[hash];
  this->buckets[hash] = &node;

}
template<typename V>
void HashMap<V>::remove(int key) {
  int hash = key % number_of_buckets;
  Node<V>* head = this->buckets[hash];
  Node<V>* prev = nullptr;
  while (head != nullptr) {
    if (head->key == key) {
      if (prev == nullptr) {
        this->buckets[hash] = head->next;
      } else {
        prev->next = head->next;
      }
    }
    prev = head;
    head = head->next;

  }

}
template<typename V>
V HashMap<V>::get(int key) {
  int hash = key % number_of_buckets;
  Node<V>* head = this->buckets[hash];
  while (head != nullptr) {
    if (head->key == key) {
      return head->data;
    }
  }
  throw std::out_of_range("Key not found");
}


template<typename V>
V HashMap<V>::getOrDefault(int key, V default_value) {
  try {
    return get(key);
  } catch (const std::out_of_range &e) {
    return default_value;
  }
}
