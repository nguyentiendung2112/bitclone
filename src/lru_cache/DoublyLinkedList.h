//
// Created by Dung on 14/9/25.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <iostream>

#include "../byte_buffer/BytesBuffer.h"

template<typename T>
struct DoublyLinkedListNode {
  int key;
  T data;
  DoublyLinkedListNode *prev = nullptr;
  DoublyLinkedListNode *next = nullptr;

  DoublyLinkedListNode(int key, T data) {
    this->key = key;
    this->data = data;
  }
};

template<typename T>
class DoublyLinkedList {
  DoublyLinkedListNode<T> *head = nullptr;
  DoublyLinkedListNode<T> *tail = nullptr;
  size_t size = 0;

  public:
    DoublyLinkedListNode<T> *addTail(const T &data, int key = 0);
    DoublyLinkedListNode<T> *addHead(const T &data, int key = 0);
    DoublyLinkedListNode<T> *getTail();
    void removeHead();
    void removeTail();
    void moveToHead(DoublyLinkedListNode<T> *node);
    // for debug
    void print();
    std::string str();
    std::string strReverse(); //for debug reverse linkedlist

    ~DoublyLinkedList() {
      while (head != nullptr || tail != nullptr) {
        removeHead();
      }
    }
};

namespace dl_list {
inline std::string to_string(BytesBuffer data) {
  return "BytesBuffer";
}

inline std::string to_string(int data) {
  return std::to_string(data);
}
}

#endif //DOUBLYLINKEDLIST_H
