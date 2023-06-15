#include "../topic-4/array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
public:
    ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data_);

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_);

        Node* remove(const T& data_);

        bool contains(const T& data_) const;

        void pre_order(ArrayList<T>& v) const;

        void in_order(ArrayList<T>& v) const;

        void post_order(ArrayList<T>& v) const;

        bool has_left() const;

        bool has_right() const;
    };

    Node* root;
    std::size_t size_;
};

}   // namespace structures

#define tt template<typename T>
#define bt structures::BinaryTree<T>
#define al structures::ArrayList<T>


/* NODE */

tt
bt::Node::Node(const T& data_) {
    data = data_;
    left = nullptr;
    right = nullptr;
}

tt
bool bt::Node::has_left() const {
    if (left == nullptr)
        return false;
    else
        return true;
}

tt
bool bt::Node::has_right() const {
    if (right == nullptr)
        return false;
    else
        return true;
}

tt
void bt::Node::insert(const T& data_) {
    if (data_ < data) {
        if (has_left())
            left->insert(data_);
        else
            left = new Node(data_);
    } else if (data_ > data) {
        if (has_right())
            right->insert(data_);
        else
            right = new Node(data_);
    }
}

tt
bool bt::Node::contains(const T& data_) const {
    if (data_ == data) {
        return true;
    } else if (data_ < data) {
        if (!has_left())
            return false;
        else
            return left->contains(data_);
    } else {
        if (!has_right())
            return false;
        else
            return right->contains(data_);
    }
}

tt
void bt::Node::pre_order(ArrayList<T>& v) const {
    /* root, left, right */
    v.push_back(data);
    if (has_left())
        left->pre_order(v);
    if (has_right())
        right->pre_order(v);
}

tt
void bt::Node::in_order(ArrayList<T>& v) const {
    /* left, root, right */
    if (has_left())
        left->in_order(v);
    v.push_back(data);
    if (has_right())
        right->in_order(v);
}

tt
void bt::Node::post_order(ArrayList<T>& v) const {
    /* left, right, root */
    if (has_left())
        left->post_order(v);
    if (has_right())
        right->post_order(v);
    v.push_back(data);
}


/* BINART TREE */

tt
bt::~BinaryTree() {
    root = nullptr;
    size_ = 0u;
}

tt
void bt::insert(const T& data) {
    if (empty())
        root = new Node(data);
    else
        root->insert(data);
    ++size_;
}

tt
void bt::remove(const T& data) {
    if (empty())
        return;

    Node* parent = root;
    Node* removedNode;
    if (root->data != data) {
        // Looks for the node to be removed
        while (removedNode->data != data && removedNode != nullptr) {
            if (data < parent->data) {
                if (parent->has_left()) {
                    if (data == parent->left->data) {
                        removedNode = parent->left;
                    } else {
                        parent = parent->left;
                    }
                } else {
                    removedNode = nullptr;
                }
            } else if (data > parent->data) {
                if (parent->has_right()) {
                    if (data == parent->right->data) {
                        removedNode = parent->right;
                    } else {
                        parent = parent->right;
                    }
                } else {
                    removedNode = nullptr;
                }
            }
        }
    } else {
        removedNode = root;
    }

    if (removedNode == nullptr)
        return;

    if (removedNode->has_left() && removedNode->has_right()) {
        Node* replacementParent = removedNode;
        while (replacementParent->has_left() &&
                replacementParent->left->has_left())
            replacementParent = replacementParent->left;

        Node* replacement = replacementParent->left;
        removedNode->data = replacement->data;

        if (replacement->has_right())
            replacementParent->left = replacement->right;

        delete replacement;
        --size_;
        return;
    }
    if (removedNode == root) {
        root = root->has_left() ? root->left : root->right;
    } else {
        if (removedNode->data < parent->data) {
            parent->left = removedNode->has_left() ? removedNode->left
                                                : removedNode->right;
        } else {
            parent->right = removedNode->has_left() ? removedNode->left
                                                : removedNode->right;
        }
    }
    delete removedNode;
    --size_;

}

tt
bool bt::contains(const T& data) const {
    if (empty())
        return false;
    else
        return root->contains(data);
}

tt
bool bt::empty() const {
    if (size_ == 0u)
        return true;
    else
        return false;
}

tt
std::size_t bt::size() const {
    return size_;
}

tt
al bt::pre_order() const {
    al* arrayList = new al(size());
    root->pre_order(*arrayList);
    return *arrayList;
}

tt
al bt::in_order() const {
    al* arrayList = new al(size());
    root->in_order(*arrayList);
    return *arrayList;
}

tt
al bt::post_order() const {
    al* arrayList = new al(size());
    root->post_order(*arrayList);
    return *arrayList;
}
