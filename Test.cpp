#include "doctest.h"
#include "sources/BinaryTree.hpp"
#include <string>
using namespace std;
using namespace ariel;
TEST_CASE("Basic Test Integer.") {
  BinaryTree<int> tree_of_ints;
  CHECK_NOTHROW(tree_of_ints.add_root(1));
  CHECK_NOTHROW(tree_of_ints.add_left(1, 9));
  CHECK_NOTHROW(tree_of_ints.add_left(9, 4));
  CHECK_NOTHROW(tree_of_ints.add_right(9, 5));
  CHECK_NOTHROW(tree_of_ints.add_right(1, 3));
  CHECK_NOTHROW(tree_of_ints.add_left(1, 2));
  CHECK_THROWS(tree_of_ints.add_left(0, 1));
  CHECK_THROWS(tree_of_ints.add_left(7, 0));
  auto it = tree_of_ints.begin_preorder();
  string s = "";
  for (auto it = tree_of_ints.begin_preorder();
       it != tree_of_ints.end_preorder(); ++it) {
    s += to_string(*it) + " ";
  }
  string sAn = "1 2 4 5 3 ";
  CHECK(s == sAn);
  s = "";
  for (auto it = tree_of_ints.begin_inorder(); it != tree_of_ints.end_inorder();
       ++it) {
    s += to_string(*it) + " ";
  }
  sAn = "4 2 5 1 3 ";
  CHECK(s == sAn);
  s = "";
  for (auto it = tree_of_ints.begin_postorder();
       it != tree_of_ints.end_postorder(); ++it) {
    s += to_string(*it) + " ";
  }
  sAn = "4 5 2 3 1 ";
  CHECK(s == sAn);
  s = "";
  for (int element : tree_of_ints) {
    s += to_string(element) + " ";
  }
  sAn = "4 2 5 1 3 ";
  CHECK(s == sAn);
}
TEST_CASE("Basic Test String.") {
  BinaryTree<string> tree_of_string;
  CHECK_NOTHROW(tree_of_string.add_root("1"));
  CHECK_NOTHROW(tree_of_string.add_left("1", "9"));
  CHECK_NOTHROW(tree_of_string.add_left("9", "4"));
  CHECK_NOTHROW(tree_of_string.add_right("9", "5"));
  CHECK_NOTHROW(tree_of_string.add_right("1", "3"));
  CHECK_NOTHROW(tree_of_string.add_left("1", "2"));
  auto it = tree_of_string.begin_preorder();
  string s = "";
  for (auto it = tree_of_string.begin_preorder();
       it != tree_of_string.end_preorder(); ++it) {
    s += (*it) + " ";
  }
  string sAn = "1 2 4 5 3 ";
  CHECK(s == sAn);
  s = "";
  for (auto it = tree_of_string.begin_inorder();
       it != tree_of_string.end_inorder(); ++it) {
    s += (*it) + " ";
  }
  sAn = "4 2 5 1 3 ";
  CHECK(s == sAn);
  s = "";
  for (auto it = tree_of_string.begin_postorder();
       it != tree_of_string.end_postorder(); ++it) {
    s += (*it) + " ";
  }
  sAn = "4 5 2 3 1 ";
  CHECK(s == sAn);
  s = "";
  for (string element : tree_of_string) {
    s += element + " ";
  }
  sAn = "4 2 5 1 3 ";
  CHECK(s == sAn);
  CHECK_THROWS(tree_of_string.add_left("0", "1"));
  CHECK_THROWS(tree_of_string.add_left("7", "0"));
}

TEST_CASE("Basic Test Letters.") {
  BinaryTree<char> tree_of_ints;
  CHECK_NOTHROW(tree_of_ints.add_root('a'));
  for (int i = 1; i <= 12; i++) {
    CHECK_NOTHROW(tree_of_ints.add_left(static_cast<char>(i + 96),
                                        static_cast<char>((2 * i) + 96)));
    CHECK_NOTHROW(tree_of_ints.add_right(
        static_cast<char>(i + 96), static_cast<char>(((2 * i) + 1) + 96)));
  }
  string s = "";
  for (auto it = tree_of_ints.begin_preorder();
       it != tree_of_ints.end_preorder(); ++it) {
    s.push_back((*it));
    s += " ";
  }
  string sAn = "a b d h p q i r s e j t u k v w c f l x y m g n o ";
  CHECK(s == sAn);
  s = "";
  for (auto it = tree_of_ints.begin_inorder(); it != tree_of_ints.end_inorder();
       ++it) {
    s.push_back((*it));
    s += " ";
  }
  sAn = "p h q d r i s b t j u e v k w a x l y f m c n g o ";
  CHECK(s == sAn);
  s = "";
  for (auto it = tree_of_ints.begin_postorder();
       it != tree_of_ints.end_postorder(); ++it) {
    s.push_back((*it));
    s += " ";
  }
  sAn = "p q h r s i d t u j v w k e b x y l m f n o g c a ";
  CHECK(s == sAn);
  s = "";
  for (char element : tree_of_ints) {
    s.push_back(element);
    s += " ";
  }
  sAn = "p h q d r i s b t j u e v k w a x l y f m c n g o ";
  CHECK(s == sAn);
}

