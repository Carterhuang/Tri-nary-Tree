#include <cstdio>
#include <sstream>
#include <string>

#ifndef _TRINARY_
#define _TRINARY_

struct Node {
    Node* left;
    Node* mid;
    Node* right;
    int val;
    Node(int v) : val(v), left(NULL), mid(NULL), right(NULL) {}
    ~Node() {}
};

class Trinary {
public:
    Trinary() : root(NULL) {}
    Trinary(Node* r) : root(r) {}

    // The destructor, or garbage collector for the 
    // the trinary tree. It traveres the entire tree
    // by post-order and deletes the nodes in that order.
    ~Trinary() { postOrderDelete(root); }

    void insertNode(int v);

    // Deleting a leaf node is fairly straightforward.
    // Deleteing a non-leaf node requires replacing 
    // the value of the current node with the value from
    // its predecessor/successor. In order to avoid generating
    // an un-balanced tree, choosing predecessor or successor 
    // should be randomnistic. In this interface, it checks 
    // the last the bit of the current node's address. If that
    // bit is set to 1 then predecessor and successor otherwise.
    void deleteNode(int v);
    void printTree();

    // This function serialize the tree in pre-order.
    // It uses '%' as the seperator between node values.
    // A NULL value is represented as '#'.
    //
    // For more information on how the tree is serialized,
    // please refer to README file in this package.
    std::string serializePreorder();
private:
    int searchNode(int v);
 
    // It finds the predecessor of the input node, saves the 
    // integer value, deletes the predecessor node and returns
    // the integer value.
    static int searchPredecessorAndDelete(Node* node);
    // Same logic for successor.
    static int searchSuccessorAndDelete(Node* node);
    // The method used by the destructor.
    static void postOrderDelete(Node* node);
    static void preorderHelper(Node* node, std::stringstream&result);
    Node* root;        
};

void treeCheck(const std::string& output, const std::string& expected);
void treeCheckAfterDelete(const std::string& output, 
                          const std::string& expected1,
                          const std::string& expected2);
#endif
