#pragma once

#include <iostream>
#include <cmath>
#include <optional>
#include <memory>
#include <utility>
#include <vector>
#include <set>
#include <queue>
#include <iomanip>

class Point {
private:
    double x_val;
    double y_val;
public:

    explicit Point(double x = 0, double y = 0) : x_val(x), y_val(y) {}

    [[nodiscard]] double x() const {
        return x_val;
    }

    [[nodiscard]] double y() const {
        return y_val;
    }

    [[nodiscard]] double distance(const Point &other) const {
        return sqrt(pow(x_val - other.x_val, 2) + pow(y_val - other.y_val, 2));
    }

    bool operator<(const Point &other) const {
        if (x_val < other.x_val) {
            return true;
        } else if (x_val > other.x_val) {
            return false;
        } else {
            return y_val < other.y_val;
        }
    }

    bool operator>(const Point &other) const {
        if (x_val > other.x_val) {
            return true;
        } else if (x_val < other.x_val) {
            return false;
        } else {
            return y_val > other.y_val;
        }
    }

    bool operator<=(const Point &other) const {
        if (x_val < other.x_val) {
            return true;
        } else if (x_val > other.x_val) {
            return false;
        } else {
            return y_val <= other.y_val;
        }
    }

    bool operator>=(const Point &other) const {
        if (x_val > other.x_val) {
            return true;
        } else if (x_val < other.x_val) {
            return false;
        } else {
            return y_val >= other.y_val;
        }
    }

private:
    template<class T>
    static bool almost_equal(T x, T y, int ulp) {
        // the machine epsilon has to be scaled to the magnitude of the values used
        // and multiplied by the desired precision in ULPs (units in the last place)
        return std::fabs(x - y) <= std::numeric_limits<T>::epsilon() * std::fabs(x + y) * ulp
               // unless the result is subnormal
               || std::fabs(x - y) < std::numeric_limits<T>::min();
    }

public:
    friend bool operator==(const Point &first, const Point &second) {
        return Point::almost_equal(first.x_val, second.x_val, 2) && almost_equal(first.y_val, second.y_val, 2);
    }

    friend bool operator!=(const Point &first, const Point &second) {
        return !(first == second);
    }

    friend std::ostream &operator<<(std::ostream &out, const Point &point) {
        out << "point {x: " << std::setw(6) << point.x_val << "; y: " << std::setw(6) << point.y_val << "}";
        return out;
    }

};

class Rect {
    double xmin_val;
    double xmax_val;
    double ymin_val;
    double ymax_val;

    static double my_abs(double x) {
        return x < 0 ? -x : x;
    }

public:

    Rect(const Point &corner1, const Point &corner2) {
        xmin_val = std::min(corner1.x(), corner2.x());
        xmax_val = std::max(corner1.x(), corner2.x());
        ymin_val = std::min(corner1.y(), corner2.y());
        ymax_val = std::max(corner1.y(), corner2.y());
    }

    [[nodiscard]] double xmin() const {
        return xmin_val;
    }

    [[nodiscard]] double ymin() const {
        return ymin_val;
    }

    [[nodiscard]] double xmax() const {
        return xmax_val;
    }

    [[nodiscard]] double ymax() const {
        return ymax_val;
    }

    [[nodiscard]] double distance(const Point &p) const {
        if (contains(p)) {
            return 0;
        }
        double x_closest = xmin_val;
        if (my_abs(p.x() - xmax_val) < my_abs(p.x() - xmin_val)) {
            x_closest = xmax_val;
        }
        double y_closest = ymin_val;
        if (my_abs(p.y() - ymax_val) < my_abs(p.y() - ymin_val)) {
            y_closest = ymax_val;
        }
        if (xmin() <= p.x() && p.x() <= xmax()) {
            return my_abs(p.y() - y_closest);
        }
        if (ymin() <= p.y() && p.y() <= ymax()) {
            return my_abs(p.x() - x_closest);
        }
        return p.distance(Point(x_closest, y_closest));
    }

    [[nodiscard]] bool contains(const Point &p) const {
        return xmin_val <= p.x() && p.x() <= xmax_val && ymin_val <= p.y() && p.y() <= ymax_val;
    }

