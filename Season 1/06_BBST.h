#ifndef BBST_H
#define BBST_H
#include "06_BST.h"
// 平衡二叉搜索树基类
template <typename T>
class BBST : public BST<T>
{
protected:
    void rotate_left(typename BBST::template Node<T> *grand);
    void rotate_right(typename BBST::template Node<T> *grand);
    virtual void rotate(typename BBST::template Node<T> *r, typename BBST::template Node<T> *b, typename BBST::template Node<T> *c, typename BBST::template Node<T> *d, typename BBST::template Node<T> *e, typename BBST::template Node<T> *f);
    virtual void after_rotate(typename BBST::template Node<T> *grand, typename BBST::template Node<T> *parent, typename BBST::template Node<T> *child);

public:
    BBST() = default;
    virtual ~BBST() = default;
};

template <typename T>
inline void BBST<T>::rotate_left(typename BBST::template Node<T> *grand)
{
    typename BBST::template Node<T> *parent = (typename BBST::template Node<T> *)grand->_right;
    typename BBST::template Node<T> *child = (typename BBST::template Node<T> *)parent->_left;
    grand->_right = child;
    parent->_left = grand;
    this->after_rotate(grand, parent, child);
}

template <typename T>
inline void BBST<T>::rotate_right(typename BBST::template Node<T> *grand)
{
    typename BBST::template Node<T> *parent = (typename BBST::template Node<T> *)grand->_left;
    typename BBST::template Node<T> *child = (typename BBST::template Node<T> *)parent->_right;
    grand->_left = child;
    parent->_right = grand;
    this->after_rotate(grand, parent, child);
}

template <typename T>
inline void BBST<T>::rotate(typename BBST::template Node<T> *r, typename BBST::template Node<T> *b, typename BBST::template Node<T> *c, typename BBST::template Node<T> *d, typename BBST::template Node<T> *e, typename BBST::template Node<T> *f)
{
    d->_parent = r->_parent;
    if (r->is_left())
        r->_parent->_left = d;
    else if (r->is_right())
        r->_parent->_right = d;
    else
        this->_root = d;

    b->_right = c;
    if (c != nullptr)
        c->_parent = b;

    f->_left = e;
    if (e != nullptr)
        e->_parent = f;

    d->_left = b;
    d->_right = f;
    b->_parent = d;
    f->_parent = d;
}

template <typename T>
inline void BBST<T>::after_rotate(typename BBST::template Node<T> *grand, typename BBST::template Node<T> *parent, typename BBST::template Node<T> *child)
{
    parent->_parent = grand->_parent;
    if (grand->is_left())
        grand->_parent->_left = parent;
    else if (grand->is_right())
        grand->_parent->_right = parent;
    else
        this->_root = parent;

    if (child != nullptr)
        child->_parent = grand;

    grand->_parent = parent;
}

#endif //BBST_H