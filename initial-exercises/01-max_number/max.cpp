#include <iostream>
using namespace std;

/*
(1) o cálculo do maior valor; exemplo:
vetor de entrada: [10, 50, 30, 70, 20]
valor de saída: 70
*/

int max(int vet[], int N) {
    int r = vet[0];
    int i;
    for (i = 1; i < N; i = i + 1) {
        if (r < vet[i]) r = vet[i];
    }
    return r;
}

int main() {
    int vet[10] = {10, 20, 60, 30, 40, 100, 50, 80, 90, 70};
    int max_num = max(vet, 10);
    cout << max_num;
    return 0;
}