    [[nodiscard]] bool intersects(const Rect &other) const {
        return other.contains(Point(xmax_val, ymax_val)) || other.contains(Point(xmin_val, ymin_val)) ||
               contains(Point(other.xmax_val, other.ymax_val)) || contains(Point(other.xmin_val, other.ymin_val));
    }
};

template<class Compare = std::greater<double>>
class cmp {
    Point anchor;
    Compare c = Compare();
public:
    explicit cmp(const Point &p) : anchor(p) {}

    cmp(const cmp &c) : anchor(c.anchor) {}

    bool operator()(const Point &a, const Point &b) const {
        return c(a.distance(anchor), b.distance(anchor));
    }
};

namespace rbtree {

    class PointSet {
    private:
        typedef std::set<Point> set;
        set data;

    public:

        class ForwardIt {
            friend class PointSet;

            std::shared_ptr<set> saved_set;
            set::iterator inner_it;

        public:
            typedef std::forward_iterator_tag iterator_category;
            typedef ptrdiff_t difference_type;
            typedef const Point value_type;
            typedef value_type *pointer;
            typedef value_type &reference;

        public:
            ForwardIt() = default;

            ForwardIt(ForwardIt const &other) = default;

        private:
            explicit ForwardIt(const set::iterator &it, std::shared_ptr<set> to_save = nullptr) : saved_set(std::move(to_save)), inner_it(it) {}

        public:
            reference operator*() {
                return inner_it.operator*();
            }

            pointer operator->() const {
                return inner_it.operator->();
            }

            ForwardIt &operator++() {
                inner_it++;
                return *this;
            }

            ForwardIt operator++(int) {
                auto tmp = *this;
                ++*this;
                return tmp;
            }

            friend bool operator==(const ForwardIt &it1, const ForwardIt &it2) {
                return it1.inner_it == it2.inner_it;
            }

            friend bool operator!=(const ForwardIt &it1, const ForwardIt &it2) {
                return !(it1 == it2);
            }
        };

        PointSet() : data(set()) {}

        [[nodiscard]] bool empty() const {
            return data.empty();
        }

        [[nodiscard]] std::size_t size() const {
            return data.size();
        }

        void put(const Point &p) {
            data.insert(p);
        }

        [[nodiscard]] bool contains(const Point &p) const {
            return data.count(p) != 0;
        }


        [[nodiscard]] std::pair<ForwardIt, ForwardIt> range(const Rect &r) const {
            std::vector<Point> v;
            for (auto it = begin(); it != end(); it++) {
                if (r.contains(*it)) {
                    v.push_back(*it);
                }
            }
            auto subset = std::make_shared<set>(v.begin(), v.end());
            return std::pair(ForwardIt(subset->begin(), subset), ForwardIt(subset->end(), subset));
        }

        [[nodiscard]] ForwardIt begin() const {
            return ForwardIt(data.cbegin());
        }

        [[nodiscard]] ForwardIt end() const {
            return ForwardIt(data.cend());
        }

        [[nodiscard]] std::optional<Point> nearest(const Point &p) const {
            auto res = nearest(p, 1);
            if (*(res.first) != *(res.second)) {
                return *res.first;
            }
            return std::nullopt;
        }

        [[nodiscard]] std::pair<ForwardIt, ForwardIt> nearest(const Point &p, std::size_t k) const {
            cmp comp(p);
            auto heap = std::priority_queue<Point, std::vector<Point>, cmp<>>(comp, {});
            for (auto it = begin(); it != end(); it++) {
                heap.push(*it);
            }
            auto subset = std::make_shared<set>();
            for (size_t i = 0; i < k; ++i) {
                subset->insert(heap.top());
                heap.pop();
            }
            return std::pair(ForwardIt(subset->begin(), subset), ForwardIt(subset->end(), subset));
        }

        friend std::ostream &operator<<(std::ostream &out, const PointSet &pointSet) {
            for (auto it = pointSet.begin(); it != pointSet.end(); ++it) {
                out << *it;
            }
            return out;
        }
    };

}

namespace kdtree {
    class PointSet {
    private:
        struct Node {
            Point val;
            int level;
            Node *parent;
            std::unique_ptr<Node> ls = nullptr;
            std::unique_ptr<Node> rs = nullptr;

