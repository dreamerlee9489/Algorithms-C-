#ifndef BBST_H
#define BBST_H
#include "./08_BST.h"
// 平衡二叉搜索树基类
template <typename T>
class BBST : public BST<T>
{
    using NODE = typename BST<T>::template Node<T>;

protected:
    void rotate_left(NODE *grand);
    void rotate_right(NODE *grand);
    virtual void rotate(NODE *r, NODE *b, NODE *c, NODE *d, NODE *e, NODE *f);
    virtual void after_rotate(NODE *grand, NODE *parent, NODE *child);

public:
    BBST() = default;
    virtual ~BBST() = default;
};

template <typename T>
inline void BBST<T>::rotate_left(NODE *grand)
{
    NODE *parent = grand->_right;
    NODE *child = parent->_left;
    grand->_right = child;
    parent->_left = grand;
    this->after_rotate(grand, parent, child);
}

template <typename T>
inline void BBST<T>::rotate_right(NODE *grand)
{
    NODE *parent = grand->_left;
    NODE *child = parent->_right;
    grand->_left = child;
    parent->_right = grand;
    this->after_rotate(grand, parent, child);
}

template <typename T>
inline void BBST<T>::rotate(NODE *r, NODE *b, NODE *c, NODE *d, NODE *e, NODE *f)
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
inline void BBST<T>::after_rotate(NODE *grand, NODE *parent, NODE *child)
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

#endif /* BBST_H */