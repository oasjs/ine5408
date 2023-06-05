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
        Node(const T& data_);

        T data;
        Node* left;
        Node* right;

        void insert(const T& data_);

        bool remove(const T& data_);

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

// Nota: Não dá para fazer isso com recursão, pois não é possível!!!
tt
bool bt::Node::remove(const T& data_) {
    if (data_ < data && has_left()) {
        // If left is to be removed
        if (left->data == data_) {
            Node* replacement = left;
            if (left->has_left() and left->has_right()) {

                Node* father = left;
                // Father is the node before the newRoot
                while (father->has_right() && father->right->has_right())
                    father = father->right;

                replacement = father->right;
                left->data = replacement->data;

                if (replacement->has_left())
                    father->right = replacement->left;

            } else if(left->has_left())
                left = left->left;
            else if(left->has_right())
                left = left->right;

            std::cout << "Deleting " << replacement->data << std::endl;
            delete replacement;
            return true;
        } else {
            return remove(left->data);
        }
    } else if (data_ > data && has_right()) {
        // If right is to be removed
        if (right->data == data_) {
            Node* replacement = right;
            if (right->has_left() && right->has_right()) {

                Node* father = right;
                // Father is the node before the newRoot
                while (father->has_left() && father->left->has_left())
                    father = father->left;

                replacement = father->left;
                right->data = replacement->data;

                if (replacement->has_right())
                    father->left = replacement->right;

            } else if (right->has_left())
                right = right->left;
            else if (right->has_right())
                right = right->right;

            std::cout << "Deleting " << replacement->data << std::endl;
            delete replacement;
            return true;
        } else {
            return remove(right->data);
        }
    } else {
        // Data is not in the tree
        return false;
    }
}

tt
bool bt::Node::contains(const T& data_) const {
    if (data_ == data) {
        return true;
    }
    else if (data_ < data) {
        if (!has_left())
            return false;
        else
            return left->contains(data_);
    }
    else {
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
    /* right, root, left */
    if (has_left())
        left->post_order(v);
    if (has_right())
        right->post_order(v);
    v.push_back(data);
}


/* BINART TREE */

tt
bt::~BinaryTree() {}

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
    if (!empty()) {
        if (root->data == data) {
        // If root is to be deleted
            Node* replacement = root;
            if (root->has_left() && root->has_right()) {

                Node* father = root->right;
                // Father is the node before the newRoot
                while (father->has_left() && father->left->has_left()) 
                    father = father->left;

                replacement = father->left;
                root->data = replacement->data;

                if (replacement->has_right())
                    father->left = replacement->right;
            } else if(root->has_left())
                root = root->left;
            else if(root->has_right())
                root = root->right;

            delete replacement;
            --size_;
        } else {
            bool removed = root->remove(data);
            if (removed)
                --size_;
        }
    }
}

tt
bool bt::contains(const T& data) const{
    if (empty())
        return false;
    else
        return root->contains(data);
}

tt
bool bt::empty() const{
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