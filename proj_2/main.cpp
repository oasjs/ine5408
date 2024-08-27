#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "trie.h"

using namespace std;

void insertWords(string filename, Trie* t);

void checkWords(vector<string>* words, Trie* t);

int main(int argc, char* argv[]) {

    string filename;
    cin >> filename;  // entrada

    vector<string>* words = new vector<string>;

    string word;
    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        words->push_back(word);
    }

    Trie* t = new Trie();

    insertWords(filename, t);

    checkWords(words, t);

    delete t;

    return 0;
}

void insertWords(string filename, Trie* t) {

    // Abre o arquivo para leitura
    ifstream file(filename);

    // Verifica se o arquivo foi aberto corretamente
    if (file.is_open()) {

        string line;
        string word;
        int pos = 0;
        int len;

        while (getline(file, line)) {

            size_t end = line.find(']');
            word = line.substr(1, end - 1);
            len = line.length();

            t->insert(word, pos, len);

            pos += (len + 1);
        }

        // Fecha o arquivo
        file.close();
    } else {
        cout << "Falhou ao tentar abrir o arquivo: " << filename << endl;
    }
}

void checkWords(vector<string>* words,  Trie* t) {

    for (int i = 0; i < words->size(); i++) {
        string word = words->at(i);
        pair<int, int> word_info = t->get(word);
        int pos = word_info.first;
        int len = word_info.second;

        // Se len for -1, a palavra buscada não existe na Trie
        if (len != -1) {
            int n_prefixed = t->getNumOfPrefixedWords(word);
            cout << word << " is prefix of " << n_prefixed << " words" << endl;

            if (len > 0)
                cout << word << " is at (" << pos << "," << len << ")" << endl;
        } else
            cout << word << " is not prefix" << endl;
    }
}