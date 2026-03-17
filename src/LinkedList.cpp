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

// Deep copy constructor — duplicate all nodes
LinkedList::LinkedList(const LinkedList &other) : head(nullptr), length(0) {
  // Walk the source list and pushFront in reverse to preserve order
  // First, collect all positions
  if (other.length == 0) return;
  
  Node* src = other.head;
  // Copy first node
  head = new Node{src->data, nullptr};
  Node* dst = head;
  src = src->next;
  
  // Copy remaining nodes
  while (src != nullptr) {
    dst->next = new Node{src->data, nullptr};
    dst = dst->next;
    src = src->next;
  }
  length = other.length;
}

// Deep copy assignment operator
LinkedList &LinkedList::operator=(const LinkedList &other) {
  if (this == &other) return *this;  // self-assignment check
  
  // Free existing nodes
  Node* current = head;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  head = nullptr;
  length = 0;
  
  // Copy from other
  if (other.length == 0) return *this;
  
  Node* src = other.head;
  head = new Node{src->data, nullptr};
  Node* dst = head;
  src = src->next;
  
  while (src != nullptr) {
    dst->next = new Node{src->data, nullptr};
    dst = dst->next;
    src = src->next;
  }
  length = other.length;
  return *this;
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