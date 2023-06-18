#include <iostream>
using namespace std;

struct No {
    float dado;
    struct No* prox;
};

struct Fila {
    No* ini;
    No* fim;
};
Fila* init() {
    Fila* f = new Fila;
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

int isEmpty(Fila* f) {
    return (f->ini == NULL);
}

int count(Fila* f) {
    int qtde = 0;
    No* no;
    no = f->ini;
    while (no != NULL) {
        qtde++;
        no = no->prox;
    }
    return qtde;
}

void print(Fila* f) {
    No* no;
    no = f->ini;
    cout << "------------" << endl;
    while (no != NULL) {
        cout << no->dado << endl;
        no = no->prox;
    }
    cout << "------------" << endl;
}

void freeFila(Fila* f) {
    No* no = f->ini;
    while (no != NULL) {
        No* temp = no->prox;
        free(no);
        no = temp;
    }
    free(f);
}

// Enfileirar
void enqueue(Fila* f, float v) {
    No* no = new No;
    no->dado = v;
    no->prox = NULL;
    if (isEmpty(f)) {
        f->ini = no;
    } else {
        f->fim->prox = no;
    }
    f->fim = no;
}

// Desenfileirar
float dequeue(Fila* f) {
    float ret;
    if (isEmpty(f)) {
        ret = -1;
    } else {
        No* no = f->ini;
        ret = no->dado;
        f->ini = no->prox;
        if (f->ini == NULL) {
            f->fim = NULL;
        }
        free(no);
    }
    return ret;
}

int main() {
    Fila* senhasGeradas = init();
    Fila* senhasAtendidas = init();
    int opcao;
    int senhaAtual = 1;

    do {
        cout << "Seletor - Escolha uma opcao:" << endl;
        cout << "0. Sair" << endl;
        cout << "1. Gerar senha" << endl;
        cout << "2. Realizar atendimento" << endl;
        cout << "Senhas aguardando atendimento: " << count(senhasGeradas) << endl;
        cin >> opcao;

        switch (opcao) {
            case 0:
                cout << "Encerrando o programa..." << endl;
                break;
            case 1:
                enqueue(senhasGeradas, senhaAtual);
                cout << "Senha gerada: " << senhaAtual << endl;
                senhaAtual++;
                break;
            case 2:
                if (isEmpty(senhasGeradas)) {
                    cout << "Nao ha senhas aguardando atendimento." << endl;
                } else {
                    float senha = dequeue(senhasGeradas);
                    enqueue(senhasAtendidas, senha);
                    cout << "Atendendo a senha: " << senha << endl;
                }
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }

        cout << endl






