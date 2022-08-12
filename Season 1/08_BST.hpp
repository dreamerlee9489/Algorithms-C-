#ifndef BST_HPP
#define BST_HPP

#include "./08_IBinaryTree.hpp"

namespace app {
    /**
     * @brief 二叉搜索树基类
     * @date 2022-04-09
     * @tparam T
     */
    template<typename T>
    class BST : public IBinaryTree<T> {
        using NODE = typename IBinaryTree<T>::template Node<T>;

    protected:
        virtual void after_add(NODE *node) {}

        virtual void after_remove(NODE *node) {}

        NODE *get_node(shared_ptr<T> data) const override;

    public:
        BST<T> &operator=(const BST<T> &tree);

        BST<T> &operator=(BST<T> &&tree) noexcept;

        BST(typename IBinaryTree<T>::Comparator comparator = nullptr) : IBinaryTree<T>(comparator) {}

        BST(const BST<T> &tree) { *this = tree; }

        BST(BST<T> &&tree)
        noexcept { *this = move(tree); }

        virtual ~BST() = default;

        void add(shared_ptr<T> data) override;

        void remove(shared_ptr<T> data) override;
    };

    template<typename T>
    inline BST<T> &BST<T>::operator=(const BST<T> &tree) {
        this->clear();
        if (tree.mSize > 0) {
            this->mComparator = tree.mComparator;
            queue<NODE *> q;
            q.push(tree.pRoot);
            while (!q.empty()) {
                NODE *elem = q.front();
                add(elem->pData);
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
    inline BST<T> &BST<T>::operator=(BST<T> &&tree) noexcept {
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
    inline void BST<T>::add(shared_ptr<T> data) {
        this->not_null_check(data);
        if (this->pRoot == nullptr) {
            this->pRoot = this->create_node(data, nullptr);
            this->mSize++;
            this->after_add(this->pRoot);
            return;
        }
        NODE *node = this->pRoot, *parent = this->pRoot;
        while (node != nullptr) {
            parent = node;
            if (this->mComparator == nullptr) {
                if (*node->pData < *data)
                    node = node->pRight;
                else if (*node->pData > *data)
                    node = node->pLeft;
                else {
                    node->pData = data;
                    return;
                }
            } else {
                if (this->mComparator(node->pData, data) < 0)
                    node = node->pRight;
                else if (this->mComparator(node->pData, data) > 0)
                    node = node->pLeft;
                else {
                    node->pData = data;
                    return;
                }
            }
        }
        NODE *temp = this->create_node(data, parent);
        if (this->mComparator == nullptr) {
            if (*parent->pData < *data)
                parent->pRight = temp;
            else
                parent->pLeft = temp;
        } else {
            if (this->mComparator(parent->pData, data) < 0)
                parent->pRight = temp;
            else
                parent->pLeft = temp;
        }
        this->mSize++;
        this->after_add(temp);
    }

    template<typename T>
    inline void BST<T>::remove(shared_ptr<T> data) {
        NODE *node = get_node(data);
        if (node != nullptr) {
            this->mSize--;
            if (node->is_binary()) {
                NODE *s = this->get_successor(node);
                node->pData = s->pData;
                node = s; //删除前驱结点
            }
            NODE *replace = node->pLeft != nullptr ? node->pLeft : node->pRight;
            if (replace != nullptr) {
                replace->pParent = node->pParent;
                if (node->pParent == nullptr)
                    this->pRoot = replace;
                else if (node == node->pParent->pLeft)
                    node->pParent->pLeft = replace;
                else
                    node->pParent->pRight = replace;
                this->after_remove(replace);
            } else if (node->pParent != nullptr) {
                if (node == node->pParent->pLeft)
                    node->pParent->pLeft = nullptr;
                else
                    node->pParent->pRight = nullptr;
                this->after_remove(node);
            } else {
                this->pRoot = nullptr;
                this->after_remove(node);
            }
            delete node;
        }
    }

    template<typename T>
    inline typename BST<T>::NODE *BST<T>::get_node(shared_ptr<T> data) const {
        NODE *node = this->pRoot;
        while (node != nullptr) {
            if (this->mComparator == nullptr) {
                if (*node->pData < *data)
                    node = node->pRight;
                else if (*node->pData > *data)
                    node = node->pLeft;
                else
                    return node;
            } else {
                if (this->mComparator(node->pData, data) < 0)
                    node = node->pRight;
                else if (this->mComparator(node->pData, data) > 0)
                    node = node->pLeft;
                else
                    return node;
            }
        }
        return nullptr;
    }
} // namespace app

#endif /* BST_HPP */
