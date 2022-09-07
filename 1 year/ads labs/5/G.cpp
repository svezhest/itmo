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
        bool hasZeros;

        explicit Node(int val) {
            this->val = val;
            hasZeros = val == 0;
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

    Node *root = nullptr;

    static int getSize(Node *node) {
        return node == nullptr ? 0 : node->sz;
    }

    static bool hasZeros(Node *node) {
        return node == nullptr ? false : node->hasZeros;
    }

    static void update(Node *node) {
        if (node == nullptr) {
            return;
        }
        node->sz = 1 + getSize(node->ls) + getSize(node->rs);
        node->hasZeros = node->val == 0 || hasZeros(node->ls) || hasZeros(node->rs);
    }


    static pair<Node *, Node *> split(Node *node, int ind) {
        if (node == nullptr) {
            return {nullptr, nullptr};
        }
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
            A->setRight(merge(A->rs, B));
            return A;
        } else {
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
            toArray(node->ls, array);
            array.push_back(node->val);
            toArray(node->rs, array);
        }
    }

    void toArray(std::vector<int> &array) {
        toArray(root, array);
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
        TreapArray::Node *part = treapArray.cut(l - 1, r - 1);
        treapArray.insert(0, part);
    }

    treapArray.toArray(ans);
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << ' ';
    }
    return 0;
}