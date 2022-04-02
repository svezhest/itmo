#pragma once

#include "tree.h"
#include <stdexcept>

template <typename Left, typename Right, typename CompareLeft = std::less<Left>,
          typename CompareRight = std::less<Right>>
struct bimap {
  using left_t = Left;
  using right_t = Right;

private:
  struct left_tag;
  struct right_tag;

  struct node_t : tree<right_t, node_t, right_type, CompareRight>::node,
                  tree<left_t, node_t, left_type, CompareLeft>::node {
    template <class... Args>
    explicit node_t(Args &&...args) noexcept(
        std::is_nothrow_constructible_v<std::pair<left_t, right_t>, Args...>)
        : priority(get_rand()), value(std::forward<Args>(args)...) {}

    size_t priority;
    std::pair<left_t, right_t> value;

    template <typename X, bool left_type = std::is_same_v<X, left_type>>
    struct projector {
      static const left_t &project(const node_t *v) noexcept {
        return v->value.first;
      }
    };

    template <typename X> struct projector<X, false> {
      static const right_t &project(const node_t *v) noexcept {
        return v->value.second;
      }
    };
  };

  tree<right_t, node_t, right_type, CompareRight> right_tree;
  tree<left_t, node_t, left_type, CompareLeft> left_tree;

  size_t sz;

public:
  template <typename RetType, typename TreeType, typename CompType>
  struct iterator_template;

  using right_iterator = iterator_template<right_t, right_type, CompareRight>;
  using left_iterator = iterator_template<left_t, left_type, CompareLeft>;

  template <bool then_left, class T = void> struct other_iterator {
    using type = left_iterator;
  };

  template <class T> struct other_iterator<true, T> {
    using type = right_iterator;
  };

  template <bool then_left, class T = void> struct other_tree {
    using type = tree<left_t, node_t, left_type, CompareLeft>;
  };

  template <class T> struct other_tree<true, T> {
    using type = tree<right_t, node_t, right_type, CompareRight>;
  };

  template <typename RetType, typename TreeType, typename CompType>
  struct iterator_template {
    friend class bimap;

    RetType const &operator*() const noexcept {
      return node_t::template projector<TreeType>::project(&(*cur));
    }

    iterator_template &operator++() noexcept {
      ++cur;
      return *this;
    }

    iterator_template operator++(int) noexcept {
      auto tmp = *this;
      ++*this;
      return tmp;
    }

    iterator_template &operator--() noexcept {
      --cur;
      return *this;
    }

    iterator_template operator--(int) noexcept {
      auto tmp = *this;
      --*this;
      return tmp;
    }

    typename other_iterator<std::is_same_v<TreeType, left_type>>::type
    flip() const noexcept {
      return typename other_iterator<std::is_same_v<TreeType, left_type>>::type(
          cur.is_valid()
              ? static_cast<typename other_tree<
                    std::is_same_v<TreeType, left_type>>::type::node *>(
                    const_cast<node_t *>(&(*cur)))
              : nullptr);
    }

    bool operator==(iterator_template const &rhs) const &noexcept {
      return cur == rhs.cur;
    }

    bool operator!=(iterator_template const &rhs) const &noexcept {
      return cur != rhs.cur;
    }

  private:
    tree_iterator<RetType, node_t, TreeType, CompType> cur;

    explicit iterator_template(
        tree_iterator<RetType, node_t, TreeType, CompType> it)
        : cur(it) {}

    explicit iterator_template(
        typename tree<RetType, node_t, TreeType, CompType>::node *p)
        : cur(tree_iterator<RetType, node_t, TreeType, CompType>(p)) {}
  };

  // Создает bimap не содержащий ни одной пары.
  explicit bimap(CompareLeft compare_left = CompareLeft(),
                 CompareRight compare_right = CompareRight()) noexcept
      : right_tree(compare_right), left_tree(compare_left), sz(0) {}

