#include "bookTree.h"
BookTree::BookTree() { _root = nullptr; }

BookTree::~BookTree() {
    clear(_root);
}

BNode* BookTree::makeSplay(BNode* root, string key) {
    // Key is already at root
    if (_root->_key == key) {
        return root;
    }
    BNode* head = nullptr;

    // Key in left tree
    if (key < root->_key) {
        // Key does not exist
        if (root->_left == nullptr) {
            return root;
        }

        // Zig
        if (root->_left->_key == key && root == _root) {
            return rightRotate(root);
        }

        // Key in left subtree
        if (key < root->_left->_key) {
            // Key does not exist
            if (root->_left->_left == nullptr) {
                return root;
            }
            
            // Zig Zig
            if (root->_left->_left->_key == key) {
                head = rightRotate(root);
                return rightRotate(head);
            }
            // Recursively update child and recall makeSplay
            else {
                root->_left = makeSplay(root->_left, key);
                return makeSplay(_root, key);
            }
        }
        // Key in right subtree
        else {
            // Key does not exist
            if (root->_left->_right == nullptr) {
                return root;
            }

            // Zig Zag
            if (root->_left->_right->_key == key) {
                // LR
                root->_left = leftRotate(root->_left);
                head = rightRotate(root);
                return head;
            }
            // Recursively update child and recall makeSplay
            else {
                root->_left = makeSplay(root->_left, key);
                return makeSplay(_root, key);
            }
        }
    }
    // Key in right tree
    else {
        // Key does not exist
        if (root->_right == nullptr) {
            return root;
        }

        // Zag
        if (root->_right->_key == key && root == _root) {
            return leftRotate(root);
        }

        // Key in left subtree
        if (key < root->_right->_key) {
            // Key does not exist
            if (root->_right->_left == nullptr) {
                return root;
            }

            // Zag Zig
            if (root->_right->_left->_key == key) {
                //RL
                root->_right = rightRotate(root->_right);
                head = leftRotate(root);
                return head;
            }
            // Recursively update child and recall makeSplay
            else {
                root->_right = makeSplay(root->_right, key);
                return makeSplay(_root, key);
            }
        }
        // Key in right subtree
        else {
            if (root->_right->_right == nullptr) {
                return root;
            }

            // Zig Zig
            if (root->_right->_right->_key == key) {
                head = leftRotate(root);
                return leftRotate(head);
            }
            // Recursively update child and recall makeSplay
            else {
                root->_right = makeSplay(root->_right, key);
                return makeSplay(_root, key);
            }
        }
    }
    cout << "how" << endl;
    return root;
}
BNode* BookTree::rightRotate(BNode* x) {
    BNode* grand = x->_parent;
    BNode* head = x->_left;
    BNode* headRight = head->_right;

    // Rotates around root
    if (x->_parent == nullptr) {
        _root = head;
        head->_parent = nullptr;
    }
    // Updates parent of head if it exists
    else {
        if (head->_key < grand->_key) {
            grand->_left = head;
        }
        else {
            grand->_right = head;
        }
    }

    // Perform rotation
    head->_right = x;
    x->_parent = head;
    x->_left = headRight;
    head->_parent = grand;

    // Updates child's parent
    if (headRight != nullptr) {
        headRight->_parent = x;
    }

    return head;
}
BNode* BookTree::leftRotate(BNode* x) {
    BNode* grand = x->_parent;
    BNode* head = x->_right;
    BNode* headLeft = head->_left;

    // Rotates around root
    if (x->_parent == nullptr) {
        _root = head;
        head->_parent = nullptr;
    }
    // Updates parent of head if it exists
    else {
        if (head->_key < grand->_key) {
            grand->_left = head;
        }
        else {
            grand->_right = head;
        }
    }

    // Perform rotation
    head->_left = x;
    x->_parent = head;
    x->_right = headLeft;
    head->_parent = grand;

    // Updates child's parent
    if (headLeft != nullptr) {
        headLeft->_parent = x;
    }

    return head;
}

bool BookTree::insert(string key, string author, string text) {
    // Tree is empty, insert at root
    if (_root == nullptr) {
        _root = new BNode(key, author, text);
        return true;
    }

    // Traverses tree iteratively
    BNode* tmp = _root;
    while (tmp != nullptr) {
        // Key in left subtree
        if (key < tmp->_key) {
            if (tmp->_left == nullptr) {
                BNode* addNode = new BNode(key, author, text);
                tmp->_left = addNode;
                tmp->_left->_parent = tmp;
                makeSplay(_root, key);
                return true;
            }
            else {
                tmp = tmp->_left;
            }
        }
        // Key in right subtree
        else if (key > tmp->_key) {
            if (tmp->_right == nullptr) {
                BNode* addNode = new BNode(key, author, text);
                tmp->_right = addNode;
                tmp->_right->_parent = tmp;
                makeSplay(_root, key);
                return true;
            }
            else {
                tmp = tmp->_right;
            }
        }
        // Key already exists
        else {
            makeSplay(_root, key);
            return false;
        }
    }
    return false;
}

