//! Copyright [year] <Copyright Owner>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>


namespace structures {

//! ...
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
    Node* tail{nullptr};
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedList<T>::LinkedList() {
    head = nullptr;
    size_ = 0u;
    tail = nullptr;
}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
    head = nullptr;
    size_ = 0u;
    tail = nullptr;
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    Node* newTail = new Node(data);
    if (empty()) {
        head = newTail;
        tail = newTail;
    } else {
        tail->next(newTail);
        tail = newTail;
    }
    ++size_;
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* newHead = new Node(data);
    if (empty()) {
        head = newHead;
        tail = newHead;
    } else {
        newHead->next(head);
        head = newHead;
    }
    ++size_;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_ || index < 0)
        throw std::out_of_range("Invalid index!");

    Node* newNode = new Node(data);
    if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        Node* previous = head;
        for (std::size_t i = 0; i < index - 1; i++) {
            previous = previous->next();
        }
        newNode->next(previous->next());
        previous->next(newNode);
        ++size_;
    }
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    Node* previous = head;
    std::size_t index = 0;
    while (index < size_ && data > previous->data()) {
        previous = previous->next();
        index++;
    }
    insert(data, index);
}

template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (index > size_ - 1 || index < 0)
        throw std::out_of_range("Invalid index!");

    Node* node = head;
    for (std::size_t i = 0; i < index; i++)
        node = node->next();
    return node->data();
}

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("List is already empty!");
    if (index > size_ - 1 || index < 0)
        throw std::out_of_range("Invalid index!");

    Node* nodeToPop;
    if (index == 0) {
        nodeToPop = head;
        if (size_ == 1) {
            clear();
            return nodeToPop->data();
        } else {
            head = head->next();
        }
    } else {
        Node* previous = head;
        for (std::size_t i = 0; i < index - 1; i++)
            previous = previous->next();
        nodeToPop = previous->next();
        if (index != size_ - 1)
            previous->next(nodeToPop->next());
        else
            tail = previous;
    }
    --size_;
    return nodeToPop->data();
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
    return pop(0);
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("List is already empty!");

    std::size_t index;
    Node* node = head;
    for (index = 0; index < size_ && data != node->data(); index++)
        node = node->next();
    pop(index);
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
    if (size_ == 0)
        return true;
    else
        return false;
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    Node* node = head;
    for (std::size_t i = 0; i < size_; i++) {
        if (node->data() == data)
            return true;
        node = node->next();
    }
    return false;
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    Node* node = head;
    for (std::size_t i = 0; i < size_; i++) {
        if (node->data() == data)
            return i;
        node = node->next();
    }
    return size_;
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}
