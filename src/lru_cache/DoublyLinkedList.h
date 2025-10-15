//
// Created by Dung on 14/9/25.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "../byte_buffer/BytesBuffer.h"

template <typename T>
struct Node {
  T* data;
  Node *prev = nullptr;
  Node *next = nullptr;
};

template <typename T>
class DoublyLinkedList {
  private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
  public:
    Node<T>* addTail(const BytesBuffer& data);
    Node<T>* addHead(const BytesBuffer& data);
    void removeHead();
    void removeTail();
    void moveToHead(Node<T>* node) const;
    // for debug
    void print();
};



#endif //DOUBLYLINKEDLIST_H
