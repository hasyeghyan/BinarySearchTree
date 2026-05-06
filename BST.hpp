#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <queue>

class BST {
    private:
        struct Node {
            int val;
            Node* left;
            Node* right;

            Node(int val) : val{val}, left{nullptr}, right{nullptr} {}
        };

        Node* root;
        void clear (Node* node);
        Node* copy (Node* node);
    public:
        BST() : root{nullptr} {}
        BST(const BST& other) {root = copy(other.root); }
        BST(BST&& other) : root{std::move(other.root)} {other.root = nullptr; }

        BST& operator=(const BST& other);
        BST& operator=(BST&& other);

        ~BST() { clear(root); }
        

        void insert(int k) { root = insert(root, k); }
        Node* insert(Node* node, int k);

        Node* search(Node* node, int key);

        Node* getMin(Node* node);
        Node* getMax(Node* node);

        Node* getPredecessor(Node* node);
        Node* getSuccessor(Node* node);

        void remove(int key) { root = remove(root, key); }
        Node* remove(Node* node, int key);
};

void BST::clear (Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

BST::Node* BST::copy (Node* node) {
    if (!node) return nullptr;

    Node* newNode = new Node(node->val);

    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
            
    return newNode;
}


BST& BST::operator=(const BST& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root);
    }
    return *this;
} 

BST& BST::operator=(BST&& other) {
    if (this != &other) {
        clear(root);
        root = std::move(other.root);
        other.root = nullptr;
    }
    return *this;
}

BST::Node* BST::insert(Node* node, int k) {
    if(!node) return new Node(k);

    if (k < node->val) node->left = insert(node->left, k);
    else if (k > node->val) node->right = insert(node->right, k);

    return node;
}

BST::Node* BST::search(Node* node, int key) {
    if (!node || node->val == key) return node;

    if (key < node->val) return search(node->left, key);
    return search(node->right, key);
}


BST::Node* BST::getMin(Node* node) {
    while (node && node->left) node = node->left;
    return node; 
}

BST::Node* BST::getMax(Node* node) {
    while (node && node->right) node = node->right;
    return node; 
}

BST::Node* BST::getPredecessor(Node* node) {
    if (!node) return nullptr;
    if (node->left) return getMax(node->left);

    Node* curr = root;
    Node* p = nullptr;

    while (curr) {
        if (curr->val > node->val) curr = curr->left;
        else if (curr->val < node->val) {
            p = curr;
            curr = curr->right;
        }
        else break;
    }
    return p;
}

BST::Node* BST::getSuccessor(Node* node) {
    if (!node) return nullptr;
    if (node->right) return getMin(node->right);

    Node* curr = root;
    Node* p = nullptr;

    while (curr) {
        if (curr->val < node->val) curr = curr->right;
        else if (curr->val > node->val) {
            p = curr;
            curr = curr->left;
        }
        else break;
    }
    return p;
}

BST::Node* BST::remove(Node* node, int key) {
    if (!node) return nullptr;
    
    if (key < node->val) node->left = remove(node->left, key);
    else if (key > node->val) node->right = remove(node->right, key);
    else {
        if (!node->left) {
            Node* tmp = node->right;
            delete node;
            return tmp;
        }
        else if (!node->right) {
            Node* tmp = node->left;
            delete node;
            return tmp;
        }
        else {
            Node* tmp = getMin(node->right);
            node->val = tmp->val;
            node->right = remove(node->right, tmp->val);
        }
    }
    return node;
}

// Variation with parent
class BST {
    private:
        struct Node {
            int val;
            Node* left;
            Node* right;
            Node* parent;

            Node(int val) : val{val}, left{nullptr}, right{nullptr}, parent{nullptr} {}
        };

        Node* root;
        void clear (Node* node);
        Node* copy (Node* node);
    public:
        BST() : root{nullptr} {}
        BST(const BST& other) {root = copy(other.root); }
        BST(BST&& other) : root{std::move(other.root)} {other.root = nullptr; }

        BST& operator=(const BST& other);
        BST& operator=(BST&& other);

        ~BST() { clear(root); }

        void insert(int k) { root = insert(root, nullptr, k); }
        Node* insert(Node* node, Node* prnt, int k);

        Node* search(Node* node, int key);

        Node* getMin(Node* node);
        Node* getMax(Node* node);

        Node* getPredecessor(Node* node);
        Node* getSuccessor(Node* node);

        void remove(int key) { root = remove(root, nullptr, key); }
        Node* remove(Node* node, Node* prnt, int key);
};

void BST::clear (Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

BST::Node* BST::copy (Node* node) {
    if (!node) return nullptr;

    Node* newNode = new Node(node->val);

    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
            
    return newNode;
}


BST& BST::operator=(const BST& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root);
    }
    return *this;
} 

BST& BST::operator=(BST&& other) {
    if (this != &other) {
        clear(root);
        root = std::move(other.root);
        other.root = nullptr;
    }
    return *this;
}

BST::Node* BST::insert(Node* node, Node* prnt, int k) {
    if(!node) {
        Node* newNode = new Node(k);
        newNode->parent = prnt;
        return newNode;
    } 

    if (k < node->val) node->left = insert(node->left, node, k);
    else if (k > node->val) node->right = insert(node->right, node, k);

    return node;
}

BST::Node* BST::search(Node* node, int key) {
    if (!node || node->val == key) return node;

    if (key < node->val) return search(node->left, key);
    return search(node->right, key);
}

BST::Node* BST::getMin(Node* node) {
    while (node && node->left) node = node->left;
    return node; 
}

BST::Node* BST::getMax(Node* node) {
    while (node && node->right) node = node->right;
    return node; 
}

BST::Node* BST::getPredecessor(Node* node) {
    if (!node) return nullptr;
    if (node->left) return getMax(node->left);

    Node* curr = node->parent;
    Node* p = node;

    while (curr && curr->left == p) {
        p = curr;
        curr = curr->parent;
    }
    return curr;
}

BST::Node* BST::getSuccessor(Node* node) {
    if (!node) return nullptr;
    if (node->right) return getMin(node->right);

    Node* curr = node->parent;
    Node* p = node;

    while (curr && curr->right == p) {
        p = curr;
        curr = curr->parent;
    }
    return curr;
}

BST::Node* BST::remove(Node* node, Node* prnt, int key) {
    if (!node) return nullptr;
    
    if (key < node->val) node->left = remove(node->left, node, key);
    else if (key > node->val) node->right = remove(node->right, node, key);
    else {
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }
        else if (!node->left) {
            Node* tmp = node->right;
            tmp->parent = prnt;

            delete node;
            return tmp;
        }
        else if (!node->right) {
            Node* tmp = node->left;
            tmp->parent = prnt;

            delete node;
            return tmp;
        }
        else {
            Node* tmp = getMin(node->right);
            node->val = tmp->val;
            node->right = remove(node->right, node, tmp->val);
        }
    }
    return node;
}

#endif