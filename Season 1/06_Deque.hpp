#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "./03_LinkedList.hpp"

namespace app {
    /**
     * @brief 双端队列
     * @date 2022-04-08
     * @tparam T
     */
    template<typename T>
    class Deque {
        friend ostream &operator<<(ostream &os, const Deque<T> &deque) { return os << *deque.pList; }

        LinkedList<T> *pList = nullptr;

    public:
        Deque<T> &operator=(const Deque<T> &deque);

        Deque<T> &operator=(Deque<T> &&deque) noexcept;

        Deque() { pList = new LinkedList<T>(); }

        Deque(const Deque<T> &deque) { *this = deque; }

        Deque(Deque<T> &&deque) noexcept { *this = move(deque); }

        ~Deque() { delete pList; }

        size_t size() const { return pList->size(); }

        bool is_empty() const { return pList->size() == 0; }

        void push(shared_ptr<T> data) { pList->add(data); }

        shared_ptr<T> pop() { return pList->remove(0); }

        void push_front(shared_ptr<T> data) { pList->insert(0, data); }

        shared_ptr<T> pop_rear() { return pList->remove(pList->size() - 1); }

        shared_ptr<T> front() const { return pList->get(0); }

        shared_ptr<T> rear() const { return pList->get(pList->size() - 1); }

        void clear() { pList->clear(); }
    };

    template<typename T>
    inline Deque<T> &Deque<T>::operator=(const Deque<T> &deque) {
        clear();
        delete pList;
        pList = new LinkedList<T>();
        *pList = *deque.pList;
        return *this;
    }

    template<typename T>
    inline Deque<T> &Deque<T>::operator=(Deque<T> &&deque) noexcept {
        clear();
        delete pList;
        pList = new LinkedList<T>();
        *pList = move(*deque.pList);
        return *this;
    }
} // namespace app

#endif /* DEQUE_HPP */
