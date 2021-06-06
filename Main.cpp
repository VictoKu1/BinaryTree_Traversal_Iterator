#include "sources/BinaryTree.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace ariel;
int main() {
  BinaryTree<char> tree;
  tree.add_root('a');
  for (int i = 1; i <= 12; i++) {
    tree.add_left(static_cast<char>(i + 96), static_cast<char>((2 * i) + 96));
    tree.add_right(static_cast<char>(i + 96),
                   static_cast<char>(((2 * i) + 1) + 96));
  }
  cout << tree << endl;
  return 0;
}

