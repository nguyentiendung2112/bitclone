//
// Created by Dung on 14/9/25.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <iostream>
#include <__ostream/basic_ostream.h>

#include "../byte_buffer/BytesBuffer.h"

template <typename T>
struct Node {
  T data;
  Node *prev = nullptr;
  Node *next = nullptr;
};

template <typename T>
class DoublyLinkedList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    size_t size = 0;
  public:
    Node<T>* addTail(const T& data);
    Node<T>* addHead(const T& data);
    void removeHead();
    void removeTail();
    void moveToHead(Node<T>* node);
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



#endif //DOUBLYLINKEDLIST_H
