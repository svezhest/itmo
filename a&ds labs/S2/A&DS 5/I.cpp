#include <iostream>
#include <random>


#define long long long
using namespace std;

random_device rd;
uniform_int_distribution<> dis(-100000, 100000);
mt19937 gen(rd());

int get_rand() {
    return dis(gen);
}

struct SomeTreap {

    struct Node {
        int val, sz, key;
        Node *ls, *rs, *parent;
        bool inverted;
        bool hasLoop = false;

        explicit Node(int val) {
            this->val = val;
            inverted = false;
            key = get_rand();
            sz = 1;
            ls = rs = parent = nullptr;
        }

        void setRight(Node *node) {
            if ((this->rs = node) != nullptr) {
                this->rs->parent     = this;
            }
            updateSize(this);
            update(this);
        }

        void setLeft(Node *node) {
            if ((this->ls = node) != nullptr) {
                this->ls->parent = this;
            }
            updateSize(this);
            update(this);
        }

        static void updateSize(Node *node) {
            if (node == nullptr) {
                return;
            }
            node->sz = 1 + getSize(node->ls) + getSize(node->rs);
        }
    };

    Node **cities;

    static void setInverted(Node *node) {
        if (node != nullptr) {
            node->inverted = !node->inverted;
        }
    }

    Node *root = nullptr;

    static int getSize(Node *node) {
        return node == nullptr ? 0 : node->sz;
    }


    static void update(Node *node) {
        if (node == nullptr) {
            return;
        }
        if (node->inverted) {
            node->inverted = false;
            setInverted(node->ls);
            setInverted(node->rs);
            Node *t = node->ls;
            node->ls = node->rs;
            node->rs = t;
        }
    }

    static void setParent(Node *node, Node *par) {
        if (node != nullptr) {
            node->parent = par;
        }
    }

    static pair<Node *, Node *> split(Node *node, int ind) {
        if (node == nullptr) {
            return {nullptr, nullptr};
        }
        update(node);
        if (getSize(node->ls) < ind) {
            auto p = split(node->rs, ind - getSize(node->ls) - 1);
            node->setRight(p.first);
            return {node, p.second};
        } else {
            auto p = split(node->ls, ind);
            node->setLeft(p.second);
            return {p.first, node};
        }
    }

////    value in the right
//    pair<Node *, Node *> splitByValue(Node *node, int x) {
//        if (node == nullptr) {
//            return {nullptr, nullptr};
//        }
//        update(node);
//        if (node->val < x) {
//            auto p = splitByValue(node->rs, x);
//            node->setRight(p.first);
//            return {node, p.second};
//        } else {
//            auto p = splitByValue(node->ls, x);
//            node->setLeft(p.second);
//            return {p.first, node};
//        }
//    }
//
//// value in the left
//    pair<Node *, Node *> splitByValueLeft(Node *node, int x) {
//        if (node == nullptr) {
//            return {nullptr, nullptr};
//        }
//        update(node);
//        if (node->val <= x) {
//            auto p = splitByValueLeft(node->rs, x);
//            node->setRight(p.first);
//            return {node, p.second};
//        } else {
//            auto p = splitByValueLeft(node->ls, x);
//            node->setLeft(p.second);
//            return {p.first, node};
//        }
//    }

    static Node *get(Node *node, int ind) {
        if (node == nullptr) {
            return nullptr;
        }
        update(node);
        int sz = getSize(node->ls);
        if (sz == ind) {
            return node;
        }
        if (sz > ind) {
            return get(node->ls, ind);
        } else {
            return get(node->rs, ind - sz - 1);
        }
    }

//    static Node *getByValue(Node *node, int val) {
//        if (node == nullptr) {
//            return nullptr;
//        }
//        if (node->val == val) {
//            return node;
//        }
//        update(node);
//        if (node->val > val) {
//            return getByValue(node->ls, val);
//        } else {
//            return getByValue(node->rs, val);
//        }
//    }

    static Node *getRoot(Node *node) {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->parent != nullptr) {
            node = node->parent;
        }
        return node;
    }

