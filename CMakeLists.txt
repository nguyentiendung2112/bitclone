cmake_minimum_required(VERSION 3.31)
project(GraphDB)

set(CMAKE_CXX_STANDARD 20)

add_executable(GraphDB src/main.cpp
        src/FileEntry.cc
        src/FileEntry.h
        src/byte_buffer/BytesBuffer.cc
        src/byte_buffer/BytesBuffer.h
        src/LogWriter.cc
        src/LogWriter.h
        src/LogReader.cc
        src/LogReader.h
        src/LogIndex.h
        src/lru_cache/LRUCache.cc
        src/lru_cache/LRUCache.h
        src/lru_cache/DoublyLinkedList.cc
        src/lru_cache/DoublyLinkedList.h
)
