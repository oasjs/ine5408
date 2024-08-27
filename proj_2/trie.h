#include <string>

namespace structures {

class Trie {
  private:
    struct Node { // Nodo da Trie
        Node();

        Node*   chd[26];
        int     pos;
        int     len;

        int prefixed();
    };

    Node* root;

 public:
    Trie(); // Construtor
    ~Trie(); // Destrutor

    // Insere uma palavra na Trie.
    void insert(std::string word, const int& p, const int& l);

    // Procura pela palavra na Trie. Retorna um par<posicao, comprimento> caso
    // a palavra exista na Trie. Caso contrario retorna um par<-1, -1>
    std::pair<int, int> get(const std::string word);

    // Retorna o número de palavras prefixadas pela palavra fornecida.
    int getNumOfPrefixedWords(const std::string word_);
};

}   // namespace structures


using Trie = structures::Trie;

Trie::Trie() {
    root = new Node();
}

Trie::~Trie() {
    root = nullptr;
}

void Trie::insert(const std::string word, const int& p, const int& l) {
    Node* node = root;
    for (std::size_t i = 0; i < word.length(); i++) {
        int index = word[i] - 'a';
        if (!node->chd[index])
            node->chd[index] = new Node();
        node = node->chd[index];
    }
    node->pos = p;
    node->len = l;
}

std::pair<int, int> Trie::get(const std::string word) {
    Node* node = root;
    for (std::size_t i = 0; i < word.length() && node != nullptr; i++) {
        int index = word[i] - 'a';
        node = node->chd[index];
    }
    std::pair<int, int> pair = node == nullptr ? std::make_pair(-1,-1)
                                        : std::make_pair(node->pos, node->len);
    return pair;
}

int Trie::getNumOfPrefixedWords(const std::string word) {
    Node* node = root;
    for (std::size_t i = 0; i < word.length() && node != nullptr; i++) {
        int index = word[i] - 'a';
        node = node->chd[index];
    }
    if (node == nullptr) return 0;
    return node->prefixed();
}


// --- Node

Trie::Node::Node() {
    for (int i = 0; i < 26; i++)
        chd[i] = nullptr;
    pos = -1;
    len = 0;
}

int Trie::Node::prefixed() {
    int count = len > 0 ? 1 : 0;
    for (int i = 0; i < 26; i++) {
        Node* child = chd[i];
        if (child != nullptr) {
            count += child->prefixed();
        }
    }
    return count;
}