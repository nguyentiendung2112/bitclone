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
  int key;
  HashMapNode *next = nullptr;
};

template<typename V>
class HashMap {
  int number_of_buckets;
  HashMapNode<V> **buckets;

  public:
    explicit HashMap(int numberOfBuckets = DEFAULT_NUMBER_OF_BUCKETS) {
      this->number_of_buckets = numberOfBuckets;
      this->buckets = new HashMapNode<V> *[this->number_of_buckets];
    }

    void put(int key, V value);
    void remove(int key);
    bool has(int key);
    V get(int key);
    V getOrDefault(int key, V default_value);

    ~HashMap() {
      for (int i = 0; i < this->number_of_buckets; ++i) {
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
void HashMap<V>::put(int key, V value) {
  int hash = key % number_of_buckets;
  auto *node = new HashMapNode<V>;
  node->data = value;
  node->key = key;
  node->next = this->buckets[hash];
  this->buckets[hash] = node;
}
template<typename V>
void HashMap<V>::remove(int key) {
  int hash = key % number_of_buckets;
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
V HashMap<V>::get(int key) {
  int hash = key % number_of_buckets;
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
V HashMap<V>::getOrDefault(int key, V default_value) {
  try {
    return get(key);
  } catch (const std::out_of_range &e) {
    return default_value;
  }
}

template<typename V>
bool HashMap<V>::has(int key) {
  int hash = key % number_of_buckets;
  HashMapNode<V> *head = this->buckets[hash];
  while (head != nullptr) {
    if (head->key == key) {
      return true;
    }
  }
  return false;
}


#endif //HASHMAP_H
