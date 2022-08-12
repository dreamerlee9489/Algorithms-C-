#ifndef STACK_HPP
#define STACK_HPP

#include "./02_ArrayList.hpp"

namespace app {
    /**
     * @brief 栈
     * @date 2022-04-05
     * @tparam T
     */
    template<typename T>
    class Stack {
        friend ostream &operator<<(ostream &os, const Stack<T> &stack) { return os << *stack.pList; }

        ArrayList<T> *pList = nullptr;

    public:
        Stack<T> &operator=(const Stack<T> &stack);

        Stack<T> &operator=(Stack<T> &&stack) noexcept;

        Stack() { pList = new ArrayList<T>(); }

        Stack(const Stack<T> &stack) { *this = stack; }

        Stack(Stack<T> &&stack) noexcept { *this = move(stack); }

        ~Stack() { delete pList; }

        size_t size() const { return pList->size(); }

        bool is_empty() const { return pList->is_empty(); }

        void push(shared_ptr<T> data) { pList->add(data); }

        shared_ptr<T> pop() { return pList->remove(pList->size() - 1); }

        shared_ptr<T> top() const { return pList->get(pList->size() - 1); }

        void clear() { pList->clear(); }
    };

    template<typename T>
    inline Stack<T> &Stack<T>::operator=(const Stack<T> &stack) {
        clear();
        delete pList;
        pList = new ArrayList<T>();
        *pList = *stack.pList;
        return *this;
    }

    template<typename T>
    inline Stack<T> &Stack<T>::operator=(Stack<T> &&stack) noexcept {
        clear();
        delete pList;
        pList = new ArrayList<T>();
        *pList = move(*stack.pList);
        return *this;
    }
} // namespace app

#endif /* STACK_HPP */
