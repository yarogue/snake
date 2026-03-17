#include "LinkedList.hpp"

//Constructor
LinkedList::LinkedList() {
  head = nullptr;
  length = 0;
}

//Destructor
LinkedList::~LinkedList() {
  const Node* current = head;
  while (current != nullptr) {
    const Node* next = current->next;
    delete current;
    current = next;
  }
  head = nullptr;
  length = 0;
}


void LinkedList::pushFront(Position pos) {
  auto newNode = new Node{pos, head};
  head = newNode;
  length++;
}

void LinkedList::popBack() {
  if(head == nullptr) return;
  if(head -> next == nullptr) {
    delete head;
    head = nullptr;
    length = 0;
    return;
  }
  Node* current = head;
  while (current->next->next !=nullptr) {
    current= current->next;
  }
  delete current->next;
  current->next = nullptr;
  length--;
}

Position LinkedList::front() const {
  return head->data;
}

int LinkedList::size() const {
  return length;
}

Position LinkedList::at(int index) const {
  Node* current = head;
  for (int i = 0; i < index; i++) {
    current= current->next;
  }
  return current->data;
}

bool LinkedList::contains(Position pos) const {
  Node* current = head;
  while (current != nullptr) {
    if (current->data == pos) return true;
    current= current->next;
  }
  return false;
}