#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "./08_BBST.hpp"

namespace app {
    /**
     * @brief AVL树
     * @date 2022-04-11
     * @tparam T
     */
    template<typename T>
    class AVLTree : public BBST<T> {
        using NODE = typename IBinaryTree<T>::template Node<T>;

        template<typename U>
        struct AVLNode : public NODE {
            size_t pHeight = 1;

            AVLNode<U> &operator=(const AVLNode<U> &node);

            AVLNode<U> &operator=(AVLNode<U> &&node) noexcept;

            AVLNode(shared_ptr<U> data, NODE *parent = nullptr, NODE *left = nullptr, NODE *right = nullptr)
                    : NODE(data, parent, left, right) {}

            AVLNode(const AVLNode<U> &node) { *this = node; }

            AVLNode(AVLNode<U> &&node) noexcept { *this = move(node); }

            ~AVLNode() = default;

            int balance_factor();

            void updatepHeight();

            NODE *taller_child();

            string to_string() const override {
                return ((IString &) *this->pData).to_string() + " h=" + std::to_string(pHeight);
            }
        };

        AVLNode<T> *get_node(shared_ptr<T> data) const override { return (AVLNode<T> *) BBST<T>::get_node(data); }

        NODE *create_node(shared_ptr<T> data, NODE *parent) override { return new AVLNode<T>(data, parent); }

        void rotate(NODE *r, NODE *b, NODE *c, NODE *d, NODE *e, NODE *f) override;

        void after_rotate(NODE *grand, NODE *parent, NODE *child) override;

        void after_add(NODE *node) override;

        void after_remove(NODE *node) override;

        bool is_balanced(NODE *node) { return abs(((AVLNode<T> *) node)->balance_factor()) <= 1; }

        void updatepHeight(NODE *node) { ((AVLNode<T> *) node)->updatepHeight(); }

        void rebalance(NODE *grand);

    public:
        AVLTree<T> &operator=(const AVLTree<T> &tree);

        AVLTree<T> &operator=(AVLTree<T> &&tree) noexcept;

        AVLTree(typename IBinaryTree<T>::Comparator comparator = nullptr) : BBST<T>(comparator) {}

        AVLTree(const AVLTree<T> &tree) { *this = tree; }

        AVLTree(AVLTree &&tree) noexcept { *this = move(tree); }

        ~AVLTree() = default;
    };

    template<typename T>
    template<typename U>
    inline typename AVLTree<T>::template AVLNode<U> &AVLTree<T>::AVLNode<U>::operator=(const AVLNode<U> &node) {
        this->pData = node.pData;
        this->pParent = node.pParent;
        this->pLeft = node.pLeft;
        this->pRight = node.pRight;
        this->pHeight = node.pHeight;
        return *this;
    }

    template<typename T>
    template<typename U>
    inline typename AVLTree<T>::template AVLNode<U> &AVLTree<T>::AVLNode<U>::operator=(AVLNode<U> &&node) noexcept {
        this->pData = nullptr;
        this = &node;
        return *this;
    }

    template<typename T>
    template<typename U>
    inline int AVLTree<T>::AVLNode<U>::balance_factor() {
        size_t leftH = (this->pLeft == nullptr) ? 0 : ((AVLNode<U> *) this->pLeft)->pHeight;
        size_t rightH = (this->pRight == nullptr) ? 0 : ((AVLNode<U> *) this->pRight)->pHeight;
        return (int) (leftH - rightH);
    }

    template<typename T>
    template<typename U>
    inline void AVLTree<T>::AVLNode<U>::updatepHeight() {
        size_t leftH = (this->pLeft == nullptr) ? 0 : ((AVLNode<U> *) this->pLeft)->pHeight;
        size_t rightH = (this->pRight == nullptr) ? 0 : ((AVLNode<U> *) this->pRight)->pHeight;
        pHeight = 1 + max(leftH, rightH);
    }

