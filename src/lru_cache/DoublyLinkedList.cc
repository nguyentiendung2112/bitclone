//
// Created by Dung on 14/9/25.
//

#include "DoublyLinkedList.h"

Node *DoublyLinkedList::addHead(const BytesBuffer& data) {
  const auto node = new Node();
  node->data = data;

  if (head == nullptr && tail == nullptr) {
    head = tail = node;
  } else {
    if (head == nullptr || tail == nullptr) {
      throw std::runtime_error("head is nullptr XOR tail is nullptr!! check your code");
    }
    tail-> next = node;
    node->prev = tail;
    node->next = head;
    head = node;
  }
  return node;
}


Node *DoublyLinkedList::addTail(const BytesBuffer& data) {
  const auto node = new Node();
  node->data = data;

  if (head == nullptr && tail == nullptr) {
    head = tail = node;
  } else {
    if (head == nullptr || tail == nullptr) {
      throw std::runtime_error("head is nullptr XOR tail is nullptr!! check your code");
    }
    tail-> next = node;
    node->prev = tail;
    node->next = head;
    tail = node;

  }
  return node;
}

void DoublyLinkedList::removeHead() {
  if (head != nullptr) {
    const Node *node = head;
    head = head->next;
    delete node;
  }
}

void DoublyLinkedList::removeTail() {
  if (tail != nullptr) {
    const Node *node = tail;
    tail = tail->prev;
    delete node;
  }
}

void DoublyLinkedList::moveToHead(const Node* node) {
  auto prev = node->prev;
}