//    int indexInSorted(Node *node, int x) {
//        if (node == nullptr) {
//            return -1;
//        }
//        update(node);
//        int sz = getSize(node->ls);
//        if (node->val == x) {
//            return sz;
//        }
//        if (node->val > x) {
//            return indexInSorted(node->ls, x);
//        } else {
//            return sz + 1 + indexInSorted(node->rs, x);
//        }
//    }

    static void pushInvert(Node *node) {
        if (node == nullptr) {
            return;
        }
        if (node->ls != nullptr) {
            pushInvert(node->ls);
        }
        if (node->rs != nullptr) {
            pushInvert(node->rs);
        }
        Node *t = node->ls;
        node->ls = node->rs;
        node->rs = t;
    }

    static Node *merge(Node *A, Node *B) {
        if (A == nullptr) {
            return B;
        }
        if (B == nullptr) {
            return A;
        }
        if (A->key > B->key) {
            update(A);
            A->setRight(merge(A->rs, B));
            return A;
        } else {
            update(B);
            B->setLeft(merge(A, B->ls));
            return B;
        }
    }

    void link(int left, int right) {
        Node *l_root = getRoot(cities[left]);
        Node *r_root = getRoot(cities[right]);
        if (l_root == r_root) {
            l_root->hasLoop = true;
        } else {
            Node *l = get(l_root, 0);
            Node *r = get(r_root, 0);
            if (l->val != left) {
                if (r->val != right) {
                    pushInvert(r_root);
                }
            } else {
                if (r->val != right) {
                    merge(r_root, l_root);
                    return;
                } else {
                    pushInvert(l_root);
                }
            }
            merge(l_root, r_root);
        }
    }

    vector<Node *> trace;

    int getIndex(Node *node) {
        Node *start = node;
        if (node == nullptr) {
            return -1;
        }
        while (node->parent != nullptr) {
            node = node->parent;
            trace.push_back(node);
        }
        for (int i = trace.size() - 1; i >= 0; --i) {
            update(trace[i]);
        }
        trace.clear();
        node = start;
        int res = getSize(node->ls);
        while (node->parent != nullptr) {
            bool fromRight = node->parent->rs == node;
            node = node->parent;
            if (fromRight) {
                res += 1 + getSize(node->ls);
            }
        }
        return res;
    }

    void cut(int left, int right) {
        Node *c_root = getRoot(cities[left]);
        if (c_root != getRoot(cities[right])) {
            return;
        }
        int l_ind = getIndex(cities[left]);
        int r_ind = getIndex(cities[right]);
        if (c_root->hasLoop) {
            c_root->hasLoop = false;
            if (!((l_ind == 0 && r_ind == getSize(c_root) - 1) || (r_ind == 0 && l_ind == getSize(c_root) - 1))) {
                auto p = split(c_root, max(l_ind, r_ind));
                setParent(p.first, nullptr);
                setParent(p.second, nullptr);
                merge(p.second, p.first);
            }
        } else {
            auto p = split(c_root, max(l_ind, r_ind));
            setParent(p.first, nullptr);
            setParent(p.second, nullptr);
        }
    }

//    void remove(int key) {
//        auto p = split(root, key);
//        root = merge(p.first, split(p.second, 1).second);
//    }

    int distance(int left, int right) {
        Node *c_root = getRoot(cities[left]);
        if (c_root != getRoot(cities[right])) {
            return -1;
        }
        int dist = abs(getIndex(cities[left]) - getIndex(cities[right]));
        if (c_root->hasLoop) {
            return min(dist, getSize(c_root) - dist) - 1;
        } else {
            return dist - 1;
        }
    }
};

int main() {

//    cin.tie(nullptr);
//    ios_base::sync_with_stdio(false);

    char operation;
    int n, m, q;
    cin >> n >> m >> q;

    SomeTreap treap;
    treap.cities = new SomeTreap::Node *[n];

    for (int i = 0; i < n; i++) {
        treap.cities[i] = new SomeTreap::Node(i);
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        treap.link(min(a, b) - 1, max(a, b) - 1);
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> operation >> a >> b;
        switch (operation) {
            case '+':
                if (a != b) {
                    treap.link(min(a, b) - 1, max(a, b) - 1);
                }
                break;
            case '-':
                if (a != b) {
                    treap.cut(min(a, b) - 1, max(a, b) - 1);
                }
                break;
            case '?':
                if (a == b) {
                    cout << "0\n";
                    break;
                }
                cout << treap.distance(min(a, b) - 1, max(a, b) - 1) << '\n';
                break;
        }
    }
    return 0;
}