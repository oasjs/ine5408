#include <iostream>
using namespace std;

/*
(2) a posição (ou índice) da primeira ocorrência do maior valor; exemplo:
vetor de entrada: [10, 50, 30, 70, 20]
posição de saída: 3
*/

int posicao(int vet[], int N) {
    int pos = 0;
    int max = vet[0];
    int i;
    for (i = 1; i < N; i = i + 1) {
        if (max < vet[i]) {
            max = vet[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int vet[10] = {10, 20, 60, 30, 40, 100, 50, 80, 90, 70};
    int max_num = posicao(vet, 10);
    cout << max_num;
    return 0;
}