void BookTree::clear(BNode* root) {
    if (root == nullptr) {
        return;
    }
    clear(root->_left);
    clear(root->_right);

    delete root;
}

void BookTree::inorderHelp(BNode* root, bool verbose) const {
    /***********************************
     *      Do not modify
     * ********************************/
    if (root != nullptr) {
        if (verbose) {
            cout << "(";
            inorderHelp(root->_left, verbose);
            cout << root->_key << ":" << root->_author;
            root->_tree.dump();
            inorderHelp(root->_right, verbose);
            cout << ")";
        } else {
            inorderHelp(root->_left, verbose);
            cout << root->_key;
            inorderHelp(root->_right, verbose);
        }
    }
}

void BookTree::dump(bool verbose) const {
    /***********************************
     *      Do not modify
     * ********************************/
    inorderHelp(_root, verbose);
}

int BookTree::findFrequency(string title, string word) {
    BNode* find = makeSplay(_root, title);

    // Checks if title exists
    if (find == nullptr) {
        cout << "title does not exist" << endl;
        return -1;
    }

    return find->findFrequency(word);
}

void BookTree::dumpTitle(string title) {
    BNode* find = makeSplay(_root, title);

    // Checks if title exists
    if (find == nullptr) {
        cout << "title does not exist" << endl;
        return;
    }

    find->_tree.dump();
}

int BookTree::searchCount(string title, string word) {
    BNode* find = makeSplay(_root, title);

    // Checks if title exists
    if (find == nullptr) {
        cout << "title does not exist" << endl;
        return 0;
    }

    return find->searchCount(word);
}

int BookTree::getTextTreeHeight(string title) {
    BNode* find = makeSplay(_root, title);

    // Checks if title exists
    if (find == nullptr) {
        cout << "title does not exist" << endl;
        return -1;
    }

    return find->getTextTreeHeight();
}

int BookTree::getWordHeight(string title, string word) {
    BNode* find = makeSplay(_root, title);

    // Checks if title exists
    if (find == nullptr) {
        cout << "title does not exist" << endl;
        return -1;
    }

    return find->getNodeHeight(word);
}

string BookTree::getRootKey() {
    /***********************************
     *      Do not modify
     * ********************************/
    return _root->_key;
}

void BookTree::loadData(string dataFile) {
    /***********************************
     *      This function is implemented
     *      to help you. You should't need
     *      to modify it.
     * ********************************/
    //read the entire file at once
    std::ifstream t(dataFile);
    std::stringstream buffer;
    buffer << t.rdbuf();

    //time to parse the information
    string titleDelimiter = "<==>";
    string itemsDeleimiter = "<=>";
    string s = buffer.str();
    size_t pos = 0;
    string token;
    while ((pos = s.find(titleDelimiter)) != string::npos) {
        token = s.substr(0, pos);  //token is complete data for one title
        //get the title
        int tempPos = token.find(itemsDeleimiter);
        string title = token.substr(0, tempPos);
        //convert title to lower case
        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        token.erase(0, tempPos + itemsDeleimiter.length() + 1);
        //get the author
        tempPos = token.find(itemsDeleimiter);
        string author = token.substr(0, tempPos);
        //convert author to lower case
        std::transform(author.begin(), author.end(), author.begin(), ::tolower);
        token.erase(0, tempPos + itemsDeleimiter.length() + 1);
        //get the text
        string text = token.substr(0, token.length() - 1);  //remove last newline
                                                            //clean up the text, remove all non-alphanumeric characters
        for (std::string::iterator iter = text.begin(); iter != text.end();) {
            if (!std::isalnum(*iter) && *iter != ' ')
                iter = text.erase(iter);
            else
                ++iter;  // not erased, increment iterator
        }
        //convert text to lower case
        std::transform(text.begin(), text.end(), text.begin(), ::tolower);

        insert(title, author, text);

        //move to info for the next title
        s.erase(0, pos + titleDelimiter.length() + 1);
    }
}

void BookTree::dump(){
    dumpTest(_root);
    cout << endl;
}
void BookTree::dumpTest(BNode* aNode){
    if (aNode != nullptr){
        cout << "[";
        dumpTest(aNode->_left);
        if (aNode == _root) {
            cout << "~";
        }
        cout << aNode->_key << ":";
        // if (aNode->_parent) cout << aNode->_parent->_key << ":";
        // else cout << "empty:";
        // if (aNode->_left) cout << aNode->_left->_key << ":";
        // else cout << "empty:";
        // if (aNode->_right) cout << aNode->_right->_key;
        // else cout << "empty:";
        dumpTest(aNode->_right);
        cout << "]";
    }
}