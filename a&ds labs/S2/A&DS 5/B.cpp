#include <iostream>
#include <random>

using namespace std;
random_device rd;
uniform_int_distribution<> dis(-100000, 100000);
mt19937 gen(rd());

int get_rand() {
    return dis(gen);
}

class Treap {
private:
    struct Node {
        int x;
        int y;
        Node *rs;
        Node *ls;
        Node *parent;

        Node(int val) {
            this->x = val;
            this->y = get_rand();
            this->rs = this->ls = this->parent = nullptr;
        }

        void setRight(Node *node) {
            if ((this->rs = node) != nullptr) {
                this->rs->parent = this;
            }
        }

        void setLeft(Node *node) {
            if ((this->ls = node) != nullptr) {
                this->ls->parent = this;
            }
        }
    };

    Node *root = nullptr;

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

    pair<Node *, Node *> split(Node *A, int x) {
        if (A == nullptr) {
            return {nullptr, nullptr};
        }
        pair < Node * , Node * > p;
        if (A->x < x) {
            p = split(A->rs, x);
            A->setRight(p.first);
            return {A, p.second};
        } else {
            p = split(A->ls, x);
            A->setLeft(p.second);
            return {p.first, A};
        }
    }

    Node *merge(Node *A, Node *B) {
        if (A == nullptr) {
            return B;
        }
        if (B == nullptr) {
            return A;
        }
        if (A->y > B->y) {
            A->setRight(merge(A->rs, B));
            return A;
        } else {
            B->setLeft(merge(A, B->ls));
            return B;
        }
    }

    Node *insert(Node *A, Node *node) {
        if (A == nullptr) {
            return node;
        }
        if (A->x == node->x) {
            return A;
        }
        pair < Node * , Node * > p;
        if (node->y > A->y) {
            p = split(A, node->x);
            node->setLeft(p.first);
            node->setRight(p.second);
            return node;
        } else {
            if (node->x < A->x) {
                A->setLeft(insert(A->ls, node));
            } else {
                A->setRight(insert(A->rs, node));
            }
            return A;
        }
    }

    Node *del(Node *A, int val) {
        if (A == nullptr) {
            return nullptr;
        }
        if (val < A->x) {
            A->setLeft(del(A->ls, val));
        } else if (val == A->x) {
            Node *r = merge(A->ls, A->rs);
            if (r != nullptr) {
                r->parent = nullptr;
            }
            return r;
        } else {
            A->setRight(del(A->rs, val));
        }
        return A;
    }

    bool exists(int n, Node *node) {
        if (node == nullptr) {
            return false;
        }
        if (n > node->x) {
            return exists(n, node->rs);
        } else if (n == node->x) {
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
            return b->x;
        } else {
            if (b == nullptr) {
                return a->x;
            }
            return max(a->x, b->x);
        }
    }

    int nodeMin(Node *a, Node *b) {
        if (a == nullptr) {
            if (b == nullptr) {
                return INT_MAX;
            }
            return b->x;
        } else {
            if (b == nullptr) {
                return a->x;
            }
            return min(a->x, b->x);
        }
    }

    int findNext(int n, Node *node) {
        if (node == nullptr) {
            return INT_MAX;
        }
        if (n > node->x) {
            if (node->rs == nullptr) {
                return nodeMin(findUpR(node), nullptr);
            } else {
                return findNext(n, node->rs);
            }
        } else if (n == node->x) {
            return nodeMin(findUpR(node), findDwR(node));
        } else {
            if (node->ls == nullptr) {
                return node->x;
            } else {
                return findNext(n, node->ls);
            }
        }
    }

    int findPrev(int n, Node *node) {
        if (node == nullptr) {
            return INT_MAX;
        }
        if (n > node->x) {
            if (node->rs == nullptr) {
                return node->x;
            } else {
                return findPrev(n, node->rs);
            }
        } else if (n == node->x) {
            return nodeMax(findUpL(node), findDwL(node));
        } else {
            if (node->ls == nullptr) {
                return nodeMax(nullptr, findUpL(node));
            } else {
                return findPrev(n, node->ls);
            }
        }
    }

public:
    void insert(int x) {
        if (!exists(x)) {
            root = insert(root, new Node(x));
        }
    }

    void del(int x) {
        root = del(root, x);
    }

    bool exists(int x) {
        return exists(x, root);
    }

    int findNext(int x) {
        return findNext(x, root);
    }

    int findPrev(int x) {
        return findPrev(x, root);
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s;
    Treap treap;
    int x, t;
    while (cin >> s) {
        cin >> x;
        switch (s[0]) {
            case 'i':
                treap.insert(x);
                break;
            case 'd':
                treap.del(x);
                break;
            case 'e':
                cout << (treap.exists(x) ? "true" : "false") << '\n';
                break;
            case 'n':
                t = treap.findNext(x);
                if (t == INT_MAX) {
                    cout << "none\n";
                } else {
                    cout << t << '\n';
                }
                break;
            case 'p':
                t = treap.findPrev(x);
                if (t == INT_MAX) {
                    cout << "none\n";
                } else {
                    cout << t << '\n';
                }
        }
    }
    return 0;
}