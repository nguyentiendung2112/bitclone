//
// Created by Dung on 25/9/25.
//

#ifndef HASHMAP_H
#define HASHMAP_H

#define DEFAULT_NUMBER_OF_BUCKETS 64

template<typename T>
struct Node {
  T data;
  int key;
  Node *next = nullptr;
};

template<typename V>
class HashMap {
  int number_of_buckets;
  Node<V> **buckets;
  public:
    HashMap(int numberOfBuckets = DEFAULT_NUMBER_OF_BUCKETS) {
      this->number_of_buckets = numberOfBuckets;
      this->buckets = new Node<V> * [this->number_of_buckets];
    }

    void put(int key, V value);
    void remove(int key);
    V get(int key);
    V getOrDefault(int key, V default_value);
    ~HashMap() {
      for (int i = 0; i < this->number_of_buckets; i++) {
        delete this->buckets[i];
      }
      delete this->buckets;
    }
};



#endif //HASHMAP_H