    template<typename T>
    template<typename U>
    inline typename AVLTree<T>::NODE *AVLTree<T>::AVLNode<U>::taller_child() {
        size_t leftH = (this->pLeft == nullptr) ? 0 : ((AVLNode<U> *) this->pLeft)->pHeight;
        size_t rightH = (this->pRight == nullptr) ? 0 : ((AVLNode<U> *) this->pRight)->pHeight;
        if (leftH > rightH)
            return this->pLeft;
        if (leftH < rightH)
            return this->pRight;
        return this->ispLeft() ? this->pLeft : this->pRight;
    }

    template<typename T>
    inline AVLTree<T> &AVLTree<T>::operator=(const AVLTree<T> &tree) {
        this->clear();
        if (tree.mSize > 0) {
            this->mComparator = tree.mComparator;
            queue<NODE *> q;
            q.push(tree.pRoot);
            while (!q.empty()) {
                NODE *elem = q.front();
                this->add(elem->pData);
                q.pop();
                if (elem->pLeft != nullptr)
                    q.push(elem->pLeft);
                if (elem->pRight != nullptr)
                    q.push(elem->pRight);
            }
        }
        return *this;
    }

    template<typename T>
    inline AVLTree<T> &AVLTree<T>::operator=(AVLTree<T> &&tree) noexcept {
        this->clear();
        this->mSize = tree.mSize;
        this->pRoot = tree.pRoot;
        this->mComparator = tree.mComparator;
        tree.mSize = 0;
        tree.pRoot = nullptr;
        tree.mComparator = nullptr;
        return *this;
    }

    template<typename T>
    inline void AVLTree<T>::after_add(NODE *node) {
        while ((node = node->pParent) != nullptr) {
            if (is_balanced(node))
                updatepHeight(node);
            else {
                rebalance(node);
                break;
            }
        }
    }

    template<typename T>
    inline void AVLTree<T>::after_remove(NODE *node) {
        while ((node = node->pParent) != nullptr) {
            if (is_balanced(node))
                updatepHeight(node);
            else
                rebalance(node);
        }
    }

    template<typename T>
    inline void AVLTree<T>::rebalance(NODE *grand) {
        NODE *parent = ((AVLNode<T> *) grand)->taller_child();
        NODE *node = ((AVLNode<T> *) parent)->taller_child();
        if (parent->ispLeft()) {
            if (node->ispLeft()) {
                this->rotatepRight(grand);
                // rotate(grand, node, (AVLNode<T> *)node->pRight, parent, (AVLNode<T> *)parent->pRight, grand);
            } else {
                this->rotatepLeft(parent);
                this->rotatepRight(grand);
                // rotate(grand, parent, (AVLNode<T> *)node->pLeft, node, (AVLNode<T> *)node->pRight, grand);
            }
        } else {
            if (node->ispLeft()) {
                this->rotatepRight(parent);
                this->rotatepLeft(grand);
                // rotate(grand, parent, (AVLNode<T> *)node->pLeft, node, (AVLNode<T> *)node->pRight, parent);
            } else {
                this->rotatepLeft(grand);
                // rotate(grand, grand, (AVLNode<T> *)parent->pLeft, parent, (AVLNode<T> *)node->pLeft, node);
            }
        }
    }

    template<typename T>
    inline void AVLTree<T>::rotate(NODE *r, NODE *b, NODE *c, NODE *d, NODE *e, NODE *f) {
        BBST<T>::rotate(r, b, c, d, e, f);
        updatepHeight(b);
        updatepHeight(f);
        updatepHeight(d);
    }

    template<typename T>
    inline void AVLTree<T>::after_rotate(NODE *grand, NODE *parent, NODE *child) {
        BBST<T>::after_rotate(grand, parent, child);
        updatepHeight(grand);
        updatepHeight(parent);
    }
} // namespace app

#endif /* AVL_TREE_HPP */