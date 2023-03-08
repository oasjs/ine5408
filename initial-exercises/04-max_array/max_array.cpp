#include <iostream>
using namespace std;

/*
(4) o cálculo de máximo ponto-a-ponto entre dois vetores vet1 e vet2 de mesmo tamanho N; a resposta consiste em atualização dos valores próprio vet1; exemplo:
vetor 1 original de entrada:  [10, 50, 30, 70, 20]
vetor 2 original de entrada:  [30, 40, 20, 70, 10]
vetor 1 após o processamento: [30, 50, 30, 70, 20]}
*/

void maximo_vetores(int vet1[], int vet2[], int N) {
    for (int i = 0; i < N; i++) {
        if (vet2[i] > vet1[i]) {
            vet1[i] = vet2[i];

        } 
        cout << vet1[i]; 
        cout << "\n";
    }
}

int main() {
    int vet1[5] = {10, 50, 30, 70, 20};
    int vet2[5] = {30, 40, 20, 70, 10};
    maximo_vetores(vet1, vet2, 5);
}
