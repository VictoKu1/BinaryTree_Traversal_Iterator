#pragma once
#include <exception>
#include <iostream>
#include <list>
#include <map>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <streambuf>
#include <string>
using namespace std;
namespace ariel {
enum Direction { Right, Left };
template <typename T> class BinaryTree {
  using Iterator = typename list<T>::iterator;

private:
  class Node {
  public:
    Node *right;
    Node *left;
    T data;

    void deleter() {
      if (left != nullptr) {
        delete left;
      }
      if (right != nullptr) {
        delete right;
      }
    }

    //*Constructor.
    Node(T data) : data(data), right(nullptr), left(nullptr) {}

    //*Copy Constructor .
    Node(Node const &node) : data(node.data), right(nullptr), left(nullptr) {
      if (node.left != nullptr) {
        left = new Node(*node.left);
      }
      if (node.right != nullptr) {
        right = new Node(*node.right);
      }
    }

    //*Move Copy Constructor.
    Node(Node &&node) noexcept {
      data = node.data;
      right = node.right;
      left = node.left;
    }

    //*Distructor.
    ~Node() {}

    //*Move Assignment.
    Node &operator=(const Node &other) noexcept {
      deleter();
      this = Node(other);
      return *this;
    }

    //*Move Assignment Operator.
    Node &operator=(Node &&other) noexcept {
      deleter();
      this = Node(move(other));
      other.deleter();
      return *this;
    }
  };

  bool setWasChanged = true;
  map<T, Node *> nodeMap;
  Node *root;
  list<T> itr;
  bool contains(T key);
  void moveN(T source, T destination, Node *father, Direction direction);
  void preorder(Node *node);
  void inorder(Node *node);
  void postorder(Node *node);
  void print2DUtil(Node *root, int space);

public:
  //*Constructor.
  BinaryTree<T>() : root(nullptr), nodeMap(), itr() {}

  //*Move Constructor .
  BinaryTree<T>(BinaryTree<T> &&bnrtree) noexcept {
    root = bnrtree.root;
    itr = bnrtree.itr;
    nodeMap = bnrtree.nodeMap;
    for (auto const &i : bnrtree.nodeMap) {
      (*i).second = nullptr;
    }
    bnrtree.nodeMap.clear();
    bnrtree.itr.clear();
  }

  //*Copy Constructor .
  BinaryTree<T>(BinaryTree<T> &bnrtree) {
    add_root(bnrtree.root->data);
    while (nodeMap.size() != bnrtree.nodeMap.size()) {
      for (auto const &i : bnrtree.nodeMap) {
        try {
          if (contains((*i).first)) {
            T f = (*i).first;
            if (contains((*i).seconds->left->data)) {
              T sl = (*i).second->left->data;
              add_left(f, sl);
            }
            if (contains((*i).seconds->right->data)) {
              T rl = (*i).second->left->data;
              add_right(f, rl);
            }
          }
        } catch (const invalid_argument &e) {
          continue;
        }
      }
    }
  }

  //*Distructor.
  ~BinaryTree<T>() {
    for (auto const &i : nodeMap) {
      delete i.second;
    }
  }

  BinaryTree &add_root(T value);
  BinaryTree &add_left(T pos, T value);
  BinaryTree &add_right(T pos, T value);
  Iterator begin_preorder();
  Iterator end_preorder();
  Iterator begin_inorder();
  Iterator end_inorder();
  Iterator begin_postorder();
  Iterator end_postorder();
  Iterator begin();
  Iterator end();
  template <typename P>
  friend ostream &operator<<(ostream &os, BinaryTree<P> &root);
  void print2D(Node *bnrtree);

  //*Assignment Operator .
  BinaryTree &operator=(const BinaryTree &other) noexcept {
    for (auto const &i : nodeMap) {
      delete (*i).second;
    }
    this = BinaryTree<T>(other);
    return *this;
  }

  //*Move Assignment Operator.
  BinaryTree &operator=(BinaryTree &&other) noexcept {
    for (auto const &i : nodeMap) {
      delete (*i).second;
    }
    root = other.root;
    itr = other.itr;
    nodeMap = other.nodeMap;
    setWasChanged = true;
    for (auto const &i : other.nodeMap) {
      (*i).second = nullptr;
    }
    other.nodeMap.clear();
    other.itr.clear();
    return *this;
  }
};

//*Helper class for redirecting cout stream to string .
class coutRedirect {
public:
  std::stringstream buffer;
  std::streambuf *old;
  coutRedirect() {
    old = std::cout.rdbuf(buffer.rdbuf()); //*Redirect cout to buffer stream.
  }
  std::string getString() const {
    return buffer.str(); //*Get string .
  }
  void coutRedirectCancel() const {
    std::cout.rdbuf(old); //*Reverse redirect .
  }
};

//*Boolean method which is checking if the given key is contained in this tree .
template <typename T> bool BinaryTree<T>::contains(T key) {
  return nodeMap.count(key) > 0;
}

//* Method which is moving a value in nodeMap from key source to destination .
template <typename T>
void BinaryTree<T>::moveN(T source, T destination, Node *father,
                          Direction direction) {
  nodeMap[destination] = new Node(move(*nodeMap[source]));
  delete nodeMap[source];
  nodeMap[source] = nullptr;
  nodeMap[destination]->data = destination;
  if (direction == Left) {
    (*father).left = nodeMap[destination];
  } else {
    (*father).right = nodeMap[destination];
  }
}

//*Method which reorganize the iterator list by this tree preoprder scan.
template <typename T> void BinaryTree<T>::preorder(Node *node) {
  if (node == nullptr) {
    return;
  }
  itr.push_back((*node).data);
  preorder((*node).left);
  preorder((*node).right);
}

//*Method which reorganize the iterator list by this tree inoprder scan.
template <typename T> void BinaryTree<T>::inorder(Node *node) {
  if (node == nullptr) {
    return;
  }
  inorder((*node).left);
  itr.push_back((*node).data);
  inorder((*node).right);
}

//*Method which reorganize the iterator list by this tree postoprder scan.
template <typename T> void BinaryTree<T>::postorder(Node *node) {
  if (node == nullptr) {
    return;
  }
  postorder((*node).left);
  postorder((*node).right);
  itr.push_back((*node).data);
}

//*Method which adds a new root node the the tree, in case the root already
//*exists the method will only change its data parameter to the given one .
template <typename T> BinaryTree<T> &BinaryTree<T>::add_root(T value) {
  if (root == nullptr) {
    root = new Node(value);
  } else {
    nodeMap.erase((*root).data);
    (*root).data = value;
  }
  nodeMap[value] = root;
  setWasChanged = true;
  return *this;
}

//*Method which adds a left child node to the node with data parameter pos .
template <typename T> BinaryTree<T> &BinaryTree<T>::add_left(T pos, T value) {
  if (contains(pos)) {
    if (nodeMap[pos]->left == nullptr) {
      Node *n = new Node(value);
      nodeMap[pos]->left = n;
      nodeMap[value] = n;
    } else {
      moveN(nodeMap[pos]->left->data, value, nodeMap[pos], Left);
    }
  } else {
    throw invalid_argument{"No source node were found.1"};
  }
  setWasChanged = true;
  return *this;
}

//*Method which adds a right child node to the node with data parameter pos .
template <typename T> BinaryTree<T> &BinaryTree<T>::add_right(T pos, T value) {
  if (contains(pos)) {
    if (nodeMap[pos]->right == nullptr) {
      Node *n = new Node(value);
      nodeMap[pos]->right = n;
      nodeMap[value] = n;
    } else {
      moveN(nodeMap[pos]->right->data, value, nodeMap[pos], Right);
    }
  } else {
    throw invalid_argument{"No source node were found.2"};
  }
  setWasChanged = true;
  return *this;
}

//* Method which returnes an iterator to the first node in preorder tree scan .
template <typename T>
typename list<T>::iterator BinaryTree<T>::begin_preorder() {
  itr.clear();
  preorder(root);
  setWasChanged = false;
  return itr.begin();
}

//* Method which returnes an iterator to the last node in preorder tree scan .
template <typename T> typename list<T>::iterator BinaryTree<T>::end_preorder() {
  if (setWasChanged) {
    begin_preorder();
  }
  return itr.end();
}

//* Method which returnes an iterator to the first node in inorder tree scan .
template <typename T>
typename list<T>::iterator BinaryTree<T>::begin_inorder() {
  itr.clear();
  setWasChanged = false;
  inorder(root);
  return itr.begin();
}

//* Method which returnes an iterator to the last node in inorder tree scan .
template <typename T> typename list<T>::iterator BinaryTree<T>::end_inorder() {
  if (setWasChanged) {
    begin_inorder();
  }
  return itr.end();
}

//* Method which returnes an iterator to the first node in postorder tree scan .
template <typename T>
typename list<T>::iterator BinaryTree<T>::begin_postorder() {
  itr.clear();
  postorder(root);
  setWasChanged = false;
  return itr.begin();
}

//* Method which returnes an iterator to the last node in postorder tree scan .
template <typename T>
typename list<T>::iterator BinaryTree<T>::end_postorder() {
  if (setWasChanged) {
    begin_postorder();
  }
  return itr.end();
}

//* Method which returnes an iterator to the first node in inorder tree scan .
template <typename T> typename list<T>::iterator BinaryTree<T>::begin() {
  itr.clear();
  begin_inorder();
  return itr.begin();
}

//* Method which returnes an iterator to the last node in inorder tree scan .
template <typename T> typename list<T>::iterator BinaryTree<T>::end() {
  if (setWasChanged) {
    begin_inorder();
  }
  return itr.end();
}

//*Function to print binary tree in 2D.
//*It does reverse inorder traversal.
template <typename T> void BinaryTree<T>::print2DUtil(Node *root, int space) {
  const int COUNT = 5;
  //*Base case .
  if (root == NULL) {
    return;
  }
  //*Increase distance between levels .
  space += COUNT;

  //*Process right child first .
  print2DUtil(root->right, space);

  //*Print current node after space count .
  cout << endl;
  for (int i = COUNT; i < space; i++) {
    if (i >= space - COUNT) {

      if (i == space - COUNT) {
        cout << "|";
      } else {
        cout << "-";
      }
    } else {
      cout << " ";
    }
  }
  cout << root->data << "\n";

  //*Process left child.
  print2DUtil(root->left, space);
}

//*Wrapper over print2DUtil().
template <typename T> void BinaryTree<T>::print2D(Node *bnrtree) {
  print2DUtil(root, 0);
}

//*Method returnes a stream of the tree visualization .
template <typename T> ostream &operator<<(ostream &os, BinaryTree<T> &bnrtree) {
  coutRedirect redirection;
  (bnrtree).print2D(bnrtree.root);
  string out = redirection.getString();
  redirection.coutRedirectCancel();
  return os << out << endl;
}
} // namespace ariel


