//
// Created by Dung on 14/9/25.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "../byte_buffer/BytesBuffer.h"


struct Node {
  BytesBuffer data;
  Node *prev = nullptr;
  Node *next = nullptr;
};

class DoublyLinkedList {
  private:
    Node* head = nullptr;
    Node* tail = nullptr;
  public:
    Node* addTail(const BytesBuffer& data);
    Node* addHead(const BytesBuffer& data);
    void removeHead();
    void removeTail();
    void moveToHead(const Node* node);
    // for debug
    void print();
};



#endif //DOUBLYLINKEDLIST_H
