//
// Created by Dung on 14/9/25.
//

#include "DoublyLinkedList.h"

template <typename T>
Node<T>* DoublyLinkedList<T>::addHead(const BytesBuffer &data) {
  const auto node = new Node<T>();
  node->data = data;

  if (head == nullptr && tail == nullptr) {
    head = tail = node;
  } else {
    if (head == nullptr || tail == nullptr) {
      throw std::runtime_error("head is nullptr XOR tail is nullptr!! check your code");
    }
    tail->next = node;
    node->prev = tail;
    node->next = head;
    head = node;
  }
  return node;
}

template <typename T>
Node<T> *DoublyLinkedList<T>::addTail(const BytesBuffer &data) {
  const auto node = new Node<T>();
  node->data = data;

  if (head == nullptr && tail == nullptr) {
    head = tail = node;
  } else {
    if (head == nullptr || tail == nullptr) {
      throw std::runtime_error("head is nullptr XOR tail is nullptr!! check your code");
    }
    tail->next = node;
    node->prev = tail;
    node->next = head;
    tail = node;
  }
  return node;
}

template <typename T>
void DoublyLinkedList<T>::removeHead() {
  if (head != nullptr) {
    const Node<T> *node = head;
    head = head->next;
    delete node;
  }
}

template <typename T>
void DoublyLinkedList<T>::removeTail() {
  if (tail != nullptr) {
    const Node<T> *node = tail;
    tail = tail->prev;
    delete node;
  }
}

template <typename T>
void DoublyLinkedList<T>::moveToHead(Node<T> *node) const {
  const auto prev = node->prev;
  if (prev != nullptr) {
    prev->next = node->next;
  }
  if (const auto next = node->next; next != nullptr) {
    next->prev = prev;
  }

  node->next = head;
  node->prev = nullptr;
}

