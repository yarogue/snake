#pragma once
#include "Position.hpp"

// ============================================================
// TODO Phase 6 (Extra) — LinkedList (header)
// ============================================================
// A custom singly-linked list that replaces std::deque<Position>
// in the Snake. Uses raw pointers with new/delete.
//
// WHY replace std::deque?
//   The extra credit requires: "Refactor the snake so that it
//   is implemented using a custom made linked list, using
//   normal pointers and new/delete."
//
// HOW the Snake uses it:
//   - pushFront(pos)  → called to add new head when moving
//   - popBack()       → called to remove tail (normal move)
//   - front()         → called to get head position
//   - The snake GROWS by calling pushFront WITHOUT popBack
//
// NODE STRUCTURE:
//   struct Node {
//     Position data;     // the cell position
//     Node* next;        // pointer to next node (toward tail)
//   };
//
// CLASS MEMBERS:
//   Node* head;          // pointer to the first node (snake head)
//   int   length;        // track count so we don't traverse to count
//
// METHODS to implement (in LinkedList.cpp):
//
//   LinkedList()
//     → Initialize head = nullptr, length = 0
//
//   ~LinkedList()
//     → Walk the list from head to end.
//     → For each node: save next, delete current, move to next.
//     → This prevents memory leaks when a LinkedList is destroyed.
//
//   void pushFront(Position pos)
//     → Create: Node* newNode = new Node{pos, head};
//     → Set head = newNode
//     → Increment length
//
//   void popBack()
//     → If length <= 1: just delete head, set head = nullptr
//     → Otherwise: walk to second-to-last node (node->next->next == nullptr)
//     → Delete the last node, set second-to-last->next = nullptr
//     → Decrement length
//
//   Position front() const
//     → Return head->data
//
//   int size() const
//     → Return length
//
//   Position at(int index) const
//     → Walk index steps from head, return that node's data
//     → Used for drawing the body and collision checks
//
//   bool contains(Position pos) const
//     → Walk the list, return true if any node has data == pos
// ============================================================

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

  void pushFront(Position pos);
  void popBack();
  Position front() const;
  int size() const;
  Position at(int index) const;
  bool contains(Position pos) const;
};
