#include "array_list.h"


namespace structures {

template<typename T>
class AVLTree {
public:
    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        Node(const T& data_);

        T data;
        int height_;
        Node* left;
        Node* right;
        Node* parent;

        void insert(const T& data_);

        bool remove(const T& data_);

        bool contains(const T& data_) const;

        void updateHeight() ;

        Node* simpleLeft() ;

        Node* simpleRight() ;

        Node* doubleLeft() ;

        Node* doubleRight() ;

        void pre_order(ArrayList<T>& v) const;

        void in_order(ArrayList<T>& v) const;

        void post_order(ArrayList<T>& v) const;

        int height() {
            return height_;
        }
    };

    Node* root;
    std::size_t size_;
};

}

template<typename T>
using AVLTree = structures::AVLTree<T>;

template<typename T>
using ArrayList = structures::ArrayList<T>;

// -----

template<typename T>
int structures::AVLTree<T>::height() const {
    return root->height();
}

template<typename T>
structures::AVLTree<T>::~AVLTree() {
    root = nullptr;
    size_ = 0u;
}

template<typename T>
void structures::AVLTree<T>::insert(const T& data) {
    if (root == nullptr) {
        root = new Node(data);
    } else {
        root->insert(data);
    }
    size_++;
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data) {}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    if (empty())
        return false;
    else
        return root->contains(data);
}

template<typename T>
bool structures::AVLTree<T>::empty() const {
    if (size_ == 0u)
        return true;
    else
        return false;
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    ArrayList<T> v{};
    if (!empty()) {
        root->pre_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    ArrayList<T> v{};
    if (!empty()) {
        root->in_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    ArrayList<T> v{};
    if (!empty()) {
        root->post_order(v);
    }
    return v;
}

// -----

template<typename T>
structures::AVLTree<T>::Node::Node(const T& data_) {
    data = data_;
    height_ = 0u;
    left = nullptr;
    right = nullptr;
}

template<typename T>
void structures::AVLTree<T>::Node::insert(const T& data_) {
    if (data_ < data) {
        if (left == nullptr) {
            left = new Node(data_);
            left->parent = this;
        } else {
            left->insert(data_);
        }
    } else {
        if (right == nullptr) {
            right = new Node(data_);
            right->parent = this;
        } else {
            right->insert(data_);
        }
    }
    Node* newRoot = nullptr;
    updateHeight();
    if (left->height() - right->height() == 2) {
        if (data_ < left->data) {
            newRoot = simpleLeft();
        } else {
            newRoot = doubleLeft();
        }
    } else if (right->height() - left->height() == 2) {
        if (data_ > right->data) {
            newRoot = simpleRight();
        } else {
            newRoot = doubleRight();
        }
    }
}

template<typename T>
bool structures::AVLTree<T>::Node::remove(const T& data_) {}

template<typename T>
bool structures::AVLTree<T>::Node::contains(const T& data_) const {
    if (data_ == data) {
        return true;
    } else if (data_ < data) {
        if (left == nullptr) {
            return false;
        } else {
            return left->contains(data_);
        }
    } else {
        if (right == nullptr) {
            return false;
        } else {
            return right->contains(data_);
        }
    }
}

template<typename T>
void structures::AVLTree<T>::Node::updateHeight() {
    int left_height = -1;
    int right_height = -1;
    if (left != nullptr) {
        left_height = left->height();
    }
    if (right != nullptr) {
        right_height = right->height();
    }
    height_ = std::max(left_height, right_height) + 1;
}

template<typename T>
typename structures::AVLTree<T>::Node* AVLTree<T>::Node::simpleLeft() {
    Node* new_root = left;
    left = new_root->right;
    new_root->right = this;
    updateHeight();
    new_root->updateHeight();

    // Update parent's pointer to the new root
    if (parent != nullptr) {
        if (parent->left == this) {
            parent->left = new_root;
        } else {
            parent->right = new_root;
        }
    }
    new_root->parent = parent;
    parent = new_root;

    return new_root;
}

template<typename T>
typename structures::AVLTree<T>::Node* AVLTree<T>::Node::simpleRight() {
    Node* new_root = right;
    right = new_root->left;
    new_root->left = this;
    updateHeight();
    new_root->updateHeight();

    // Update parent's pointer to the new root
    if (parent != nullptr) {
        if (parent->left == this) {
            parent->left = new_root;
        } else {
            parent->right = new_root;
        }
    }
    new_root->parent = parent;
    parent = new_root;

    return new_root;
}

template<typename T>
typename structures::AVLTree<T>::Node* AVLTree<T>::Node::doubleLeft() {
    left = left->simpleRight();
    return simpleLeft();
}

template<typename T>
typename structures::AVLTree<T>::Node* AVLTree<T>::Node::doubleRight() {
    right = right->simpleLeft();
    return simpleRight();
}

template<typename T>
void structures::AVLTree<T>::Node::pre_order(ArrayList<T>& v) const {
    v.push_back(data);
    if (left != nullptr) {
        left->pre_order(v);
    }
    if (right != nullptr) {
        right->pre_order(v);
    }
}

template<typename T>
void structures::AVLTree<T>::Node::in_order(ArrayList<T>& v) const {
    if (left != nullptr) {
        left->in_order(v);
    }
    v.push_back(data);
    if (right != nullptr) {
        right->in_order(v);
    }
}

template<typename T>
void structures::AVLTree<T>::Node::post_order(ArrayList<T>& v) const {
    if (left != nullptr) {
        left->post_order(v);
    }
    if (right != nullptr) {
        right->post_order(v);
    }
    v.push_back(data);
}
