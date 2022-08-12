#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "./08_BBST.hpp"

namespace app {
    /**
     * @brief 红黑树
     * @date 2022-04-13
     * @tparam T
     */
    template<typename T>
    class RBTree : public BBST<T> {
        using NODE = typename IBinaryTree<T>::template Node<T>;
        static const bool BLACK = false, RED = true;

        template<typename U>
        struct RBNode : public NODE {
            bool mColor = RED;

            RBNode<U> &operator=(const RBNode<U> &node);

            RBNode<U> &operator=(RBNode<U> &&node) noexcept;

            RBNode(shared_ptr<U> data, NODE *parent = nullptr, NODE *left = nullptr, NODE *right = nullptr)
                    : NODE(data, parent, left, right) {}

            RBNode(const RBNode<U> &node) { *this = node; }

            RBNode(RBNode<U> &&node) noexcept { *this = move(node); }

            ~RBNode() = default;

            string to_string() const override {
                string str = ((IString &) *this->pData).to_string();
                return str += mColor == RED ? " R E D" : " BLACK";
            }
        };

        RBNode<T> *get_node(shared_ptr<T> data) const override { return (RBNode<T> *) BBST<T>::get_node(data); }

        NODE *create_node(shared_ptr<T> data, NODE *parent) override { return new RBNode<T>(data, parent); }

        void after_add(NODE *node) override;

        void after_remove(NODE *node) override;

        NODE *setmColor(NODE *node, bool color);

        bool color_of(NODE *node) { return node == nullptr ? BLACK : ((RBNode<T> *) node)->mColor; }

        bool is_black(NODE *node) { return color_of(node) == BLACK; }

        bool is_red(NODE *node) { return color_of(node) == RED; }

    public:
        RBTree<T> &operator=(const RBTree<T> &tree);

        RBTree<T> &operator=(RBTree<T> &&tree) noexcept;

        RBTree(typename IBinaryTree<T>::Comparator comparator = nullptr) : BBST<T>(comparator) {}

        RBTree(const RBTree<T> &tree) { *this = tree; }

        RBTree(RBTree<T> &&tree) noexcept { *this = move(tree); }

        ~RBTree() = default;
    };

    template<typename T>
    template<typename U>
    inline RBTree<T>::RBNode<U> &RBTree<T>::RBNode<U>::operator=(const RBNode<U> &node) {
        this->pData = node.pData;
        this->pParent = node.pParent;
        this->pLeft = node.pLeft;
        this->pRight = node.pRight;
        mColor = node.mColor;
        return *this;
    }

    template<typename T>
    template<typename U>
    inline RBTree<T>::RBNode<U> &RBTree<T>::RBNode<U>::operator=(RBNode<U> &&node) noexcept {
        this->pData = nullptr;
        this = &node;
        return *this;
    }

    template<typename T>
    inline RBTree<T> &RBTree<T>::operator=(const RBTree<T> &tree) {
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
    inline RBTree<T> &RBTree<T>::operator=(RBTree<T> &&tree) noexcept {
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
    inline typename RBTree<T>::NODE *RBTree<T>::setmColor(NODE *node, bool color) {
        if (node != nullptr)
            ((RBNode<T> *) node)->mColor = color;
        return node;
    }

    template<typename T>
    inline void RBTree<T>::after_add(NODE *node) {
        NODE *parent = node->pParent;
        if (parent == nullptr) {
            setmColor(node, BLACK);
            return;
        }
        if (is_red(parent)) {
            NODE *uncle = parent->get_sibling();
            NODE *grand = setmColor(parent->pParent, RED);
            if (is_red(uncle)) {
                setmColor(parent, BLACK);
                setmColor(uncle, BLACK);
                after_add(grand);
                return;
            }
            if (parent->ispLeft()) {
                if (node->ispLeft())
                    setmColor(parent, BLACK);
                else {
                    setmColor(node, BLACK);
                    this->rotatepLeft(parent);
                }
                this->rotatepRight(grand);
            } else {
                if (node->ispLeft()) {
                    setmColor(node, BLACK);
                    this->rotatepRight(parent);
                } else
                    setmColor(parent, BLACK);
                this->rotatepLeft(grand);
            }
        }
    }

    template<typename T>
    inline void RBTree<T>::after_remove(NODE *node) {
        if (is_red(node)) {
            setmColor(node, BLACK);
            return;
        }
        NODE *parent = node->pParent;
        if (parent != nullptr) {
            bool ispLeft = parent->pLeft == nullptr || node->ispLeft();
            NODE *sibling = ispLeft ? parent->pRight : parent->pLeft;
            if (ispLeft) {
                if (is_red(sibling)) {
                    setmColor(sibling, BLACK);
                    setmColor(parent, RED);
                    this->rotatepLeft(parent);
                    sibling = parent->pRight;
                }
                if (is_black(sibling->pLeft) && is_black(sibling->pRight)) {
                    bool parent_black = is_black(parent);
                    setmColor(parent, BLACK);
                    setmColor(sibling, RED);
                    if (parent_black)
                        after_remove(parent);
                } else {
                    if (is_black(sibling->pRight)) {
                        this->rotatepRight(sibling);
                        sibling = parent->pRight;
                    }
                    setmColor(sibling, color_of(parent));
                    setmColor(sibling->pRight, BLACK);
                    setmColor(parent, BLACK);
                    this->rotatepLeft(parent);
                }
            } else {
                if (is_red(sibling)) {
                    setmColor(sibling, BLACK);
                    setmColor(parent, RED);
                    this->rotatepRight(parent);
                    sibling = parent->pLeft;
                }
                if (is_black(sibling->pLeft) && is_black(sibling->pRight)) {
                    bool parent_black = is_black(parent);
                    setmColor(parent, BLACK);
                    setmColor(sibling, RED);
                    if (parent_black)
                        after_remove(parent);
                } else {
                    if (is_black(sibling->pLeft)) {
                        this->rotatepLeft(sibling);
                        sibling = parent->pLeft;
                    }
                    setmColor(sibling, color_of(parent));
                    setmColor(sibling->pLeft, BLACK);
                    setmColor(parent, BLACK);
                    this->rotatepRight(parent);
                }
            }
        }
    }
} // namespace app

#endif /* RB_TREE_HPP */
