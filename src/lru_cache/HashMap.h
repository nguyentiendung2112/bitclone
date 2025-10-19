//
// Created by Dung on 25/9/25.
//

#ifndef HASHMAP_H
#define HASHMAP_H

#define DEFAULT_NUMBER_OF_BUCKETS 64
#include <stdexcept>

template<typename T>
struct HashMapNode {
  T data;
  uint64_t key;
  HashMapNode *next = nullptr;
};

template<typename V>
class HashMap {
  uint64_t number_of_buckets;
  HashMapNode<V> **buckets;

  public:
    explicit HashMap(int numberOfBuckets = DEFAULT_NUMBER_OF_BUCKETS) {
      this->number_of_buckets = numberOfBuckets;
      this->buckets = new HashMapNode<V> *[this->number_of_buckets]();
    }

    void put(uint64_t key, V value);
    void remove(uint64_t key);
    bool has(uint64_t key);
    V get(uint64_t key);
    V getOrDefault(uint64_t key, V default_value);

    ~HashMap() {
      for (uint64_t i = 0; i < this->number_of_buckets; ++i) {
        HashMapNode<V>* current = this->buckets[i];
        while (current != nullptr) {
          HashMapNode<V>* temp = current;
          current = current->next;
          delete temp;
        }
      }
      delete[] this->buckets;
    }
};

template<typename V>
void HashMap<V>::put(uint64_t key, V value) {
  uint64_t hash = key % number_of_buckets;
  auto *node = new HashMapNode<V>;
  node->data = value;
  node->key = key;
  node->next = this->buckets[hash];
  this->buckets[hash] = node;
}
template<typename V>
void HashMap<V>::remove(uint64_t key) {
  uint64_t hash = key % number_of_buckets;
  HashMapNode<V> *head = this->buckets[hash];
  HashMapNode<V> *prev = nullptr;
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
V HashMap<V>::get(uint64_t key) {
  uint64_t hash = key % number_of_buckets;
  HashMapNode<V> *head = this->buckets[hash];
  while (head != nullptr) {
    if (head->key == key) {
      return head->data;
    }
    head = head->next;
  }
  throw std::out_of_range("Key not found");
}


template<typename V>
V HashMap<V>::getOrDefault(uint64_t key, V default_value) {
  try {
    return get(key);
  } catch (const std::out_of_range &e) {
    return default_value;
  }
}

template<typename V>
bool HashMap<V>::has(uint64_t key) {
  uint64_t hash = key % number_of_buckets;
  HashMapNode<V> *head = this->buckets[hash];
  while (head != nullptr) {
    if (head->key == key) {
      return true;
    }
    head = head->next;
  }
  return false;
}


#endif //HASHMAP_H
