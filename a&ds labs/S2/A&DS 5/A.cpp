#include <iostream>

using namespace std;

struct Node {
    int val;
    Node *ls;
    Node *rs;
    Node *parent;

    Node(int x, Node *parent) {
        this->val = x;
        this->rs = this->ls = nullptr;
        this->parent = parent;
    }
};

Node *findUpR(Node *cur) {
    if (cur == nullptr || cur->parent == nullptr) {
        return nullptr;
    }
    if (cur->parent->ls == cur) {
        return cur->parent;
    }
    return findUpR(cur->parent);
}

Node *findUpL(Node *cur) {
    if (cur == nullptr || cur->parent == nullptr) {
        return nullptr;
    }
    if (cur->parent->rs == cur) {
        return cur->parent;
    }
    return findUpL(cur->parent);
}

Node *findL(Node *cur) {
    if (cur == nullptr) {
        return nullptr;
    }
    while (cur->ls != nullptr) {
        cur = cur->ls;
    }
    return cur;
}

Node *findR(Node *cur) {
    if (cur == nullptr) {
        return nullptr;
    }
    while (cur->rs != nullptr) {
        cur = cur->rs;
    }
    return cur;
}

Node *findDwL(Node *cur) {
    if (cur == nullptr) {
        return nullptr;
    }
    return findR(cur->ls);
}

Node *findDwR(Node *cur) {
    if (cur == nullptr) {
        return nullptr;
    }
    return findL(cur->rs);
}

Node *root;

void insert(int n, Node *node) {
    if (n > node->val) {
        if (node->rs == nullptr) {
            node->rs = new Node(n, node);
        } else {
            insert(n, node->rs);
        }
    } else if (n == node->val) {
        return;
    } else {
        if (node->ls == nullptr) {
            node->ls = new Node(n, node);
        } else {
            insert(n, node->ls);
        }
    }
}

void del(int n, Node *node) {
    if (node == nullptr) {
        return;
    }
    if (n > node->val) {
        del(n, node->rs);
    } else if (n == node->val) {
        if (node->ls == nullptr) {
            if (node->parent == nullptr) {
                root = node->rs;
            } else {
                if (node->parent->ls == node) {
                    node->parent->ls = node->rs;
                } else {
                    node->parent->rs = node->rs;
                }
            }
            if (node->rs != nullptr) {
                node->rs->parent = node->parent;
            }
            delete (node);
        } else {
            Node *cur = node->ls;
            while (cur->rs != nullptr) {
                cur = cur->rs;
            }
            if (cur->parent->ls == cur) {
                cur->parent->ls = cur->ls;
                if (cur->ls != nullptr) {
                    cur->ls->parent = cur->parent;
                }
            } else {
                cur->parent->rs = cur->ls;
                if (cur->ls != nullptr) {
                    cur->ls->parent = cur->parent;
                }
            }
            node->val = cur->val;
            delete (cur);
        }
    } else {
        del(n, node->ls);
    }
}

bool exists(int n, Node *node) {
    if (node == nullptr) {
        return false;
    }
    if (n > node->val) {
        return exists(n, node->rs);
    } else if (n == node->val) {
        return true;
    } else {
        return exists(n, node->ls);
    }
}

int nodeMax(Node *a, Node *b) {
    if (a == nullptr) {
        if (b == nullptr) {
            return INT_MAX;
        }
        return b->val;
    } else {
        if (b == nullptr) {
            return a->val;
        }
        return a->val > b->val ? a->val : b->val;
    }
}

int nodeMin(Node *a, Node *b) {
    if (a == nullptr) {
        if (b == nullptr) {
            return INT_MAX;
        }
        return b->val;
    } else {
        if (b == nullptr) {
            return a->val;
        }
        return a->val < b->val ? a->val : b->val;
    }
}

int findNext(int n, Node *node) {
    if (node == nullptr) {
        return INT_MAX;
    }
    if (n > node->val) {
        if (node->rs == nullptr) {
            return nodeMin(findUpR(node), nullptr);
        } else {
            return findNext(n, node->rs);
        }
    } else if (n == node->val) {
        return nodeMin(findUpR(node), findDwR(node));
    } else {
        if (node->ls == nullptr) {
            return node->val;
        } else {
            return findNext(n, node->ls);
        }
    }
}

int findPrev(int n, Node *node) {
    if (node == nullptr) {
        return INT_MAX;
    }
    if (n > node->val) {
        if (node->rs == nullptr) {
            return node->val;
        } else {
            return findPrev(n, node->rs);
        }
    } else if (n == node->val) {
        return nodeMax(findUpL(node), findDwL(node));
    } else {
        if (node->ls == nullptr) {
            return nodeMax(nullptr, findUpL(node));
        } else {
            return findPrev(n, node->ls);
        }
    }
}

int main() {
    string s;
    int x, t;
    while (cin >> s) {
        cin >> x;
        switch (s[0]) {
            case 'i':
                if (root == nullptr) {
                    root = new Node(x, nullptr);
                } else {
                    insert(x, root);
                }
                break;
            case 'd':
                del(x, root);
                break;
            case 'e':
                cout << (exists(x, root) ? "true" : "false") << '\n';
                break;
            case 'n':
                t = findNext(x, root);
                if (t == INT_MAX) {
                    cout << "none\n";
                } else {
                    cout << t << '\n';
                }
                break;
            case 'p':
                t = findPrev(x, root);
                if (t == INT_MAX) {
                    cout << "none\n";
                } else {
                    cout << t << '\n';
                }
        }
    }
    return 0;
}