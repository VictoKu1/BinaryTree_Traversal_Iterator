#include "sources/BinaryTree.hpp"
#include <vector>
#include<iostream>
using namespace std;
using namespace ariel;
int main(){
    BinaryTree<int> tree;
    tree.add_root(1);
    tree.add_left(1,2).add_right(1,3);
    cout << "in" << endl;
    for(auto i : tree){
        cout << i << " ";
    }
    cout << endl;
    cout << "in" << endl;
    for(auto i = tree.begin_inorder();i != tree.end_inorder();++i){
        cout << *i << " ";
    }
    cout << endl;
    cout << "pre" << endl;
    for(auto i = tree.begin_preorder();i != tree.end_preorder();++i){
        cout << *i << " ";
    }
    cout << endl;
    cout << "post" << endl;
       for(auto i = tree.begin_postorder();i != tree.end_postorder();++i){
        cout << *i << " ";
    }
    cout << endl;
    cout << "copy" << endl;
    BinaryTree<int> tree2(tree);
    for(auto i : tree2){
        cout << i << " ";
    }
    cout << endl;
    tree.add_left(1,10);
    for(auto i : tree2){
        cout << i << " ";
    }
    cout << endl;
    for(auto i : tree){
        cout << i << " ";
    }
    cout << endl;
    tree2 = tree;
    vector< BinaryTree<int>> v(1);
    v.insert(v.end(),tree);
    v.insert(v.end(),tree2);
    return 0;
}
