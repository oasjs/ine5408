//! Copyright [year] <Copyright Owner>

#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>


namespace structures {

//! ...
template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {  // implementar cada um dos métodos de Node
     public:
        explicit Node(const T& data) {
            data_ = data;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        Node(const T& data, Node* prev, Node* next) {
            data_ = data;
            prev_ = prev;
            next_ = next;
        }

        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }
        const Node* next() const {
            return next_;
        }
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;  // primeiro da lista
    Node* tail;  // ultimo da lista
    std::size_t size_;
};

}  // namespace structures

#endif


template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    if (size_ > 1) {
        Node* node = head->next();
        for (std::size_t i = 1; i < size_; i++) {
            delete node->prev();
            node = node->next();
        }
    }
    delete tail;
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    Node* newNode = new Node(data);
    if (newNode == nullptr) throw std::out_of_range("List is full!");
    if (size_ > 0) {
        tail->next(newNode);
        newNode->prev(tail);
    } else {
        head = newNode;
    }
    tail = newNode;
    ++size_;
}  // insere no fim

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node* newNode = new Node(data);
    if (newNode == nullptr) throw std::out_of_range("List is full!");
    if (size_ > 0) {
        head->prev(newNode);
        newNode->next(head);
    } else {
        tail = newNode;
    }
    head = newNode;
    ++size_;
}  // insere no início

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index < 0 || index > size_) throw std::out_of_range("Invalid index!");
    if (index == 0 || empty()) return push_front(data);
    if (index == size_) return push_back(data);

    Node* newNode = new Node(data);
    if (newNode == nullptr) throw std::out_of_range("List is full!");
    Node* prev;
    if (index < std::size_t(size_ / 2)) {
        prev = head;
        for (std::size_t i = 0; i < index - 1; i++)
            prev = prev->next();
    } else {
        prev = tail;
        for (std::size_t i = size_ - 1; i > index - 1; i--)
            prev = prev->prev();
    }
    if (prev->next() != nullptr) {
        newNode->next(prev->next());
        prev->next()->prev(newNode);
    }
    newNode->prev(prev);
    prev->next(newNode);
    ++size_;
}  // insere na posição

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    Node* node = head;
    std::size_t index = 0u;
    while (index < size_ && data > node->data()) {
        node = node->next();
        ++index;
    }
    return insert(data, index);
}  // insere em ordem

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (empty()) throw std::out_of_range("List is already empty!");
    if (index < 0 || index >= size_) throw std::out_of_range("Invalid index!");
    Node* nodeToPop;
    if (index < size_t(size_ / 2)) {
        nodeToPop = head;
        for (size_t i = 0; i < index; i++)
            nodeToPop = nodeToPop->next();
    } else {
        nodeToPop = tail;
        for (size_t i = size_ - 1; i > index; i--)
            nodeToPop = nodeToPop->prev();
    }

    T data = nodeToPop->data();
    if (size_ == 1) {
        clear();
        return data;
    }
    if (index == 0)
        head = nodeToPop->next();
    if (index == size_ - 1)
        tail = nodeToPop->prev();
    if (nodeToPop->prev() != nullptr)
        nodeToPop->prev()->next(nodeToPop->next());
    if (nodeToPop->next() != nullptr)
        nodeToPop->next()->prev(nodeToPop->prev());

    delete nodeToPop;
    --size_;
    return data;
}  // retira da posição


template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    return pop(size_ - 1);
}  // retira do fim
template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    return pop(0);
}  // retira do início

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    pop(find(data));
}  // retira específico

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    if (size_ == 0u) return true;
    return false;
}  // lista vazia

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    size_t index = find(data);
    if (index == size_) return false;
    return true;
}  // contém

template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    if (index < 0 || index >= size_) throw std::out_of_range("Invalid index!");
    Node* node;
    if (index < size_t(size_ / 2)) {
        node = head;
        for (size_t i = 0; i < index; i++)
            node = node->next();
    } else {
        node = tail;
        for (size_t i = size_ - 1; i > index; i--)
            node = node->prev();
    }
    return node->data();
}  // acesso a um elemento (checando limites)

template<typename T>
const T& structures::DoublyLinkedList<T>::at(std::size_t index) const {
    return at(index);
}  // getter constante a um elemento

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    if (empty()) throw std::out_of_range("List is empty!");
    Node* node = head;
    size_t index = 0;
    while (index < size_ && node->data() != data) {
        node = node->next();
        index++;
    }
    return index;
}  // posição de um dado

template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}  // tamanho
