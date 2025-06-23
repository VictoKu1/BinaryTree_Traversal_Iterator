# Binary Tree with Iterators

This project implements a generic Binary Tree data structure in C++ along with iterators for different traversal methods.

## Table of Contents
- [Task](#task)
- [Solution](#solution)
  - [BinaryTree Class](#binarytree-class)
  - [Traversal Iterators](#traversal-iterators)
    - [In-order Traversal](#in-order-traversal)
    - [Pre-order Traversal](#pre-order-traversal)
    - [Post-order Traversal](#post-order-traversal)
  - [Memory Management](#memory-management)
- [How to Compile and Run](#how-to-compile-and-run)

## Task

The goal of this assignment is to implement a `BinaryTree` class in C++ that includes iterators for pre-order, in-order, and post-order traversals.

The `BinaryTree` class should have the following methods:
* `add_root(value)`: Adds or replaces the root of the tree.
* `add_left(existing_value, new_value)`: Adds `new_value` as the left child of `existing_value`.
* `add_right(existing_value, new_value)`: Adds `new_value` as the right child of `existing_value`.

It must also provide the following iterator pairs for traversal:
* `begin_preorder()`, `end_preorder()`
* `begin_inorder()`, `end_inorder()`
* `begin_postorder()`, `end_postorder()`

Additionally, the implementation should be memory-efficient, support deep copy and move semantics, and include a creative `main` function to demonstrate its functionality.

## Solution

The solution is implemented in the `BinaryTree.hpp` header file, which contains the `BinaryTree` class and the associated iterators.

### BinaryTree Class

The `BinaryTree<T>` class is a template class that can hold any type `T`. It uses a nested `Node` structure to represent the nodes of the tree. Each `Node` contains a value of type `T` and pointers to its left and right children.

The main methods of the `BinaryTree` class are:
*   `add_root(const T& value)`: Creates a new root for the tree. If a root already exists, its value is updated.
*   `add_left(const T& existing_val, const T& new_val)`: Finds the node with `existing_val` and adds `new_val` as its left child. Throws an exception if `existing_val` is not in the tree.
*   `add_right(const T& existing_val, const T& new_val)`: Finds the node with `existing_val` and adds `new_val` as its right child. Throws an exception if `existing_val` is not in the tree.

### Traversal Iterators

The iterators are implemented as nested classes within the `BinaryTree` class. Each iterator stores a pointer to the current `Node` it is pointing to. The core of the iterator implementation is the `operator++` (prefix increment), which advances the iterator to the next node in the specific traversal order.

To be memory-efficient, the iterators do not store the entire traversal sequence. Instead, they compute the next node on the fly. This is achieved by maintaining a queue of nodes to visit.

#### In-order Traversal

The in-order traversal visits the nodes in the following order: left subtree, root, right subtree. The `inorder_iterator` uses a queue to store the nodes in the correct order. The queue is populated by a recursive helper function that performs an in-order traversal of the tree and enqueues the nodes.

#### Pre-order Traversal

The pre-order traversal visits the nodes in the following order: root, left subtree, right subtree. The `preorder_iterator` works similarly to the in-order one, but the helper function enqueues the nodes in pre-order.

#### Post-order Traversal

The post-order traversal visits the nodes in the following order: left subtree, right subtree, root. The `postorder_iterator` follows the same pattern, with the helper function enqueuing nodes in post-order.

### Memory Management

The `BinaryTree` class manages memory using smart pointers (`std::unique_ptr`) or by explicitly handling memory with `new` and `delete`. The class implements:
*   A destructor `~BinaryTree()` that deallocates all nodes in the tree.
*   A copy constructor and copy assignment operator that perform a **deep copy** of the tree.
*   A move constructor and move assignment operator that perform a **shallow copy** by transferring ownership of the root pointer.

## How to Compile and Run

The project uses a `Makefile` for easy compilation.

*   To compile the code, run: `make`
*   To run the tests: `make test`
*   To run the demo: `make run`
*   To check for memory leaks with Valgrind: `make valgrind`
*   To clean the build files: `make clean`

A `main` function is provided in `Main.cpp` to demonstrate the usage of the `BinaryTree` class and its iterators.