  // Конструкторы от других и присваивания
  bimap(bimap const &other)
      : bimap(
            static_cast<typename tree<left_t, node_t, left_type,
                                      CompareLeft>::base_type>(other.left_tree),
            static_cast<typename tree<right_t, node_t, right_type,
                                      CompareRight>::base_type>(
                other.right_tree)) {
    for (auto it = other.begin_left(); it != other.end_left(); ++it) {
      insert(*it, *it.flip());
    }
  }

  bimap(bimap &&other) noexcept = default;

  bimap &operator=(bimap const &other) {
    if (this != &other) {
      bimap(other).swap(*this);
    }
    return *this;
  }

private:
  void swap(bimap &other) noexcept {
    std::swap(left_tree, other.left_tree);
    std::swap(right_tree, other.right_tree);
    std::swap(sz, other.sz);
  }

public:
  bimap &operator=(bimap &&other) noexcept = default;

  // Деструктор. Вызывается при удалении объектов bimap.
  // Инвалидирует все итераторы ссылающиеся на элементы этого bimap
  // (включая итераторы ссылающиеся на элементы следующие за последними).
  ~bimap() { erase_left(begin_left(), end_left()); }

  // Вставка пары (left, right), возвращает итератор на left.
  // Если такой left или такой right уже присутствуют в bimap, вставка не
  // производится и возвращается end_left()

  template <typename A, typename B>
  left_iterator insert_template(A &&left, B &&right) {
    if (right_tree.find(right).first) {
      return end_left();
    }
    auto *v = left_tree.insert(in_place_tag, std::forward<A>(left), std::forward<B>(right));
    if (v == nullptr) {
      return end_left();
    }
    ++sz;
    right_tree.insert(not_in_place_tag, v);
    return left_iterator(v);
  }

  left_iterator insert(left_t const &left, right_t const &right) {
    return insert_template(left, right);
  }

  left_iterator insert(left_t &&left, right_t const &right) {
    return insert_template(std::move(left), right);
  }

  left_iterator insert(left_t const &left, right_t &&right) {
    return insert_template(left, std::move(right));
  }

  left_iterator insert(left_t &&left, right_t &&right) {
    return insert_template(std::move(left), std::move(right));
  }

  // Удаляет элемент и соответствующий ему парный.
  // erase невалидного итератора неопределен.
  // erase(end_left()) и erase(end_right()) неопределены.
  // Пусть it ссылается на некоторый элемент e.
  // erase инвалидирует все итераторы ссылающиеся на e и на элемент парный к e.
  left_iterator erase_left(left_iterator it) {
    left_iterator ret = it;
    ++ret;
    if (erase_left(*it)) {
      return ret;
    }
    return end_left();
  }

  // Аналогично erase, но по ключу, удаляет элемент если он присутствует, иначе
  // не делает ничего Возвращает была ли пара удалена
  bool erase_left(left_t const &left) {
    node_t *v = left_tree.template erase<false>(left);
    if (v) {
      --sz;
      right_tree.template erase<true>(v->value.second);
      return true;
    }
    return false;
  }

  right_iterator erase_right(right_iterator it) {
    auto ret = it;
    ++ret;
    if (erase_right(*it)) {
      return ret;
    }
    return end_right();
  }

  bool erase_right(right_t const &right) {
    node_t *v = right_tree.template erase<false>(right);
    if (v) {
      --sz;
      left_tree.template erase<true>(v->value.first);
      return true;
    }
    return false;
  }

  // erase от ренжа, удаляет [first, last), возвращает итератор на последний
  // элемент за удаленной последовательностью

  left_iterator erase_left(left_iterator first, left_iterator last) {
    auto it = first;
    while (it != last) {
      erase_left(it++);
    }
    return it;
  }

  right_iterator erase_right(right_iterator first, right_iterator last) {
    auto it = first;
    while (it != last) {
      erase_right(it++);
    }
    return it;
  }

  // Возвращает итератор по элементу. Если не найден - соответствующий end()
  left_iterator find_left(left_t const &left) const {
    return left_iterator(left_tree.find(left).first);
  }

