//
// Created by Dung on 15/11/25.
//

#ifndef LOGINDEX_H
#define LOGINDEX_H

struct LogIndex {
  std::string key;
  std::string value;

  LogIndex(std::string key, std::string value) {
    this -> key = key;
    this -> value = value;
  }
};


#endif //LOGINDEX_H
