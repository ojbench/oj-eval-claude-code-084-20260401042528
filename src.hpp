//
// Created by wzj on 2021/12/3.
// Modified by Yifei Ma on 2023/10/25.
//

#ifndef FINAL_SRC_HPP
#define FINAL_SRC_HPP

#include <string>
#include <vector>

// If the two following commands bother you, you may comment them and write
// std::vector and std::string instead.
using std::string;
using std::vector;

struct LinkedHashMap;
struct Node {
  Node* next = nullptr;
  Node* timePre = nullptr;
  Node* timeNext = nullptr;

  int key = 0;
  string value;
};

struct Data {
  int key;
  string value;
};

vector<Data> traverseByTime(const LinkedHashMap& obj);
vector<Data> traverseByIndex(const LinkedHashMap& obj);

struct LinkedHashMap {
  // You can modify beg, cur and related parts in the constructor as you wish.
  // 你可以根据自己写链表的习惯修改或删除头尾节点并修改构造函数。

  int len;
  Node** array;
  Node* beg;
  Node* cur;
  // TODO: define a function pointer named "forEachMethod"
  // to be pointed to one of the functions "traverseByTime" or "traverseByDict".
  // 定义一个名为 forEachMethod 的函数指针，用于指向 travelByTime 或
  // travelByDict 函数。
  vector<Data> (*forEachMethod)(const LinkedHashMap&);

  void init(int len_, bool forEachByTime) {
    len = len_;
    beg = new Node();
    cur = beg;
    array = new Node*[len];
    for (int i = 0; i < len; i++) {
      array[i] = nullptr;
    }
    if (forEachByTime)
      forEachMethod = traverseByTime;
    else
      forEachMethod = traverseByIndex;
  }

  void clearMemory() {
    // Traverse by time to delete all nodes
    Node* p = beg->timeNext;
    while (p != nullptr) {
      Node* temp = p;
      p = p->timeNext;
      delete temp;
    }
    delete beg;
    delete[] array;
  }

  void insert(int key, string value) {
    // Create new node
    Node* newNode = new Node();
    newNode->key = key;
    newNode->value = value;

    // Insert at head of hash chain
    newNode->next = array[key];
    array[key] = newNode;

    // Insert at tail of time chain
    cur->timeNext = newNode;
    newNode->timePre = cur;
    newNode->timeNext = nullptr;
    cur = newNode;
  }

  void remove(int key, string value) {
    // Remove from hash chain
    Node* p = array[key];
    Node* prev = nullptr;

    while (p != nullptr) {
      if (p->value == value) {
        // Remove from hash chain
        if (prev == nullptr) {
          array[key] = p->next;
        } else {
          prev->next = p->next;
        }

        // Remove from time chain
        if (p->timePre != nullptr) {
          p->timePre->timeNext = p->timeNext;
        }
        if (p->timeNext != nullptr) {
          p->timeNext->timePre = p->timePre;
        }

        // Update cur if we're deleting the last node
        if (p == cur) {
          cur = p->timePre;
        }

        Node* temp = p;
        p = p->next;
        delete temp;
      } else {
        prev = p;
        p = p->next;
      }
    }
  }

  vector<string> ask(int key) const {
    vector<string> result;
    Node* p = array[key];
    while (p != nullptr) {
      result.push_back(p->value);
      p = p->next;
    }
    return result;
  }

  vector<Data> forEach() const { return forEachMethod(*this); }
};

vector<Data> traverseByTime(const LinkedHashMap& obj) {
  vector<Data> result;
  Node* p = obj.beg->timeNext;
  while (p != nullptr) {
    Data d;
    d.key = p->key;
    d.value = p->value;
    result.push_back(d);
    p = p->timeNext;
  }
  return result;
}

vector<Data> traverseByIndex(const LinkedHashMap& obj) {
  vector<Data> result;
  for (int i = 0; i < obj.len; i++) {
    Node* p = obj.array[i];
    while (p != nullptr) {
      Data d;
      d.key = p->key;
      d.value = p->value;
      result.push_back(d);
      p = p->next;
    }
  }
  return result;
}

#endif  // FINAL_SRC_HPP
