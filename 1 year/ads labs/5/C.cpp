#include <vector>
#include <cstdio>
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


    Node *searchNull(Node *t, int &ind) {
        Node *cur = t;
        ind = getSize(cur->ls);

        while (hasZeros(cur)) {
            if (cur->ls != nullptr && hasZeros(cur->ls)) {
                cur = cur->ls;
                ind = ind - getSize(cur->rs) - 1;
            } else if (cur->val == 0) {
                break;
            } else {
                cur = cur->rs;
                ind += getSize(cur->ls);
                ind++;
            }
        }
        return cur;
    }

    Node *remove(Node *r, int key) {
        auto p = split(r, key);
        return merge(p.first, split(p.second, 1).second);
    }

    void insert(int ind, int val) {
        Node *z;
        int i;

        auto p = split(root, ind);
        z = searchNull(p.second, i);
        if (z != nullptr && z->val == 0) {
            p.second = remove(p.second, i);
        }

        root = merge(merge(p.first, new Node(val)), p.second);
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

    void fillZeros(int n) {
        for (int i = 0; i < n; ++i) {
            root = merge(new Node(0), root);
        }
    }
};

int main() {;
    int n, m, t;
    vector<int> ans;
    scanf("%d %d", &n, &m);
    TreapArray treapArray;
    treapArray.fillZeros(m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &t);
        treapArray.insert(t - 1, i + 1);
    }

    treapArray.toArray(ans);
    while (!ans.empty() && ans.back() == 0) {
        ans.pop_back();
    }
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); ++i) {
        printf("%d ", ans[i]);
    }
    return 0;
}