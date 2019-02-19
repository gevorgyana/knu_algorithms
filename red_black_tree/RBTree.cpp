//
// Created by artyom on 17.02.19.
//

#include "RBTree.h"
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

RBTree::RBTree() {
    root = new Node;
    root = nullptr;
}

//Node* RBTree::root = nullptr;

Node *RBTree::getRoot() {
    return root;
}

void RBTree::show() {
    stackWrite();
    system("./show_png.sh");
}

void RBTree::stackWrite() {
    ofstream dotFile;
    dotFile.open ("./gr.dot");
    dotFile << "digraph {\n";
    stack <Node*> st;
    Node* cur = root;
    while (cur || !st.empty()) {
        while (cur) {
            st.push(cur);
            cur = cur -> left;
        }
        cur = st.top();
        st.pop();
        if (cur -> left) {
            dotFile << "\t" << cur -> key << " -> " << cur -> left -> key << ";\n";
        }
        if (cur -> right) {
            dotFile << "\t" << cur -> key << " -> " << cur -> right -> key << ";\n";
        }
        cur = cur -> right;
    }
    dotFile << "}\n";
    dotFile.close();
}



void RBTree::insert(Node *i) {

    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (i->key < x -> key) {
            x = x -> left;
        } else  {
            x = x -> right;
        }
    }

    i -> parent = y;
    if (y == nullptr) {
        root = i;
    }
    else if (i -> key < y -> key) {
        y -> left = i;
    } else {
        y -> right = i;
    }
    insertFixup(i);

}

void RBTree::setRoot(Node *r) {
    root = r;
}

Node *RBTree::getGoodNode(int v) {
    auto goodN = new Node;
    goodN->left = nullptr;
    goodN -> right = nullptr;
    goodN ->parent = nullptr;
    goodN -> key = v;
    goodN -> color = true;
    return goodN;
}

void RBTree::insertFixup(Node *z) {
}

void RBTree::leftRotate(Node *x) {

    Node* y = x -> right;
    x -> right = y -> left;
    if (y -> left) {
        y -> left -> parent = x;
    }

    y -> parent = x -> parent;
    if (x -> parent == nullptr) {
        root = y;
    }
    else if (x -> parent -> left && x -> parent -> left == x) {
        x -> parent -> left = y;
    } else {
        x -> parent -> right = y;
    }
    x -> parent = y;
    y -> left = x;
}

void RBTree::rightRotate(Node *x) {
    Node* y = x -> left;
    if (y) {
        x -> left = y -> right;
    } else {
        x -> left = nullptr;
    }
    //x -> left = y -> right;

    if (y && y -> right) {
        y -> right -> parent = x;
    }
    if (y&& y -> parent)y -> parent = x -> parent;
    if (!(x->parent)) {
        root = y;
    }
    else if (x == x -> parent -> left) {
        x -> parent -> left = y;
    } else {
        x -> parent -> right = y;
    }
    if (y && y -> right)y -> right = x;
    x -> parent = y;
}
