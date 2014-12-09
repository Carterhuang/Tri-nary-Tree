#include "trinary.h"
#include <assert.h>
#include <stdint.h>
#include <queue>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

void Trinary::insertNode(int v) {
    // Empty root.
    if (!root) {
        root = new Node(v);
        return;
    }
   
    Node* paren = root;
    Node* node = root;
    while(node) {
        paren = node;
        if (v < node->val) {
            node = node->left;
        }
        else if (v > node->val) {
            node = node->right;
        }
        else {
            node = node->mid;
        }
    }

    if (v < paren->val) {
        paren->left = new Node(v);
    }
    else if (v > paren->val) {
        paren->right = new Node(v);
    }
    else {
        paren->mid = new Node(v);
    }
}

void Trinary::deleteNode(int v) {
    // Empty root.
    if (!root) {
        return;
    }
   
    if (!(root->left || root->mid || root->right)) {
        if (root->val == v)
            root = NULL;
        return;
    }

    Node* paren = NULL;
    Node* node = root;

    int flag = -1;
    while(node && node->val != v) {
        paren = node;
        if (v < node->val) {
            flag = 0;
            node = node->left;
        }
        else if (v > node->val) {
            flag = 2;
            node = node->right;
        }
        else {
            flag = 1;
            node = node->mid;
        }
    }
  
    if (!node) {
        return;
    }

    // The node to be deleted is a 
    // leaf node.
    if (!(node->left || node->mid || node->right)) {
        if (flag == 0)
            paren->left = NULL;
        else if (flag == 1)
            paren->mid = NULL;
        else
            paren->right = NULL;        
        delete node;
        return;
    }

    // This node that contains v has a 
    // mid node.
    if (node->mid != NULL) {
        Node* tmp = node->mid;
        node->mid = tmp->mid;
        delete tmp;
        return;
    }

    if ((uintptr_t)node & 0x0001) {
        int value;
        if (node->left) {
            value = searchPredecessorAndDelete(node);
        } 
        else {
            value = searchSuccessorAndDelete(node);
        }
        node->val = value;
    }

    else {
        int value;
        if (node->right) {
            value = searchSuccessorAndDelete(node);
        } 
        else {
            value = searchPredecessorAndDelete(node);
        }
        node->val = value;
    }
}

int Trinary::searchPredecessorAndDelete(Node* n) {
    assert(n != NULL);
    assert(n->left != NULL);  
    printf("P\n"); 
 
    Node* paren = n;
    Node* node = paren->left;

    if (!node->right) {
        paren->left = NULL;
        int result = node->val;
        delete node;
        return result;
    }

    while(node->right || node->mid) {
        paren = node;
        if (node->right)
            node = node->right;
        else
            node = node->mid;
    }
    paren->right = NULL;
    int result = node->val;
    delete node;
    return result;
}

int Trinary::searchSuccessorAndDelete(Node* n) {
    assert(n != NULL);
    assert(n->right != NULL);   
    printf("S\n");
 
    Node* paren = n;
    Node* node = paren->right;

    if (!node->left) {
        paren->right = NULL;
        int result = node->val;
        delete node;
        return result;
    }

    while(node->left || node->mid) {
        paren = node;
        if (node->left)
            node = node->left;
        else
            node = node->mid;
    }
    paren->left = NULL;
    int result = node->val;
    delete node;
    return result;
}


void Trinary::printTree() {
    queue<Node*> que;
    printf("Tree:\n"); 
    if(root)
        que.push(root);
    else
        printf("(empty)\n");
    int count;
    while(!que.empty()) {
        count = que.size();
        for (int i = 0; i < count; ++i) {
            Node* tmp = que.front();
            printf("%d ", tmp->val);
            if (tmp->left) 
                que.push(tmp->left);
            if (tmp->mid)
                que.push(tmp->mid);
            if (tmp->right)
                que.push(tmp->right);
            que.pop();
        }
        printf("\n");
    }
    printf("printTree finished!\n"); 
}

void Trinary::postOrderDelete(Node* node) {
    if (!node)
        return;
    
    if (node->left)
        postOrderDelete(node->left);
    if (node->mid)
        postOrderDelete(node->mid);
    if (node->right)
        postOrderDelete(node->right);
    delete node;
}

void Trinary::preorderHelper(Node* node, stringstream& result) {
    if (!node) {
        result << '#' << '%';
        return;
    }
    result << node->val << '%';
    if (! (node->left || node->mid || node->right) ) {
        return;
    }
    preorderHelper(node->left, result);
    preorderHelper(node->mid, result);
    preorderHelper(node->right, result);
}


string Trinary::serializePreorder() {
    stringstream result;
    preorderHelper(root, result);
    return result.str();
}

void treeCheck(const string& output, const string& expected) {
    if (output.compare(expected) == 0) {
        printf("Case succeeded on %s.\n", expected.c_str());
    }
    else {
        printf("Case failed on %s!!!!!!!!\n", expected.c_str());
    }
}


void treeCheckAfterDelete(const string& output, 
                          const string& expected1, const string& expected2) {
    if (output.compare(expected1) == 0 || output.compare(expected2) == 0) {
        printf("Case succeeded on %s, %s.\n", expected1.c_str(), expected2.c_str());
    }
    else {
        printf("Case failed on %s, %s!!!!!!!!\n", expected1.c_str(), expected2.c_str());
    }
}
