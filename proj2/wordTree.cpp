#include "wordTree.h"

WordTree::~WordTree(){
    clearTree(_root);
}

void WordTree::updateHeight(Node *aNode) {
    if (aNode == nullptr) {
        return;
    }
    // Increments height based on tallest child
    aNode->_height = maxHeight(aNode->_left, aNode->_right) + 1;
}

void WordTree::clearTree(Node* aNode){
    if (aNode == nullptr) {
        return;
    }
    clearTree(aNode->_left);
    clearTree(aNode->_right);

    delete aNode;
}

void WordTree::inOrder(Node* aNode, std::ostream& ostr){
    /***********************************
     *      Do not modify
     * ********************************/
    if (aNode != nullptr){
        ostr << "[";
        inOrder(aNode->_left, ostr);
        if (aNode == _root) {
            ostr << "~";
        }
        ostr << aNode->_value << ":" << aNode->_count << ":" << aNode->_height;
        inOrder(aNode->_right, ostr);
        ostr << "]";
    }
}

Node* WordTree::find(Node* aNode, const string& element){
    if (aNode == nullptr || aNode->_value == element) {
        return aNode;
    }
    // Traverses left
    else if (aNode->_value > element) {
        return find(aNode->_left, element);
    }
    // Traverses right
    return find(aNode->_right, element);
}

Node* WordTree::find(const string& element){
    return find(_root, element);
}

Node* WordTree::leftRotation(Node* aNode){
    Node* head = aNode->_right;
    Node* headLeft = head->_left;

    // Rotates around root
    if (aNode->_parent == nullptr) {
        _root = head;
        head->_parent = nullptr;
    }

    // Perform rotation
    head->_left = aNode;
    aNode->_parent = head;
    aNode->_right = headLeft;

    // Updates child's parent
    if (headLeft != nullptr) {
        headLeft->_parent = aNode;
    }

    updateHeight(aNode);
    updateHeight(head);

    return head;
}

Node* WordTree::rightRotation(Node* aNode){
    Node* head = aNode->_left;
    Node* headRight = head->_right;

    // Rotates around root
    if (aNode->_parent == nullptr) {
        _root = head;
        head->_parent = nullptr;
    }

    // Perform rotation
    head->_right = aNode;
    aNode->_parent = head;
    aNode->_left = headRight;

    // Updates child's parent
    if (headRight != nullptr) {
        headRight->_parent = aNode;
    }

    updateHeight(aNode);
    updateHeight(head);

    return head;
}

int WordTree::checkBalance(Node* aNode){
    // Returns the difference in height between aNode's children; Positive if left child is taller, negative otherwise
    int leftHeight = aNode->_left == nullptr ? -1 : aNode->_left->_height;
    int rightHeight = aNode->_right == nullptr ? -1 : aNode->_right->_height;

    return leftHeight - rightHeight;
}

Node* WordTree::reBalance(Node* aNode){
    Node* unbalChild;
    int bal = checkBalance(aNode);

    // Unbalanced on left side of aNode
    if (bal > 1) {
        unbalChild = aNode->_left;

        // Left Left imbalance 
        if (checkBalance(unbalChild) > 0) {
            return rightRotation(aNode);
        }
        // Left Right
        else {
            aNode->_left = leftRotation(aNode->_left);
            return rightRotation(aNode);
        }
    }
    // Unbalanced on right side of aNode
    else if (bal < -1) {
        unbalChild = aNode->_right;

        // Right Right imbalance
        if (checkBalance(unbalChild) < 0) {
            return leftRotation(aNode);
        }
        // Right Left imbalance
        else {
            aNode->_right = rightRotation(aNode->_right);
            return leftRotation(aNode);
        }
    }

    return aNode;
}

void WordTree::insert(const string& element){
    Node* exists = find(element);

    // Check if element already exists
    if (exists) {
        exists->_count++;
        return;
    }

    insert(element, _root);
}

Node* WordTree::insert(const string& element, Node*& aNode){
    // Inserts element
    if (aNode == nullptr) {
        aNode = new Node(element);
        aNode->_count++;
        return aNode;
    }

    // Traverses tree while updating parent
    if (element < aNode->_value) {
        aNode->_left = insert(element, aNode->_left);
        aNode->_left->_parent = aNode;
    }
    else if (element > aNode->_value) {
        aNode->_right = insert(element, aNode->_right);
        aNode->_right->_parent = aNode;
    }
    else {
        return aNode;
    }

    updateHeight(aNode);
    return reBalance(aNode);
}

void WordTree::dump(std::ostream& ostr){
    /***********************************
     *      Do not modify
     * ********************************/
    inOrder(_root, ostr);
}

int WordTree::searchCount(string word){
    return searchCountHelp(_root, word, 0);
}

int WordTree::searchCountHelp(Node* aNode, string word, int counter){
    if (aNode == nullptr || aNode->_value == word) {
        return counter;
    }
    else if (aNode->_value > word) {
        return searchCountHelp(aNode->_left, word, ++counter);
    }
    return searchCountHelp(aNode->_right, word, ++counter);
}

int WordTree::getRootHeight(){
    return _root->_height;
}

int WordTree::getNodeHeight(string word){
    return getNodeHeightHelp(_root, word);
}

int WordTree::getNodeHeightHelp(Node* aNode, string word){
    Node* search = find(word);
    
    // Check if word exists in tree
    if (search == nullptr) {
        return -1;
    }
    return search->_height;
}

int WordTree::maxHeight(Node* a, Node* b) {
    // Height equals -1 if nullptr
    int aHeight = (a == nullptr ? -1 : a->_height);
    int bHeight = (b == nullptr ? -1 : b->_height);

    // Returns taller child
    return aHeight >= bHeight ? aHeight : bHeight;
}