// Copyright [2022] <COLOQUE SEU NOME AQUI...>
#include "./stack-vpl/array_stack.h"

bool verificaChaves(std::string trecho_programa)
{
    bool resposta = true;
    int tamanho = trecho_programa.length();
    structures::ArrayStack<char> pilha(500);

    for (int i = 0; i < tamanho; i++) {
        if (trecho_programa[i] == '{')
            pilha.push('1');
        else if (trecho_programa[i] == '}')
            pilha.pop();
    }
    if (pilha.size() > 0)
        resposta == false;

    return resposta;
}
