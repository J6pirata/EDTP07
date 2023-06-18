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

struct Guiche {
    int id;
    Fila* senhasAtendidas;
};

Fila* initFila() {
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
    Fila* senhasGeradas = initFila();
    int Guiche* guiches;
    int opcao;
    int senhaAtual = 1;

    do {
        cout << "Seletor - Escolha uma opcao:" << endl;
        cout << "0. Sair" << endl;
        cout << "1. Gerar senha" << endl;
        cout << "2. Abrir guiche" << endl;
        cout << "3. Chamar senha" << endl;
        cout << "4. Listar senhas atendidas por guiche" << endl;
        cout << "Senhas aguardando atendimento: " << count(senhasGeradas) << endl;
        cout << "Guiches abertos: " << guiches.size() << endl;
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
            case 2: {
                int guicheId;
                cout << "Digite o ID do guiche: ";
                cin >> guicheId;
                if (guiches.find(guicheId) != guiches.end()) {
                    cout << "Guiche com ID " << guicheId << " ja esta aberto." << endl;
                } else {
                    Guiche* guiche = new Guiche;
                    guiche->id = guicheId;
                    guiche->senhasAtendidas = initFila();
                    guiches[guicheId] = guiche;
                    cout << "Guiche com ID " << guicheId << " aberto com sucesso." << endl;
                }
                break;
            }
            case 3: {
                if (isEmpty(senhasGeradas)) {
                    cout << "Nao ha senhas aguardando atendimento." << endl;
                } else {
                    float senha = dequeue(senhasGeradas);
                    int guicheId;
                    cout << "Digite o ID do guiche que esta chamando a senha: ";
                    cin >> guicheId;
                    if (guiches.find(guicheId) == guiches.end()) {
                        cout << "Guiche com ID " << guicheId << " nao existe." << endl;
                    } else {
                        Guiche* guiche = guiches[guicheId];
                        enqueue(guiche->senhasAtendidas, senha);
                        cout << "Senha " << senha << " chamada pelo guiche " << guicheId << endl;
                    }
                }
                break;
            }
            case 4: {
                int guicheId;
                cout << "Digite o ID do guiche: ";
                cin >> guicheId;
                if (guiches.find(guicheId) == guiches.end()) {
                    cout << "Guiche com ID " << guicheId << " nao existe." << endl;
                } else {
                    Guiche* guiche = guiches[guicheId];
                    cout << "Senhas atendidas pelo guiche " << guicheId << ":" << endl;
                    print(guiche->senhasAtendidas);
                }
                break;
            }
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }

        cout << endl;

    } while (count(senhasGeradas) > 0 || !guiches.empty());

    int totalSenhasAtendidas = 0;
    for (auto it = guiches.begin(); it != guiches.end(); ++it) {
        Guiche* guiche = it->second;
        totalSenhasAtendidas += count(guiche->senhasAtendidas);
        freeFila(guiche->senhasAtendidas);
        delete guiche;
    }
    freeFila(senhasGeradas);

    cout << "Total de senhas atendidas: " << totalSenhasAtendidas << endl;

    return 0;
}