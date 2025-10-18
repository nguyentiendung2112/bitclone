//
// Created by Dung on 17/10/25.
//

#include "gtest/gtest.h"
#include "src/lru_cache/DoublyLinkedList.h"

namespace DoublyLinkedTest {
  TEST(DoublyLinkedList, add_tail) {
    auto linked_list = DoublyLinkedList<int>();
    linked_list.addTail(10);
    linked_list.addTail(20);
    EXPECT_EQ(linked_list.str(), "10 -> 20");
    EXPECT_EQ(linked_list.strReverse(), "20 -> 10");
  }


  TEST(DoublyLinkedList, add_head) {
    auto linked_list = DoublyLinkedList<int>();
    linked_list.addHead(10);
    linked_list.addHead(20);
    EXPECT_EQ(linked_list.str(), "20 -> 10");
    EXPECT_EQ(linked_list.strReverse(), "10 -> 20");
  }

  TEST(DoublyLinkedList, removeTail) {
    auto linked_list = DoublyLinkedList<int>();
    linked_list.addTail(10);
    linked_list.addTail(20);
    linked_list.removeTail();
    EXPECT_EQ(linked_list.str(), "10");
    EXPECT_EQ(linked_list.strReverse(), "10");
  }

  TEST(DoublyLinkedList, removeHead) {
    auto linked_list = DoublyLinkedList<int>();
    linked_list.addTail(10);
    linked_list.addTail(20);
    linked_list.removeHead();
    EXPECT_EQ(linked_list.str(), "20");
    EXPECT_EQ(linked_list.strReverse(), "20");
  }

  TEST(DoublyLinkedList, moveToHead) {
    auto linked_list = DoublyLinkedList<int>();
    auto node1 =  linked_list.addTail(10);
    auto node2 =  linked_list.addTail(20);
    auto node3 = linked_list.addTail(30);

    EXPECT_EQ(linked_list.str(), "10 -> 20 -> 30");
    // try move the head
    linked_list.moveToHead(node1);
    EXPECT_EQ(linked_list.str(), "10 -> 20 -> 30");

    // try move the middle
    linked_list.moveToHead(node2);
    EXPECT_EQ(linked_list.str(), "20 -> 10 -> 30");

    //try move the tail
    linked_list.moveToHead(node3);
    EXPECT_EQ(linked_list.str(), "30 -> 20 -> 10");
    EXPECT_EQ(linked_list.strReverse(), "10 -> 20 -> 30");
    std::cout << "ok" << std::endl;
  }



}
