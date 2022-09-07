#include <iostream>
#include <random>

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
        Node *ls, *rs, *parent;
        bool inverted;

        explicit Node(int val) {
            this->val = val;
            inverted = false;
            key = get_rand();
            sz = 1;
            ls = rs = parent = nullptr;
        }

        void setRight(Node *node) {
            if ((this->rs = node) != nullptr) {
                this->rs->parent = this;
            }
            update(this);
        }

        void setLeft(Node *node) {
            if ((this->ls = node) != nullptr) {
                this->ls->parent = this;
            }
            update(this);
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

    static void update(Node *node) {
        if (node == nullptr) {
            return;
        }
        node->sz = 1 + getSize(node->ls) + getSize(node->rs);
    }

    static void updateInversion(Node *node) {
        if (node->inverted) {
            node->inverted = false;
            setInverted(node->ls);
            setInverted(node->rs);
            Node *t = node->ls;
            node->ls = node->rs;
            node->rs = t;
        }
    }

    static pair<Node *, Node *> split(Node *node, int ind) {
        if (node == nullptr) {
            return {nullptr, nullptr};
        }
        updateInversion(node);
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

    static Node *merge(Node *A, Node *B) {
        if (A == nullptr) {
            return B;
        }
        if (B == nullptr) {
            return A;
        }
        if (A->key > B->key) {
            updateInversion(A);
            A->setRight(merge(A->rs, B));
            return A;
        } else {
            updateInversion(B);
            B->setLeft(merge(A, B->ls));
            return B;
        }
    }

    Node *remove(Node *r, int key) {
        auto p = split(r, key);
        return merge(p.first, split(p.second, 1).second);
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
            updateInversion(node);
            toArray(node->ls, array);
            array.push_back(node->val);
            toArray(node->rs, array);
        }
    }

    void toArray(std::vector<int> &array) {
        toArray(root, array);
    }

    void invert(int l, int r) {
        auto p = split(root, l);
        auto p2 = split(p.second, r - l + 1);
        setInverted(p2.first);
        root = merge(p.first, merge(p2.first, p2.second));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    TreapArray treapArray;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        treapArray.insert(i - 1, i);
    }
    vector<int> ans;
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        treapArray.invert(l - 1, r - 1);
//
//        treapArray.toArray(ans);
//        for (int i = 0; i < ans.size(); ++i) {
//            cout << ans[i] << ' ';
//        }
//        cout << '\n';
//        ans.clear();
    }

    treapArray.toArray(ans);
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << ' ';
    }
    return 0;
}