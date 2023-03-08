#include <iostream>
using namespace std;

/*
(5) a construção de uma inversão do vetor, ou seja, o primeiro passa a ser o último, o segundo passa a ser o penúltimo, e assim por diante; exemplo:
vetor original: [A, B, C, D, E]
vetor após a chamada do método: [E, D, C, B, A]
*/
void inversao(int vet[], int N) {
    int inverted_array[N];
    for (int i = N-1; i >= 0; i--) {
        inverted_array[N-i-1] = vet[i];
        cout << vet[i];
        cout << "\n";
    }
}

int main() {
    int vet[5] = {1, 2, 3, 4, 5};
    inversao(vet, 5);
    return 0;
}