#include <atomic>
#include <iostream>

struct Node {
  int data;
  Node* next;
};

class Stack {
  std::atomic<Node*> top;
  
  public:
    Stack(): top(nullptr) {
      std::cout << "Stack is " << 
        (top.is_lock_free() ? "" : "not ")
        << "lock-free" << std::endl;
    }

    void Push(int data) {
      Node* new_node = new Node{data, nullptr};
      new_node->next = top.load();
      while(!std::atomic_compare_exchange_weak(
                &top,
                &new_node->next,
                new_node));
    }
};

int main() {
  Stack s;
  s.Push(1);
}