  right_iterator find_right(right_t const &right) const {
    return right_iterator(right_tree.find(right).first);
  }

  // Возвращает противоположный элемент по элементу
  // Если элемента не существует -- бросает std::out_of_range
  right_t const &at_left(left_t const &key) const {
    auto *v = left_tree.find(key).first;
    if (v) {
      const right_t &at = v->value.second;
      return at;
    } else {
      throw std::out_of_range("at_left: no such element\n");
    }
  }

  left_t const &at_right(right_t const &key) const {
    auto *v = right_tree.find(key).first;
    if (v) {
      const left_t &at = v->value.first;
      return at;
    } else {
      throw std::out_of_range("at_left: no such element\n");
    }
  }

  // Возвращает противоположный элемент по элементу
  // Если элемента не существует, добавляет его в bimap и на противоположную
  // сторону кладет дефолтный элемент, ссылку на который и возвращает
  // Если дефолтный элемент уже лежит в противоположной паре - должен поменять
  // соответствующий ему элемент на запрашиваемый (смотри тесты)
  template <typename T = right_t,
            typename = std::enable_if_t<std::is_default_constructible_v<T>>>
  T const &at_left_or_default(left_t const &key) {
    auto *v = left_tree.find(key).first;
    if (v) {
      const right_t &at = v->value.second;
      return at;
    } else {
      right_t def = Right();
      erase_right(def);
      return *insert(key, std::move(def)).flip();
    }
  }

  template <typename T = left_t,
            typename = std::enable_if_t<std::is_default_constructible_v<T>>>
  T const &at_right_or_default(right_t const &key) {
    auto *v = right_tree.find(key).first;
    if (v) {
      const left_t &at = v->value.first;
      return at;
    } else {
      right_t def = Left();
      erase_left(def);
      return *insert(std::move(def), key);
    }
  }

  // lower и upper bound'ы по каждой стороне
  // Возвращают итераторы на соответствующие элементы
  // Смотри std::lower_bound, std::upper_bound.
  left_iterator lower_bound_left(const left_t &left) const {
    auto p = left_tree.find(left);
    if (p.first) {
      return left_iterator(p.first);
    }
    return left_iterator(p.second);
  }

  left_iterator upper_bound_left(const left_t &left) const {
    auto *v = left_tree.find(left).second;
    return left_iterator(v);
  }

  right_iterator lower_bound_right(const right_t &right) const {
    auto p = right_tree.find(right);
    if (p.first) {
      return right_iterator(p.first);
    }
    return right_iterator(p.second);
  }

  right_iterator upper_bound_right(const right_t &right) const {
    auto *v = right_tree.find(right).second;
    return right_iterator(v);
  }

  // Возващает итератор на минимальный по порядку left.
  left_iterator begin_left() const noexcept {
    return left_iterator(left_tree.begin());
  }
  // Возващает итератор на следующий за последним по порядку left.
  left_iterator end_left() const noexcept {
    return left_iterator(left_tree.end());
  }

  // Возващает итератор на минимальный по порядку right.
  right_iterator begin_right() const noexcept {
    return right_iterator(right_tree.begin());
  }
  // Возващает итератор на следующий за последним по порядку right.
  right_iterator end_right() const noexcept {
    return right_iterator(right_tree.end());
  }

  // Проверка на пустоту
  bool empty() const noexcept { return sz == 0; }

  // Возвращает размер бимапы (кол-во пар)
  std::size_t size() const noexcept { return sz; }

  // операторы сравнения
  friend bool operator==(bimap const &a, bimap const &b) noexcept {
    for (auto it1 = a.begin_left(), it2 = b.begin_left();; ++it1, ++it2) {
      if (it1 == a.end_left()) {
        return it2 == b.end_left();
      } else if (it2 == b.end_left()) {
        return false;
      }
      if (*it1 != *it2 || *it1.flip() != *it2.flip()) {
        return false;
      }
    }
  }

  friend bool operator!=(bimap const &a, bimap const &b) noexcept {
    return !(a == b);
  }
};
