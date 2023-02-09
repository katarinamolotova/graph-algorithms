#ifndef SRC_HELPERS_S21_STACK_H
#define SRC_HELPERS_S21_STACK_H

#include <initializer_list>
#include <stdexcept>

namespace s21 {
template <class T>
class Stack {
 private:
  class Node {
   public:
    Node *back;
    T data;

    Node(T data = T(), Node *back = nullptr) {
      this->data = data;
      this->back = back;
    }
  };

  Node *top_;
  size_t size_;

  void clear();
  void copy(const Stack &other);
  void half_copy(const Stack &other);

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack();
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s);
  ~Stack();
  Stack<value_type> &operator=(Stack &s);

  const_reference top();
  bool empty();
  size_type size();

  void push(const_reference value);
  void swap(Stack &other);

  value_type pop();
  value_type peek();

  template <class... Args>
  void emplace_front(Args &&...args);
};
}  // namespace s21

#endif  //  SRC_HELPERS_S21_STACK_H
