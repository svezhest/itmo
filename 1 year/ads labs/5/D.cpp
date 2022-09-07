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

struct TreapArray {
    struct Node {
        int val, sz, key;
        long sum;
        Node *ls, *rs, *parent;
        bool inverted;

        explicit Node(int val) {
            this->val = sum = val;
            inverted = false;
            key = get_rand();
            sz = 1;
            ls = rs = parent = nullptr;
        }

        void setRight(Node *node) {
            if ((this->rs = node) != nullptr) {
                this->rs->parent = this;
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

    static void setInverted(Node *node) {
        if (node != nullptr) {
            node->inverted = !node->inverted;
        }
    }

    Node *root = nullptr;

    static int getSize(Node *node) {
        return node == nullptr ? 0 : node->sz;
    }

    static long getSum(Node *node) {
        return node == nullptr ? 0 : node->sum;
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
        node->sum = node->val + getSum(node->ls) + getSum(node->rs);
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

    pair<Node *, Node *> splitByValue(Node *node, int x) {
        if (node == nullptr) {
            return {nullptr, nullptr};
        }
        update(node);
        if (node->val < x) {
            auto p = splitByValue(node->rs, x);
            node->setRight(p.first);
            return {node, p.second};
        } else {
            auto p = splitByValue(node->ls, x);
            node->setLeft(p.second);
            return {p.first, node};
        }
    }

    pair<Node *, Node *> splitByValueLeft(Node *node, int x) {
        if (node == nullptr) {
            return {nullptr, nullptr};
        }
        update(node);
        if (node->val <= x) {
            auto p = splitByValueLeft(node->rs, x);
            node->setRight(p.first);
            return {node, p.second};
        } else {
            auto p = splitByValueLeft(node->ls, x);
            node->setLeft(p.second);
            return {p.first, node};
        }
    }

    Node *get(Node *node, int ind) {
        if (node == nullptr) {
            return nullptr;
        }
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

//    int findInSorted(Node *node, int x) {
//        if (node == nullptr) {
//            return -1;
//        }
//        int sz = getSize(node->ls);
//        if (node->val == x) {
//            return sz;
//        }
//        if (node->val > x) {
//            return findInSorted(node->ls, x);
//        } else {
//            return sz + 1 + findInSorted(node->rs, x);
//        }
//    }

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

    void remove(int key) {
        auto p = split(root, key);
        root = merge(p.first, split(p.second, 1).second);
    }

    void insert(int ind, int val) {
        insert(ind, new Node(val));
    }

    void insert(int ind, Node *node) {
        auto p = split(root, ind);
        root = merge(merge(p.first, node), p.second);
    }

    Node *cut(int l, int r) {
        auto p = split(root, l);
        auto p2 = split(p.second, r - l + 1);
        root = merge(p.first, p2.second);
        return p2.first;
    }

    void toArray(Node *node, std::vector<int> &array) {
        if (node != nullptr) {
            update(node);
            toArray(node->ls, array);
            array.push_back(node->val);
            toArray(node->rs, array);
        }
    }

    void toArray(std::vector<int> &array) {
        toArray(root, array);
    }

    long findSum(int l, int r) {
        auto p = splitByValue(root, l);
        auto p2 = splitByValueLeft(p.second, r);
        long res = getSum(p2.first);
        root = merge(p.first, merge(p2.first, p2.second));
        return res;
    }

    void invert(int l, int r) {
        auto p = split(root, l);
        auto p2 = split(p.second, r - l + 1);
        setInverted(p2.first);
        root = merge(p.first, merge(p2.first, p2.second));
    }

    bool exists(int n) {
        return exists(n, root);
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

    void insertByValue(int val) {
        insertByValue(val, new Node(val));
    }

    void insertByValue(int ind, Node *node) {
        auto p = splitByValue(root, ind);
        root = merge(merge(p.first, node), p.second);
    }

    void fillZeros(int n) {
        for (int i = 0; i < n; ++i) {
            root = merge(new Node(0), root);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    TreapArray treapArray;
    int n;
    cin >> n;
    vector<int> ans;
    long last = 0;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        switch (s[0]) {
            case '+': {
                int t;
                cin >> t;
                t = static_cast<int>((static_cast<long>(t) + last) % 1000000000);
                if (!treapArray.exists(t)) {
                    treapArray.insertByValue(t);
                }
                last = 0;
            }
                break;
            case '?':
                int l, r;
                cin >> l >> r;
                last = treapArray.findSum(l, r);
                cout << last << '\n';
                break;
        }

//        treapArray.toArray(ans);
//        for (int i = 0; i < ans.size(); ++i) {
//            cout << ans[i] << ' ';
//        }
//        cout << '\n';
//        ans.clear();
    }

//    treapArray.toArray(ans);
//    cout << ans.size() << '\n';
//    for (int i = 0; i < ans.size(); ++i) {
//        cout << ans[i] << ' ';
//    }
    return 0;
}