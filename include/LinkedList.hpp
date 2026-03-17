#pragma once
#include "Position.hpp"

struct Node {
  Position data;
  Node *next;
};

class LinkedList {
public:
  Node *head;
  int length;

  LinkedList();
  ~LinkedList();
  LinkedList(const LinkedList &other);            // deep copy
  LinkedList &operator=(const LinkedList &other); // deep copy assignment

  void pushFront(Position pos);
  void popBack();
  Position front() const;
  int size() const;
  Position at(int index) const;
  bool contains(Position pos) const;
};
