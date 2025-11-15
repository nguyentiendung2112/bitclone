//
// Created by Dung on 14/9/25.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <string>


template <typename T>
struct DoublyLinkedListNode {
  std::uint64_t key;
  T data;
  DoublyLinkedListNode* prev = nullptr;
  DoublyLinkedListNode* next = nullptr;

  DoublyLinkedListNode(std::uint64_t key, T data) : key(key), data(data) {}
};

template <typename T>
class DoublyLinkedList {
  DoublyLinkedListNode<T>* head = nullptr;
  DoublyLinkedListNode<T>* tail = nullptr;
  std::size_t size = 0;

 public:
  DoublyLinkedListNode<T>* addTail(const T& data, std::uint64_t key = 0);
  DoublyLinkedListNode<T>* addHead(const T& data, std::uint64_t key = 0);
  DoublyLinkedListNode<T>* getTail();
  void removeHead();
  void removeTail();
  void moveToHead(DoublyLinkedListNode<T>* node);

  // For debug
  void print();
  std::string str();
  std::string strReverse();  // For debug reverse linkedlist

  ~DoublyLinkedList() {
    while (head != nullptr || tail != nullptr) {
      removeHead();
    }
  }
};

namespace dl_list {
inline std::string to_string(std::uint64_t data) { return std::to_string(data); }
inline std::string to_string(int data) { return std::to_string(data); }
}  // namespace dl_list

#endif  // DOUBLYLINKEDLIST_H
