#pragma once
#include <bits/c++config.h>
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
#include <vector>
using namespace std;
namespace ariel {

enum Direction { Right, Left };

enum Order { Preorder, Inorder, Postorder };

template <typename T> class BinaryTree {

  class Node {
  public:
    Node *right;
    Node *left;
    T data;

    void deleter(Node *node) {
      if (node == nullptr) {
        return;
      }
      if ((*node).left != nullptr) {
        deleter((*node).left);
        delete (*node).left;
      }
      if ((*node).right != nullptr) {
        deleter((*node).right);
        delete (*node).right;
      }
    }

    //*Constructor.
    Node(T data) : data(data), right(nullptr), left(nullptr) {}

    //*Copy Constructor .
    Node(const Node &node) : data(node.data), right(nullptr), left(nullptr) {
      if (node.left != nullptr) {
        this->left = new Node(*(node.left));
      }
      if (node.right != nullptr) {
        this->right = new Node(*(node.right));
      }
    }

    //*Move Copy Constructor.
    Node(Node &&node) noexcept
        : data(node.data), right(node.right), left(node.left) {}

    //*Distructor.
    ~Node() { /*deleter((*this).root);*/
    }

    //*Move Assignment.
    Node &operator=(const Node &other) noexcept {
      if (this == &other) {
        return *this;
      }
      Node *leftN = nullptr;
      Node *rightN = nullptr;
      try {
        // if (node.left != nullptr) {
        leftN = new Node(*other.left);
        // }
        // if (node.right != nullptr) {
        rightN = new Node(*other.right);
        //  }
      } catch (...) {
        delete leftN;
        delete rightN;
      }
      data = T(other).data;
      swap(left, leftN);
      swap(right, rightN);
      delete leftN;
      delete rightN;
      deleter((*other).root);
      return *this;
    }

    //*Move Assignment Operator.
    Node &operator=(Node &&other) noexcept {
      deleter(this);
      this = new Node(move(other));
      other.deleter(other.root);
      return *this;
    }
  };


  //*Parameters.
  bool setWasChanged = true;
  map<T, Node *> nodeMap;
  Node *root;
  vector<Node *> preItr;
  vector<Node *> inItr;
  vector<Node *> postItr;

  //*Methods.
  bool contains(T key);
  void moveN(T source, T destination, Node *father, Direction direction);
  void preorder(Node *node);
  void inorder(Node *node);
  void postorder(Node *node);
  void print2DUtil(Node *root, int space);
  void fillMap(Node *node);

public:

  class Iterator {

  private:
    size_t pos;
    BinaryTree *btree;
    Order order;

    vector<Node *> orderedItr() const {
      switch (order) {
      case Preorder:
        return (*btree).preItr;
      case Inorder:
        return (*btree).inItr;
      case Postorder:
        return (*btree).postItr;
      }
    }

  public:
    Iterator(BinaryTree *btree, size_t pos, Order order)
        : btree(btree), pos(pos), order(order) {}

    bool operator==(const Iterator &other) {
      if (other.pos == other.orderedItr().size() &&
          pos == orderedItr().size()) {
        return true;
      }
      if (other.pos == other.orderedItr().size()) {
        return orderedItr().at(pos) == nullptr;
      }
      if (pos == orderedItr().size()) {
        return other.orderedItr().at(other.pos) == nullptr;
      }
      return orderedItr().at(pos) == other.orderedItr().at(other.pos);
    }

    bool operator!=(const Iterator &other) {
      if (other.pos == other.orderedItr().size() &&
          pos == orderedItr().size()) {
        return false;
      }
      if (other.pos == other.orderedItr().size()) {
        return orderedItr().at(pos) != nullptr;
      }
      if (pos == orderedItr().size()) {
        return other.orderedItr().at(other.pos) != nullptr;
      }
      return orderedItr().at(pos) != other.orderedItr().at(other.pos);
    }

    T &operator*() { return orderedItr().at(pos)->data; }

    T *operator->() { return &(this->operator*()); }

    Iterator &operator++() {
      pos++;
      return *this;
    }

    Iterator operator++(int d) {
      Iterator temporary = *this;
      pos++;
      return temporary;
    }
  };

  void itrClear() {
    preItr.clear();
    inItr.clear();
    postItr.clear();
  }

  //*Constructor.
  BinaryTree<T>() : root(nullptr), nodeMap() {}

  //*Copy Constructor .
  BinaryTree<T>(BinaryTree<T> const &bnrtree) : nodeMap() {
    root = new Node(*(bnrtree.root));
    fillMap(root);
  }

  //*Move Constructor .
  BinaryTree<T>(BinaryTree<T> &&bnrtree) noexcept {
    nodeMap.clear();
    root = move(bnrtree.root);
    fillMap(root);
    bnrtree.nodeMap.clear();
    bnrtree.itrClear();
    bnrtree.root = nullptr;
    setWasChanged = true;
  }

  //*Assignment Operator .
  BinaryTree &operator=(const BinaryTree &other) noexcept {
    if (&other == this) {
      return *this;
    }
    Node *temp = new Node(*(other.root));
    for (auto const &i : this->nodeMap) {
      delete i.second;
    }
    root = temp;
    itrClear();
    nodeMap.clear();
    setWasChanged = true;
    fillMap(root);
    return *this;
  }

  //*Move Assignment Operator.
  BinaryTree &operator=(BinaryTree &&other) noexcept {
    if (&other == this) {
      return *this;
    }
    for (auto const &i : nodeMap) {
      delete i.second;
    }
    nodeMap.clear();
    root = other.root;
    nodeMap = other.nodeMap;
    other.nodeMap.clear();
    other.itrClear();
    return *this;
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

  int size() { return nodeMap.size(); }

  template <typename P>
  friend ostream &operator<<(ostream &os, BinaryTree<P> &root);
  void print2D(Node *bnrtree);

  void syncr() {
    nodeMap.clear();
    fillMap(root);
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
  syncr();
  return nodeMap.count(key) > 0 && nodeMap[key] != nullptr;
}

//* Method which is moving a value in nodeMap from key source to destination .
template <typename T>
void BinaryTree<T>::moveN(T source, T destination, Node *father,
                          Direction direction) {
  auto entry = nodeMap.find(source);
  if (entry != nodeMap.end()) {
    auto value = entry->second;
    nodeMap.erase(entry);
    value->data = destination;
    nodeMap.insert({destination, value});
    nodeMap[destination]->data = destination;
    if (direction == Left) {
      (*father).left = nodeMap[destination];
    } else {
      (*father).right = nodeMap[destination];
    }
  }
}

//*Method which reorganize the iterator list by this tree preoprder scan.
template <typename T> void BinaryTree<T>::preorder(Node *node) {
  if (node == nullptr) {
    return;
  }
  preItr.insert(preItr.end(), node);
  preorder((*node).left);
  preorder((*node).right);
}

//*Method which reorganize the iterator list by this tree inoprder scan.
template <typename T> void BinaryTree<T>::inorder(Node *node) {
  if (node == nullptr) {
    return;
  }
  inorder((*node).left);
  inItr.insert(inItr.end(), node);
  inorder((*node).right);
}

//*Method which reorganize the iterator list by this tree postoprder scan.
template <typename T> void BinaryTree<T>::postorder(Node *node) {
  if (node == nullptr) {
    return;
  }
  postorder((*node).left);
  postorder((*node).right);
  postItr.insert(postItr.end(), node);
}

//*Method which adds a new root node the the tree, in case the root already
//*exists the method will only change its data parameter to the given one .
template <typename T> BinaryTree<T> &BinaryTree<T>::add_root(T value) {
  if (root == nullptr) {
    root = new Node(value);
  } else {
    syncr();
    nodeMap[root->data] = nullptr;
    root->data = value;
  }
  nodeMap[value] = root;
  setWasChanged = true;
  return *this;
}

//*Method which adds a left child node to the node with data parameter pos .
template <typename T> BinaryTree<T> &BinaryTree<T>::add_left(T pos, T value) {
  syncr();
  if (contains(pos)) {

    if (nodeMap[pos]->left == nullptr) {
      Node *n = new Node(value);
      nodeMap[pos]->left = n;
      nodeMap[value] = n;
    } else {
      moveN(nodeMap[pos]->left->data, value, nodeMap[pos], Left);
    }
  } else {
    throw invalid_argument{"No source node were found."};
  }
  setWasChanged = true;
  return *this;
}

//*Method which adds a right child node to the node with data parameter pos .
template <typename T> BinaryTree<T> &BinaryTree<T>::add_right(T pos, T value) {
  syncr();
  if (contains(pos)) {

    if (nodeMap[pos]->right == nullptr) {
      Node *n = new Node(value);
      nodeMap[pos]->right = n;
      nodeMap[value] = n;
    } else {
      moveN(nodeMap[pos]->right->data, value, nodeMap[pos], Right);
    }
  } else {
    throw invalid_argument{"No source node were found."};
  }
  setWasChanged = true;
  return *this;
}

//* Method which returnes an iterator to the first node in preorder tree scan .
template <typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::begin_preorder() {
  preItr.clear();
  preorder(root);
  setWasChanged = false;
  return Iterator(this, 0, Preorder);
}

//* Method which returnes an iterator to the last node in preorder tree scan .
template <typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::end_preorder() {
  begin_preorder();
  return Iterator(this, preItr.size(), Preorder);
}

//* Method which returnes an iterator to the first node in inorder tree scan .
template <typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::begin_inorder() {
  inItr.clear();
  setWasChanged = false;
  inorder(root);
  return Iterator(this, 0, Inorder);
}

//* Method which returnes an iterator to the last node in inorder tree scan .
template <typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::end_inorder() {
  begin_inorder();
  return Iterator(this, inItr.size(), Inorder);
}

//* Method which returnes an iterator to the first node in postorder tree scan .
template <typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::begin_postorder() {
  postItr.clear();
  postorder(root);
  setWasChanged = false;
  return Iterator(this, 0, Postorder);
}
//* Method which returnes an iterator to the last node in postorder tree scan .
template <typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::end_postorder() {

  begin_postorder();
  return Iterator(this, postItr.size(), Postorder);
}
//* Method which returnes an iterator to the first node in inorder tree scan .
template <typename T> typename BinaryTree<T>::Iterator BinaryTree<T>::begin() {
  // begin_inorder();
  // return Iterator(this, 0, Inorder);
  inItr.clear();
  setWasChanged = false;
  inorder(root);
  return Iterator(this, 0, Inorder);
}

//* Method which returnes an iterator to the last node in inorder tree scan .
template <typename T> typename BinaryTree<T>::Iterator BinaryTree<T>::end() {
  begin_inorder();
  return Iterator(this, inItr.size(), Inorder);
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

template <typename T> void BinaryTree<T>::fillMap(BinaryTree<T>::Node *node) {
  if (node == nullptr) {
    return;
  }
  nodeMap[node->data] = node;
  fillMap((*node).left);
  fillMap((*node).right);
}
} // namespace ariel


























































