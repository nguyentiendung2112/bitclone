//
// Created by Dung on 25/9/25.
//

#ifndef HASHMAP_H
#define HASHMAP_H

#define DEFAULT_NUMBER_OF_BUCKETS 64

#include <cstddef>
#include <cstdint>
#include <stdexcept>

template <typename K, typename T>
struct HashMapNode {
  T data;
  K key;
  HashMapNode* next = nullptr;
};

template <typename K, typename V>
class HashMap {
  std::uint64_t number_of_buckets;
  HashMapNode<K, V>** buckets;

 public:
  explicit HashMap(std::uint64_t numberOfBuckets = DEFAULT_NUMBER_OF_BUCKETS) {
    this->number_of_buckets = numberOfBuckets;
    this->buckets = new HashMapNode<K, V>*[this->number_of_buckets]();
  }

  void put(K key, V value);
  void remove(K key);
  bool has(K key);
  V get(K key);
  V getOrDefault(K key, V default_value);
  void clear();

  ~HashMap() {
    for (std::uint64_t i = 0; i < this->number_of_buckets; ++i) {
      HashMapNode<K, V>* current = this->buckets[i];
      while (current != nullptr) {
        HashMapNode<K, V>* temp = current;
        current = current->next;
        delete temp;
      }
    }
    delete[] this->buckets;
  }
};

template <typename K, typename V>
void HashMap<K, V>::put(K key, V value) {
  std::uint64_t hash = std::hash<K>{}(key) % number_of_buckets;
  auto* node = new HashMapNode<K, V>;
  node->data = value;
  node->key = key;
  node->next = this->buckets[hash];
  this->buckets[hash] = node;
}

template <typename K, typename V>
void HashMap<K, V>::remove(K key) {
  std::uint64_t hash = std::hash<K>{}(key) % number_of_buckets;
  HashMapNode<K, V>* head = this->buckets[hash];
  HashMapNode<K, V>* prev = nullptr;
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

template <typename K, typename V>
V HashMap<K,V>::get(K key) {
  std::uint64_t hash = std::hash<K>{}(key) % number_of_buckets;
  HashMapNode<K, V>* head = this->buckets[hash];
  while (head != nullptr) {
    if (head->key == key) {
      return head->data;
    }
    head = head->next;
  }
  throw std::out_of_range("Key not found");
}

template <typename K, typename V>
V HashMap<K, V>::getOrDefault(K key, V default_value) {
  try {
    return get(key);
  } catch (const std::out_of_range& e) {
    (void)e;  // silence unused variable warnings
    return default_value;
  }
}

template <typename K, typename V>
bool HashMap<K, V>::has(K key) {
  auto hash = std::hash<K>{}(key) % number_of_buckets;
  HashMapNode<K, V>* head = this->buckets[hash];
  while (head != nullptr) {
    if (head->key == key) {
      return true;
    }
    head = head->next;
  }
  return false;
}

template <typename K, typename V>
void HashMap<K, V>::clear() {
  for (std::uint64_t i = 0; i < this->number_of_buckets; ++i) {
    HashMapNode<K, V>* current = this->buckets[i];
    while (current != nullptr) {
      HashMapNode<K, V>* temp = current;
      current = current->next;
      delete temp;
    }
    this->buckets[i] = nullptr;
  }
}

#endif  // HASHMAP_H
