#include "trinary.h"

#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

void test_insert_empty_tree() {
    printf("TEST CASE: %s =======\n", __func__);
    Trinary* tree = new Trinary();
    tree->insertNode(1);
    treeCheck(tree->serializePreorder(), "1%");
    delete tree;
}

void test_delete_from_one_tree() {
    printf("TEST CASE: %s =======\n", __func__);
    Trinary* tree = new Trinary();
    tree->insertNode(1);
    tree->deleteNode(2);
    treeCheck(tree->serializePreorder(), "1%");
    tree->deleteNode(1);
    treeCheck(tree->serializePreorder(), "#%");
    tree->deleteNode(1);
    treeCheck(tree->serializePreorder(), "#%");
    delete tree;
}

void test_build_two_tree() {
    printf("TEST CASE: %s =======\n", __func__);
    Trinary* tree = new Trinary();
    tree->insertNode(1);
    tree->insertNode(2);
    treeCheck(tree->serializePreorder(), "1%#%#%2%");
    delete tree;
}

void test_delete_two_tree1() {
    printf("TEST CASE: %s\n", __func__);
    Trinary* tree = new Trinary();
    tree->insertNode(2);
    tree->insertNode(1);
    treeCheck(tree->serializePreorder(), "2%1%#%#%");
    tree->deleteNode(2);
    treeCheck(tree->serializePreorder(), "1%");
    tree->deleteNode(1);
    treeCheck(tree->serializePreorder(), "#%");
    delete tree;
}

void test_delete_two_tree2() {
    printf("TEST CASE: %s\n", __func__);
    Trinary* tree = new Trinary();
    tree->insertNode(1);
    tree->insertNode(2);
    treeCheck(tree->serializePreorder(), "1%#%#%2%");
    tree->deleteNode(2);
    tree->deleteNode(1);
    treeCheck(tree->serializePreorder(), "#%");
    delete tree;
}

void test_delete_non_leaf_node() {
    printf("TEST CASE: %s\n", __func__);
    Trinary* tree = new Trinary();
    tree->insertNode(4);
    tree->insertNode(2);
    tree->insertNode(6);
    tree->insertNode(1);
    tree->insertNode(3);
    tree->insertNode(5);
    tree->insertNode(7);
    treeCheck(tree->serializePreorder(), "4%2%1%#%3%#%6%5%#%7%");
    tree->deleteNode(2);
    treeCheckAfterDelete(tree->serializePreorder(), 
                         "4%3%1%#%#%#%6%5%#%7%",  
                         "4%1%#%#%3%#%6%5%#%7%");
    delete tree;
}

void test_delete_root() {
    printf("TEST CASE: %s\n", __func__);
    Trinary* tree = new Trinary();
    tree->insertNode(4);
    tree->insertNode(2);
    tree->insertNode(6);
    tree->insertNode(1);
    tree->insertNode(3);
    tree->insertNode(5);
    tree->insertNode(7);
    treeCheck(tree->serializePreorder(), "4%2%1%#%3%#%6%5%#%7%");
    tree->deleteNode(4);
    treeCheckAfterDelete(tree->serializePreorder(), 
                         "3%2%1%#%#%#%6%5%#%7%",  
                         "5%2%1%#%3%#%6%#%#%7%");
    delete tree;
}

int main() {
    test_insert_empty_tree();
    test_delete_from_one_tree();
    test_build_two_tree();
    test_delete_two_tree1();
    test_delete_two_tree2();
    test_delete_non_leaf_node();
    test_delete_root();
    return 0;
}
