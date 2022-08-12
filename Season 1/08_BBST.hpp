#ifndef BBST_HPP
#define BBST_HPP

#include "./08_BST.hpp"

namespace app {
    /**
     * @brief 平衡二叉搜索树基类
     * @date 2022-04-12
     * @tparam T
     */
    template<typename T>
    class BBST : public BST<T> {
        using NODE = typename IBinaryTree<T>::template Node<T>;

    protected:
        virtual void rotate(NODE *r, NODE *b, NODE *c, NODE *d, NODE *e, NODE *f);

        virtual void after_rotate(NODE *grand, NODE *parent, NODE *child);

        void rotatepLeft(NODE *grand);

        void rotatepRight(NODE *grand);

    public:
        BBST(typename IBinaryTree<T>::Comparator comparator = nullptr) : BST<T>(comparator) {}

        virtual ~BBST() = default;
    };

    template<typename T>
    inline void BBST<T>::rotatepLeft(NODE *grand) {
        NODE *parent = grand->pRight;
        NODE *child = parent->pLeft;
        grand->pRight = child;
        parent->pLeft = grand;
        this->after_rotate(grand, parent, child);
    }

    template<typename T>
    inline void BBST<T>::rotatepRight(NODE *grand) {
        NODE *parent = grand->pLeft;
        NODE *child = parent->pRight;
        grand->pLeft = child;
        parent->pRight = grand;
        this->after_rotate(grand, parent, child);
    }

    template<typename T>
    inline void BBST<T>::rotate(NODE *r, NODE *b, NODE *c, NODE *d, NODE *e, NODE *f) {
        d->pParent = r->pParent;
        if (r->ispLeft())
            r->pParent->pLeft = d;
        else if (r->ispRight())
            r->pParent->pRight = d;
        else
            this->pRoot = d;
        b->pRight = c;
        if (c != nullptr)
            c->pParent = b;
        f->pLeft = e;
        if (e != nullptr)
            e->pParent = f;
        d->pLeft = b;
        d->pRight = f;
        b->pParent = d;
        f->pParent = d;
    }

    template<typename T>
    inline void BBST<T>::after_rotate(NODE *grand, NODE *parent, NODE *child) {
        parent->pParent = grand->pParent;
        if (grand->ispLeft())
            grand->pParent->pLeft = parent;
        else if (grand->ispRight())
            grand->pParent->pRight = parent;
        else
            this->pRoot = parent;
        if (child != nullptr)
            child->pParent = grand;
        grand->pParent = parent;
    }
} // namespace app

#endif /* BBST_HPP */