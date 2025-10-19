//
// Created by Dung on 14/9/25.
//

#include "DoublyLinkedList.h"

#include <iostream>
#include <string>

template <typename T>
DoublyLinkedListNode<T>* DoublyLinkedList<T>::addHead(const T& data, int key) {
  const auto node = new DoublyLinkedListNode<T>(key, data);

  if (head == nullptr && tail == nullptr) {
    head = tail = node;
  } else {
    if (head == nullptr || tail == nullptr) {
      throw std::runtime_error("head is nullptr XOR tail is nullptr!! check your code");
    }
    head->prev = node;
    node->next = head;
    head = node;
  }
  size++;
  return node;
}

template <typename T>
DoublyLinkedListNode<T> *DoublyLinkedList<T>::addTail(const T& data, int key) {
  const auto node = new DoublyLinkedListNode<T>(key, data);

  if (head == nullptr && tail == nullptr) {
    head = tail = node;
  } else {
    if (head == nullptr || tail == nullptr) {
      throw std::runtime_error("head is nullptr XOR tail is nullptr!! check your code");
    }
    tail->next = node;
    node->prev = tail;
    tail = node;
  }
  size++;
  return node;
}

template <typename T>
void DoublyLinkedList<T>::removeHead() {
  if (!head) {
    return;
  }
  const DoublyLinkedListNode<T> *node = head;

  head = node->next;
  if (head != nullptr) {
    head->prev = nullptr;
  } else {
    tail = nullptr;
  }

  delete node;
  size--;
}

template <typename T>
void DoublyLinkedList<T>::removeTail() {
  if (tail != nullptr) {
    const DoublyLinkedListNode<T> *node = tail;
    auto prev = tail->prev;
    if (prev != nullptr) {
      prev->next = nullptr;
    }
    tail = tail->prev;
    if (tail == nullptr) {
      head = nullptr;
    }
    delete node;
    size--;
  }
}

template <typename T>
void DoublyLinkedList<T>::moveToHead(DoublyLinkedListNode<T> *node) {
  if (node == nullptr)
    return;
  auto prev = node->prev;
  auto next = node->next;
  if (prev == nullptr)
    return;

  prev->next = next;
  if (next != nullptr) {
    next->prev = node->prev;
  } else {
    tail = prev;
  }
  head->prev = node;
  node->next = head;
  node->prev = nullptr;
  head = node;
}

template<typename T>
std::string DoublyLinkedList<T>::str() {
  std::string result = "";
  const DoublyLinkedListNode<T> *node = head;
  if (head == nullptr)
    return result;
  while (node != tail) {
    result += dl_list::to_string(node->key)+":"+ dl_list::to_string(node->data) + " -> ";
    node = node->next;
  }
  result +=dl_list::to_string(node->key)+ ":" + dl_list::to_string(node->data);
  return result;
}

template<typename T>
std::string DoublyLinkedList<T>::strReverse() {
  std::string result = "";
  const DoublyLinkedListNode<T> *node = tail;
  if (tail == nullptr)
    return result;
  while (node != head) {
    result += dl_list::to_string(node->data) + " -> ";
    node = node->prev;
  }
  result += dl_list::to_string(node->data);
  return result;
}



template<typename T>
void DoublyLinkedList<T>::print() {
  std::cout << str() << std::endl;
}

template<typename T>
DoublyLinkedListNode<T> * DoublyLinkedList<T>::getTail() {
  return this -> tail;
}

template class DoublyLinkedList<int>;
template class DoublyLinkedList<BytesBuffer>;