            Node(const Node &) = delete;

            explicit Node(const Point &val) : val(val), level(0), parent(nullptr) {}

            Node(const Point &val, Node *par) : val(val), level(par->level + 1), parent(par) {}
        };

        class TreeIterator {
            friend class PointSet;

        public:
            typedef std::forward_iterator_tag iterator_category;
            typedef ptrdiff_t difference_type;
            typedef const Point value_type;
            typedef value_type *pointer;
            typedef value_type &reference;


        private:
            Node *current{};
            std::shared_ptr<Node> saved_tree;

        public:
            TreeIterator() = default;

            TreeIterator(TreeIterator const &other) = default;

        private:
            explicit TreeIterator(Node *node, std::shared_ptr<Node> to_save = nullptr) : current(node), saved_tree(std::move(to_save)) {}

        public:
            reference operator*() {
                return current->val;
            }

            pointer operator->() const {
                return &(current->val);
            }

            TreeIterator &operator++() {
                if (current) {
                    if (current->parent == nullptr) {
                        current = nullptr;
                    } else if (current->parent->rs.get() == current) {
                        current = current->parent;
                    } else {
                        current = current->parent;
                        if (current->rs != nullptr) {
                            current = current->rs.get();
                            while (current->ls != nullptr || current->rs != nullptr) {
                                if (current->ls != nullptr) {
                                    current = current->ls.get();
                                } else {
                                    current = current->rs.get();
                                }
                            }
                        }
                    }
                }
                return *this;
            }

            TreeIterator operator++(int) {
                auto tmp = *this;
                ++*this;
                return tmp;
            }

            friend bool operator==(const TreeIterator &it1, const TreeIterator &it2) {
                return it1.current == it2.current;
            }

            friend bool operator!=(const TreeIterator &it1, const TreeIterator &it2) {
                return !(it1 == it2);
            }
        };

    public:
        using ForwardIt = TreeIterator;
    private:

        std::unique_ptr<Node> root = nullptr;

        template<class It>
        [[nodiscard]] std::pair<Node*, std::shared_ptr<Node>> gen_subtree(It start, It end) const {
            std::shared_ptr<Node> subtree_root = nullptr;
            Node *subtree_current = nullptr;
            for (auto i = start; i != end; i++) {
                if (subtree_root == nullptr) {
                    subtree_root = std::make_shared<Node>(*i);
                    subtree_current = subtree_root.get();
                } else {
                    subtree_current->rs = std::make_unique<Node>(*i, subtree_current);
                    subtree_current = subtree_current->rs.get();
                }
            }
            return std::make_pair(subtree_current, subtree_root);
        }

        size_t tree_size = 0;

        std::pair<bool, Node *> find(Node *node, const Point &value) const {
            if (node == nullptr) {
                return {false, nullptr};
            }
            if (node->val == value) {
                return {true, node};
            }
            if (node->level % 2 == 0 ? node->val.x() < value.x() : node->val.y() < value.y()) {
                return find(node->ls.get(), value);
            } else {
                return find(node->rs.get(), value);
            }
        }

        void insert(Node *node, const Point &value) {
            if (node == nullptr) {
                return;
            }
            if (node->val == value) {
                return;
            }
            if (node->level % 2 == 0 ? node->val.x() < value.x() : node->val.y() < value.y()) {
                if (node->ls) {
                    return insert(node->ls.get(), value);
                } else {
                    node->ls = std::make_unique<Node>(value, node);
                }
            } else {
                if (node->rs) {
                    return insert(node->rs.get(), value);
                } else {
                    node->rs = std::make_unique<Node>(value, node);
                }
            }
            ++tree_size;
        }

