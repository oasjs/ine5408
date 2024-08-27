//! Copyright [year] <Copyright Owner>

namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

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
    class Node {
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

    Node* head;
    std::size_t size_;
};

}   // namespace structures


template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    head = nullptr;
    size_ = 0u;
}
template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    if (empty()) return;
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    Node* newNode = new Node(data);
    if (newNode == nullptr) throw std::out_of_range("List is full!");
    if (empty()) {
        head = newNode;
        head->next(newNode);
        head->prev(newNode);
    } else {
        newNode->prev(head->prev());
        head->prev()->next(newNode);
        newNode->next(head);
        head->prev(newNode);
    }
    size_++;
}  // insere no fim

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node* newNode = new Node(data);
    if (newNode == nullptr) throw std::out_of_range("List is full!");
    if (empty()) {
        head = newNode;
        head->next(newNode);
        head->prev(newNode);
    } else {
        newNode->prev(head->prev());
        head->prev()->next(newNode);
        newNode->next(head);
        head->prev(newNode);
    }
    head = newNode;
    size_++;
}  // insere no início

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data,
std::size_t index) {
    if (index < 0 || index > size_) throw std::out_of_range("Invalid index!");
    if (index == 0) return push_front(data);
    if (index == size_) return push_back(data);

    Node* newNode = new Node(data);
    if (newNode == nullptr) throw std::out_of_range("List is already full!");
    Node* newNodePrev = head;
    for (std::size_t i = 0; i < index - 1; i++) {
        newNodePrev = newNodePrev->next();
    }
    newNode->prev(newNodePrev);
    newNode->next(newNodePrev->next());
    newNodePrev->next()->prev(newNode);
    newNodePrev->next(newNode);
    size_++;
}  // insere na posição

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty()) return push_back(data);
    std::size_t index = 0;
    Node* node = head;
    while (index < size_ && node->data() < data) {
        node = node->next();
        index++;
    }
    insert(data, index);
}  // insere em ordem

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (empty()) throw std::out_of_range("List is already empty!");
    if (index < 0 || index >= size_) throw std::out_of_range("Invalid index!");
    Node* nodeToPop = head;
    for (std::size_t i = 0; i < index; i++) {
        nodeToPop = nodeToPop->next();
    }
    nodeToPop->next()->prev(nodeToPop->prev());
    nodeToPop->prev()->next(nodeToPop->next());
    if (index == 0) head = nodeToPop->next();
    T data = nodeToPop->data();
    delete nodeToPop;
    size_--;
    if (empty()) head = nullptr;
    return data;
}  // retira da posição

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    return pop(size_ - 1);
}  // retira do fim

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    return pop(0);
}  // retira do início

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    std::size_t index = find(data);
    if (index >= size_) throw std::out_of_range("Invalid index");
    pop(index);
}  // retira específico

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    if (size_ == 0u) return true;
    return false;
}  // lista vazia

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    if (find(data) == size_) return false;
    return true;
}  // contém

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (empty()) throw std::out_of_range("List is empty! Nothing to see.");
    if (index < 0 || index >= size_) throw std::out_of_range("Invalid index");
    Node* node = head;
    for (std::size_t i = 0; i < index; i++) {
        node = node->next();
    }
    return node->data();
}  // acesso a um elemento (checando limites)

template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    return at(index);
}  // getter constante a um elemento

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    if (empty()) throw std::out_of_range("List is empty! Nothing to find.");
    Node* node = head;
    std::size_t index = 0;
    while (index < size_ && node->data() != data) {
        node = node->next();
        index++;
    }
    return index;
}  // posição de um dado

template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}  // tamanho
