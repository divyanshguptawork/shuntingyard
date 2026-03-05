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

void printPrefix(Node* root) {
  if (root) {
    if (isOperator(root->data)) std::cout<<"(";
    printPrefix(root->left);
    printPrefix(root->right);
  }
}

void printPostfix(Node* root) {
  if (root) {
    printPostfix(root->left);
    printPostfix(root->right);
    std::cout<<root->data<<" ";
  }
}

// main algorithms
int main(){
  char input[100];
  std::cout<<"Enter infix expression (space separated): "<< std::endl;
  std::cin.getline(input, 100);

  Node *opStack = nullptr;
  Node *outHead = nullptr, *outTail = nullptr;

  //shunting yard algorithm
  char* token = strtok(input, " ");
  while (token!=nullptr) {
    char c = token[0];

    if (isdigit(c)) {
      enqueue(outHead, outTail, new Node(c));
    } else if (c=='(') {
      push(opStack, new Node(c));
    } else if(c==')') {
      while (peek(opStack) && peek(opStack) ->data!='(') {
	enqueue(outHead, outTail, pop(opStack));
      }
      delete pop(opStack); // remove '('
    } else if (isOperator(c)) {
      while (peek(opStack) && getPrecedence(peek(opStack)->data)>=getPrecedence(c)) {
	// note: ^ is right associative but for single digits/simplicity
	// we treat standard precendence here
	enqueue(outHead, outTail, pop(opStack));
      }
      push(opStack, new Node(c));
    }
    token = strtok(nullptr, " ");
  }
  while (peek(opStack)) {
    enqueue(outHead, outTail, pop(opStack));
  }

  // print postfix result from shunting yard
  std::cout<<"Postfix(from Shunting Yard): ";
  Node* current = outHead;
  while (current) {
    std::cout<<current->data<<" ";
    current = current->next;
  }
  std::cout<<"\n\n";

  // build expression tree
  Node* treeStack = nullptr;
  while (outHead) {
    Node* node = dequeue(outHead, outTail);
    if (isdigit(node->data)) {
      push(treeStack, node);
    } else {
      node->right = pop(treeStack);
      node->left = pop(treeStack);
      push(treeStack, node);
    }
  }
  Node* root = pop(treeStack);

  //output from tree
  std::cout<<"lnfix (from tree): ";
  printlnfix(root);
  std::cout<<"\n";
  std::cout<<"Prefix (from tree): ";
  printPrefix(root);
  std::cout<<"\n";
  std::cout<<"Postfix (from tree): ";
  printPostfix(root);
  std::cout<<"\n";

  return 0;
}

