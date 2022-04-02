#include "utils.h"

struct left_type;
struct right_type;

template <typename T, typename V, typename TreeType, typename Compare>
class tree;

template <typename T, typename V, typename TreeType, typename Compare>
class tree_iterator {
  friend class tree<T, V, TreeType, Compare>;

  typename tree<T, V, TreeType, Compare>::node *current;

public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = const V;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;

  tree_iterator() = default;

  tree_iterator(tree_iterator const &other) : current(other.current) {}

  reference operator*() const noexcept {
    return static_cast<reference>(*current);
  }

  pointer operator->() const noexcept { return static_cast<pointer>(current); }

  tree_iterator &operator++() &noexcept {
    if (current) {
      if (current->r) {
        current = current->r;
        while (current->l) {
          current = current->l;
        }
      } else {
        while (current->parent && current == current->parent->r) {
          current = current->parent;
        }
        current = current->parent;
      }
    }
    return *this;
  }

  tree_iterator &operator--() &noexcept {
    if (current) {
      if (current->l) {
        current = current->l;
        while (current->r) {
          current = current->r;
        }
      } else {
        while (current->parent && current == current->parent->l) {
          current = current->parent;
        }
        current = current->parent;
      }
    }
    return *this;
  }

  tree_iterator operator++(int) &noexcept {
    auto tmp = *this;
    ++*this;
    return tmp;
  }

  tree_iterator operator--(int) &noexcept {
    auto tmp = *this;
    --*this;
    return tmp;
  }

  bool is_valid() const noexcept { return current != nullptr; }

  bool operator==(tree_iterator const &rhs) const &noexcept {
    return current == rhs.current;
  }

  bool operator!=(tree_iterator const &rhs) const &noexcept {
    return current != rhs.current;
  }

  explicit tree_iterator(
      typename tree<T, V, TreeType, Compare>::node *cur) noexcept
      : current(cur) {}
};

template <typename T, typename V, typename TreeType, typename Compare>
struct tree : Compare {
  using base_type = Compare;

  using iterator = tree_iterator<T, V, TreeType, Compare>;

  struct node {
    node *l, *r, *parent;

    node() : l(nullptr), r(nullptr), parent(nullptr) {}

    void set_as_left(node *other) {
      if ((l = other) != nullptr) {
        l->parent = this;
      }
    }

    void set_as_right(node *other) {
      if ((r = other) != nullptr) {
        r->parent = this;
      }
    }
  };

private:
  static V &cast(node &n) { return static_cast<V &>(n); }

  static V *cast(node *n) { return static_cast<V *>(n); }

  mutable node *root;

  struct sort_x_to_left;
  struct sort_x_to_right;

  template <typename sort_type> bool compare(V *v, const T &p) const {
    return std::is_same_v<sort_type, sort_x_to_right>
               ? this->operator()(V::template projector<TreeType>::project(v),
                                  p)
               : !this->operator()(p,
                                   V::template projector<TreeType>::project(v));
  }

  template <typename sort_type>
  std::pair<node *, node *> split(node *cur, const T &pivot, V *&ret) const {
    if (!cur) {
      return {nullptr, nullptr};
    }
    if (compare<sort_type>(cast(cur), pivot)) {
      auto p = split<sort_type>(cur->r, pivot, ret);
      cur->set_as_right(p.first);
      return {cur, p.second};
    } else {
      ret = cast(cur);
      auto p = split<sort_type>(cur->l, pivot, ret);
      cur->set_as_left(p.second);
      return {p.first, cur};
    }
  }

  static node *merge(node *l, node *r) noexcept {
    if (!l) {
      return r;
    } else if (!r) {
      return l;
    }
    if (cast(l)->priority > cast(r)->priority) {
      l->set_as_right(merge(l->r, r));
      return l;
    } else {
      r->set_as_left(merge(l, r->l));
      return r;
    }
  }

  template <typename A, typename B,
            bool left_type = std::is_same_v<TreeType, left_type>>
  struct unpacker {
    static const A &unpack(const A &left, const B &right) noexcept {
      return left;
    }
  };

  template <typename A, typename B> struct unpacker<A, B, false> {
    static const B &unpack(const A &left, const B &right) noexcept {
      return right;
    }
  };

public:
  explicit tree(Compare comp = Compare()) noexcept(
      std::is_nothrow_move_constructible_v<Compare>)
      : base_type(std::move(comp)), root(nullptr) {}

  iterator begin() const noexcept {
    auto it = iterator(root);
    iterator prev;
    do {
      prev = it--;
    } while (it.current != nullptr);
    return prev;
  }

  iterator end() const noexcept { return iterator(nullptr); }

  std::pair<V *, V *> find(const T &value) const {
    V *right_closest = nullptr;
    auto [l, r_and_x] = split<sort_x_to_right>(root, value, right_closest);
    auto [x, r] = split<sort_x_to_left>(r_and_x, value, right_closest);
    if (l) {
      l->parent = nullptr;
    }
    if (r) {
      r->parent = nullptr;
    }
    if (x) {
      x->parent = nullptr;
    }
    root = merge(merge(l, x), r);
    return std::make_pair(static_cast<V *>(x), right_closest);
  }

private:
  template <typename... Args> V *first(V *v, Args &&...) {
    return v;
  }

  template <typename InsertionType, typename... Args>
  const T& get_value(Args &&...args) {
    if constexpr (std::is_same_v<in_place_t, InsertionType>) {
      return unpacker<Args...>::unpack(args...);
    } else {
      return V::template projector<TreeType>::project(
          first(std::forward<Args>(args)...));
    }
  }

public:
  template <typename InsertionType, typename... Args>
  V *insert(InsertionType, Args &&...args) {
    const T &value = get_value<InsertionType>(std::forward<Args>(args)...);
    V *right_closest = nullptr;
    auto [l, r_and_x] = split<sort_x_to_right>(root, value, right_closest);
    auto [x, r] = split<sort_x_to_left>(r_and_x, value, right_closest);
    if (l) {
      l->parent = nullptr;
    }
    if (r) {
      r->parent = nullptr;
    }
    if (x) {
      x->parent = nullptr;
      root = merge(merge(l, x), r);
      return nullptr;
    }
    try {
      if constexpr (std::is_same_v<in_place_t, InsertionType>) {
        x = new V(std::forward<Args>(args)...);
      } else {
        x = first(std::forward<Args>(args)...);
      }
    } catch (...) {
      root = merge(l, r);
      throw;
    }
    root = merge(merge(l, x), r);
    return cast(x);
  }

  template <bool do_delete> V *erase(const T &value) {
    V *right_closest = nullptr;
    auto [l, r_and_x] = split<sort_x_to_right>(root, value, right_closest);
    auto [x, r] = split<sort_x_to_left>(r_and_x, value, right_closest);
    if (l) {
      l->parent = nullptr;
    }
    if (r) {
      r->parent = nullptr;
    }
    node *ret = x;
    if (ret) {
      if constexpr (do_delete) {
        delete cast(x);
      }
    }
    root = merge(l, r);
    return cast(ret);
  }
};
