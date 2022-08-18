#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "./03_IList.hpp"

namespace app {
/**
 * @brief 双向循环链表
 * @date 2022-03-30
 * @tparam T
 */
    template<typename T>
    class LinkedList : public IList<T> {
        template<typename U>
        struct Node {
            shared_ptr<T> _data = nullptr;
            Node<U> *_prev = nullptr, *_next = nullptr;

            Node<U> &operator=(const Node<U> &node);

            Node<U> &operator=(Node<U> &&node) noexcept;

            Node(shared_ptr<T> data, Node<U> *prev = nullptr, Node<U> *next = nullptr);

            Node(const Node<U> &node) { *this = node; }

            Node(Node<U> &&node) noexcept { *this = move(node); }

            ~Node() { _data = nullptr; }

            shared_ptr<T> disconnect();
        };

        template<typename U>
        friend ostream &operator<<(ostream &os, const LinkedList<U> &list);

        Node<T> *get_node(int index) const;

    public:
        Node<T> *_head = nullptr;

        LinkedList<T> &operator=(const LinkedList<T> &list);

        LinkedList<T> &operator=(LinkedList<T> &&list) noexcept;

        LinkedList() {
            _head = new Node<T>(nullptr);
            _head->_prev = _head->_next = _head;
        }

        LinkedList(const LinkedList<T> &list) { *this = list; }

        LinkedList(LinkedList<T> &&list) noexcept { *this = move(list); }

        ~LinkedList() {
            clear();
            delete _head;
        }

        int index_of(shared_ptr<T> data) const override;

        void insert(int index, shared_ptr<T> data) override;

        shared_ptr<T> remove(int index) override;

        shared_ptr<T> get(int index) const override;

        void set(int index, shared_ptr<T> data) override;

        void clear() override;
    };

    template<typename T>
    template<typename U>
    inline LinkedList<T>::Node<U>::Node(shared_ptr<T> data, Node<U> *prev,
                                        Node<U> *next) {
        _data = data;
        _prev = prev;
        _next = next;
    }

    template<typename T>
    template<typename U>
    inline typename LinkedList<T>::template Node<U> &
    LinkedList<T>::Node<U>::operator=(const Node<U> &node) {
        _data = node._data;
        _prev = node._prev;
        _next = node._next;
        return *this;
    }

    template<typename T>
    template<typename U>
    inline typename LinkedList<T>::template Node<U> &
    LinkedList<T>::Node<U>::operator=(Node<U> &&node) noexcept {
        _data = nullptr;
        this = &node;
        return *this;
    }

    template<typename T>
    template<typename U>
    inline shared_ptr<T> LinkedList<T>::Node<U>::disconnect() {
        auto old = _data;
        _data = nullptr;
        _prev = _next = nullptr;
        return old;
    }

    template<typename U>
    inline ostream &operator<<(ostream &os, const LinkedList<U> &list) {
        for (size_t i = 0; i < list._size; ++i)
            if (list.get(i) != nullptr)
                os << *list.get(i) << "\n";
        return os;
    }

    template<typename T>
    inline LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &list) {
        clear();
        if (_head == nullptr) {
            _head = new Node<T>(nullptr);
            _head->_prev = _head->_next = _head;
        }
        for (size_t i = 0; i < list._size; ++i)
            insert(i, list.get(i));
        return *this;
    }

    template<typename T>
    inline LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> &&list) noexcept {
        clear();
        if (_head == nullptr) {
            _head = new Node<T>(nullptr);
            _head->_prev = _head->_next = _head;
        }
        if (list._size > 0) {
            this->_size = list._size;
            _head->_next = list._head->_next;
            _head->_prev = list._head->_prev;
            list._head->_next->_prev = _head;
            list._size = 0;
            list._head = nullptr;
        }
        return *this;
    }

    template<typename T>
    inline int LinkedList<T>::index_of(shared_ptr<T> data) const {
        Node<T> *p = _head;
        for (size_t i = 0; i < this->_size; ++i) {
            p = p->_next;
            if (*p->_data == *data)
                return i;
        }
        return -1;
    }

    template<typename T>
    inline void LinkedList<T>::insert(int index, shared_ptr<T> data) {
        this->check_range(index, true);
        Node<T> *prev = get_node(index - 1);
        Node<T> *next = prev->_next;
        Node<T> *temp = new Node<T>(data, prev, next);
        if (next != _head) {
            prev->_next = temp;
            next->_prev = temp;
        } else {
            prev->_next = temp;
            temp->_next = _head;
            _head->_prev = temp;
        }
        this->_size++;
    }

    template<typename T>
    inline shared_ptr<T> LinkedList<T>::remove(int index) {
        this->check_range(index);
        Node<T> *old = _head->_next;
        for (size_t i = 0; i < index; ++i)
            old = old->_next;
        if (index == 0) {
            _head->_next = _head->_next->_next;
            _head->_next->_prev = _head;
        } else if (index == this->_size - 1) {
            _head->_prev = _head->_prev->_prev;
            _head->_prev->_next = _head;
        } else {
            old->_prev->_next = old->_next;
            old->_next->_prev = old->_prev;
        }
        this->_size--;
        return old->disconnect();
    }

    template<typename T>
    inline shared_ptr<T> LinkedList<T>::get(int index) const {
        this->check_range(index);
        Node<T> *p = _head->_next;
        for (size_t i = 0; i < index; ++i)
            p = p->_next;
        return p->_data;
    }

    template<typename T>
    inline void LinkedList<T>::set(int index, shared_ptr<T> data) {
        this->check_range(index);
        Node<T> *p = _head->_next;
        for (size_t i = 0; i < index; ++i)
            p = p->_next;
        p->_data = data;
    }

    template<typename T>
    inline void LinkedList<T>::clear() {
        if (this->_size > 0) {
            Node<T> *p = _head->_prev;
            while (p != _head) {
                p = p->_prev;
                delete p->_next;
            }
            _head->_next = _head;
            _head->_prev = _head;
            this->_size = 0;
        }
    }

    template<typename T>
    inline typename LinkedList<T>::template Node<T> *
    LinkedList<T>::get_node(int index) const {
        if (index == -1)
            return _head;
        if (index == this->_size - 1)
            return _head->_prev;
        Node<T> *p = _head;
        for (size_t i = 0; i < index; ++i)
            p = p->_next;
        return p->_next;
    }
} // namespace app

#endif /* LINKEDLIST_HPP */