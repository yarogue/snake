#include "LinkedList.hpp"

// ============================================================
// TODO Phase 6 (Extra) — LinkedList (implementation)
// ============================================================
// Implement all methods declared in LinkedList.hpp.
// Read the header file TODOs for detailed pseudocode.
//
// MEMORY RULES:
//   - Every 'new Node' MUST have a matching 'delete'
//   - pushFront() creates nodes → popBack() and ~LinkedList() delete them
//   - Never access a deleted node (dangling pointer!)
// ============================================================

// ────────────────────────────────────────────
// TODO 6a — Constructor
// ────────────────────────────────────────────
// PSEUDOCODE:
//   head = nullptr;
//   length = 0;
// ────────────────────────────────────────────
LinkedList::LinkedList() {
  // TODO: implement
}

// ────────────────────────────────────────────
// TODO 6b — Destructor
// ────────────────────────────────────────────
// PSEUDOCODE:
//   Node* current = head;
//   while (current != nullptr):
//     Node* next = current->next;
//     delete current;
//     current = next;
//   head = nullptr;
//   length = 0;
// ────────────────────────────────────────────
LinkedList::~LinkedList() {
  // TODO: implement
}

// ────────────────────────────────────────────
// TODO 6c — pushFront
// ────────────────────────────────────────────
// PSEUDOCODE:
//   Node* newNode = new Node{pos, head};
//   head = newNode;
//   length++;
// ────────────────────────────────────────────
void LinkedList::pushFront(Position pos) {
  // TODO: implement
}

// ────────────────────────────────────────────
// TODO 6d — popBack
// ────────────────────────────────────────────
// PSEUDOCODE:
//   if (head == nullptr) return;
//   if (head->next == nullptr):
//     delete head;
//     head = nullptr;
//     length = 0;
//     return;
//   Node* current = head;
//   while (current->next->next != nullptr):
//     current = current->next;
//   delete current->next;
//   current->next = nullptr;
//   length--;
// ────────────────────────────────────────────
void LinkedList::popBack() {
  // TODO: implement
}

// ────────────────────────────────────────────
// TODO 6e — front
// ────────────────────────────────────────────
// PSEUDOCODE:
//   return head->data;
// ────────────────────────────────────────────
Position LinkedList::front() const {
  // TODO: implement
  return Position{0, 0};
}

// ────────────────────────────────────────────
// TODO 6f — size
// ────────────────────────────────────────────
int LinkedList::size() const {
  // TODO: implement
  return 0;
}

// ────────────────────────────────────────────
// TODO 6g — at
// ────────────────────────────────────────────
// PSEUDOCODE:
//   Node* current = head;
//   for (int i = 0; i < index; i++):
//     current = current->next;
//   return current->data;
// ────────────────────────────────────────────
Position LinkedList::at(int index) const {
  // TODO: implement
  return Position{0, 0};
}

// ────────────────────────────────────────────
// TODO 6h — contains
// ────────────────────────────────────────────
// PSEUDOCODE:
//   Node* current = head;
//   while (current != nullptr):
//     if (current->data == pos) return true;
//     current = current->next;
//   return false;
// ────────────────────────────────────────────
bool LinkedList::contains(Position pos) const {
  // TODO: implement
  return false;
}