        void
        nearest(const cmp<> &comp, const Point &p, Node *node,
                std::priority_queue<Point, std::vector<Point>, cmp<>> &heap,
                std::priority_queue<Point, std::vector<Point>, cmp<std::less<>>> &back_heap,
                std::size_t k) const {
            if (node == nullptr) { return; }
            heap.push(node->val);
            back_heap.push(node->val);
            if (back_heap.size() > k) {
                back_heap.pop();
            }
            bool visited_left = false;
            if (node->level % 2 == 0 ? node->val.x() >= p.x() : node->val.y() >= p.y()) {
                nearest(comp, p, node->rs.get(), heap, back_heap, k);
            } else {
                visited_left = true;
                nearest(comp, p, node->ls.get(), heap, back_heap, k);
            }
            if (!visited_left) {
                if (heap.size() < k || (node->ls != nullptr && comp(back_heap.top(), node->ls->val))) {
                    nearest(comp, p, node->ls.get(), heap, back_heap, k);
                }
            } else {
                if (heap.size() < k || (node->rs != nullptr && comp(back_heap.top(), node->rs->val))) {
                    nearest(comp, p, node->rs.get(), heap, back_heap, k);
                }
            }
        }

        void range(const Rect &rect, Node *node, std::vector<Point> &vec) const {
            if (node == nullptr) {
                return;
            }
            if (node->level % 2 == 0 ? node->val.x() > rect.xmax() : node->val.y() > rect.ymax()) {
                range(rect, node->rs.get(), vec);
            } else if (node->level % 2 == 0 ? node->val.x() < rect.xmin() : node->val.y() < rect.ymin()) {
                range(rect, node->ls.get(), vec);
            } else {
                if (rect.contains(node->val)) {
                    vec.push_back(node->val);
                }
                range(rect, node->ls.get(), vec);
                range(rect, node->rs.get(), vec);
            }
        }


    public:

        PointSet() : root(nullptr), tree_size(0) {
        }

        [[nodiscard]] bool empty() const {
            return size() == 0;
        }

        [[nodiscard]] size_t size() const {
            return tree_size;
        }

        void put(const Point &value) {
            if (root) {
                insert(root.get(), value);
            } else {
                tree_size = 1;
                root = std::make_unique<Node>(value);
            }
        }

        [[nodiscard]] bool contains(const Point &value) const {
            if (root) {
                return find(root.get(), value).second;
            } else {
                return false;
            }
        }

        [[nodiscard]] std::pair<ForwardIt, ForwardIt> range(const Rect &rect) const {
            std::vector<Point> v;
            range(rect, root.get(), v);
            auto [n, r] = gen_subtree(v.begin(), v.end());
            return {TreeIterator(n, r), TreeIterator(nullptr)};
        }

        [[nodiscard]] ForwardIt begin() const {
            if (root) {
                Node *cur = root.get();
                while (cur->ls != nullptr || cur->rs != nullptr) {
                    if (cur->ls != nullptr) {
                        cur = cur->ls.get();
                    } else {
                        cur = cur->rs.get();
                    }
                }
                return TreeIterator(cur);
            } else {
                return end();
            }
        }

        [[nodiscard]] static ForwardIt end() {
            return TreeIterator(nullptr);
        }

        [[nodiscard]] std::optional<Point> nearest(const Point &p) const {
            auto res = nearest(p, 1);
            if (res.first != res.second) {
                return *res.first;
            }
            return std::nullopt;
        }

        [[nodiscard]] std::pair<ForwardIt, ForwardIt> nearest(const Point &p, std::size_t k) const {
            cmp comp(p);
            auto heap = std::priority_queue<Point, std::vector<Point>, cmp<>>(comp, {});
            cmp<std::less<>> comp_back(p);
            auto back_heap = std::priority_queue<Point, std::vector<Point>, cmp<std::less<>>>(comp_back, {});
            nearest(comp, p, root.get(), heap, back_heap, k);
            std::vector<Point> v;
            for (size_t i = 0; i < k && !heap.empty(); ++i) {
                v.push_back(heap.top());
                heap.pop();
            }
            auto [n, r] = gen_subtree(v.begin(), v.end());
            return {TreeIterator(n, r), TreeIterator(nullptr)};
        }

        friend std::ostream &operator<<(std::ostream &out, const PointSet &pointSet) {
            size_t i = 0;
            for (auto it = pointSet.begin(); it != kdtree::PointSet::end(); ++it) {
                out << *it << "  ";
                ++i;
                if (i % 3 == 0) {
                    out << '\n';
                }
            }
            return out;
        }

    };
}
