#include <iostream>
#include <cstring>
#include <cctype>

struct Node {
  char data;
  Node *left, *right, *next;
  Node(char val) : data(val), left(nullptr),right(nullptr), next(nullptr) {}
};

// Stack operations
void push(Node*& top, Node*newNode) {
  newNode->next=top;
  top=newNode;
}

Node* pop(Node*& top) {
  if (!top) return nullptr;
  Node* temp = top;
  top = top->next;
  temp->next = nullptr; //detach from stack list
  return temp;
}

Node* peek(Node* top) {
  return top;
}

// queue operations
void enqueue(Node*& head, Node*& tail, Node* newNode) {
  newNode->next = nullptr;
  if (!tail) {
    head = tail = newNode;
  } else {
    tail->next = newNode;
    tail = newNode;
  }
}

Node*dequeue(Node*& head, Node*& tail) {
  if (!head) return nullptr;
  Node* temp = head;
  head = head->next;
  if (!head) tail = nullptr;
  temp->next = nullptr;
  return temp;
}

//helper functions
int getPrecedence(char op) {
  if (op =='^') return 3;
  if (op =='*' || op == '/') return 2;
  if (op =='+' || op == '-') return 1;
  return 0;
}

bool isOperator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// recursive tree traversals
void printlnfix(Node* root) {
  if (root) {
    if (isOperator(root->data)) std::cout << "(";
    printlnfix(root->left);
    std::cout << root->data << " ";
    printlnfix(root -> right);
    if (isOperator(root->data)) std::cout << ") ";
  }
}
