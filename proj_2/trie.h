#include <string>

namespace structures {

class Trie {
 public:
    Trie();

    ~Trie();

    struct Node {
        Node();

        Node*   chd[26];
        int     pos;
        int     len;

        int prefixed();
    };

    void insert(std::string word, const int& p, const int& l);

    Node* get(const std::string word);

    int getNumOfPrefixedWords(const std::string word_);


 private:
    Node* root;

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

Trie::Node* Trie::get(const std::string word) {

    Node* node = root;
    for (std::size_t i = 0; i < word.length() && node != nullptr; i++) {
        int index = word[i] - 'a';
        node = node->chd[index];
    }
    return node;
}

int Trie::getNumOfPrefixedWords(const std::string word_) {
    Node* word = get(word_);
    if (word == nullptr) return 0;
    return word->prefixed();
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