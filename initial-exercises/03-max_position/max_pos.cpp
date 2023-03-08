#include <iostream>
using namespace std;

/*
(3) a criação de uma estrutura, denominada maxpos, contendo o valor do maior valor e a posição de sua primeira ocorrência; exemplo:
vetor de estrada: [10, 50, 30, 70, 20]
estrutura de saída: { 70, 3 }
*/

struct maxpos {
    int max;
    int pos;
};

maxpos maximo_posicao(int vet[], int N) {
    maxpos MP;
    MP.max = 0;
    MP.pos = 0;
    for (int i = 1; i < N; i = i + 1) {
        if (MP.max < vet[i]) {
            MP.max = vet[i];
            MP.pos = i;
        }
    }
    return MP;
}

int main() {
    int vet[10] = {10, 20, 60, 30, 40, 100, 50, 80, 90, 70};
    maxpos max_pos = maximo_posicao(vet, 10);
    int max = max_pos.max;
    int pos = max_pos.pos;
    cout << max;
    cout << pos;
    return 0;
}
