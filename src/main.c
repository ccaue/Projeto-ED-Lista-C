#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os dados de um contato
typedef struct Contato {
    char nome[50];
    char telefone[20];
    char email[50];
} Contato;

// Nó da lista ligada
typedef struct No {
    Contato contato;
    struct No *proximo;
} No;

// Função para criar um novo contato
Contato criarContato(char *nome, char *telefone, char *email) {
    Contato novoContato;
    strcpy(novoContato.nome, nome);
    strcpy(novoContato.telefone, telefone);
    strcpy(novoContato.email, email);
    return novoContato;
}

// Função para adicionar um novo contato à lista (já adiciona em ordem alfabética)
void adicionarContato(No **lista, Contato contato) {
    No *novo = malloc(sizeof(No)); // Aloca espaço na memória com o tamanho de um nó
    novo->contato = contato;
    novo->proximo = NULL;

    // Insere o contato no início da lista se ela estiver vazia
    if (*lista == NULL || strcmp(contato.nome, (*lista)->contato.nome) < 0) {
        novo->proximo = *lista;
        *lista = novo;
    }
    else {
        // Encontra a posição correta para inserir o novo contato
        No *atual = *lista;

        while (atual->proximo != NULL && strcmp(atual->proximo->contato.nome, contato.nome) < 0) {
            atual = atual->proximo;
        }
        // Insere o novo nó na posição correta
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
    printf("Contato adicionado com sucesso!\n");
}

// Função para remover um contato da lista pelo nome
void removerContato(No **lista, char *nome) {
    No *atual = *lista;
    No *anterior = NULL;

    while (atual != NULL && strcmp(atual->contato.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Contato não encontrado.\n");
        return;
    }
    if (anterior == NULL) {
        *lista = atual->proximo;
    }
    else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("Contato removido com sucesso.\n");
}

// Função para buscar o contato
void buscarContatos(No *lista, char *nome) {
    No *atual = lista;
    int encontrado = 0;

    while (atual != NULL) {
        if (strcmp(atual->contato.nome, nome) == 0) {
            encontrado = 1;
            printf("Contato encontrado:\n");
            printf("Nome: %s\n", atual->contato.nome);
            printf("Telefone: %s\n", atual->contato.telefone);
            printf("Email: %s\n", atual->contato.email);
            printf("--------------------------------------\n");
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("Nenhum contato encontrado com o nome '%s'.\n", nome);
    }
}

// Função para listar todos os contatos
void listarContatos(No *lista) {
    No *atual = lista;

    if (atual == NULL) {
        printf("A lista de contatos está vazia.\n");
        return;
    }
    while (atual != NULL) {
        printf("Nome: %s\n", atual->contato.nome);
        printf("Telefone: %s\n", atual->contato.telefone);
        printf("Email: %s\n", atual->contato.email);
        printf("--------------------------------------\n");
        atual = atual->proximo;
    }
}

// Função para exibir o menu
int menu() {
    int opcao;

    printf("\n---------- Menu de Comandos ----------\n");
    printf("0. Sair\n");
    printf("1. Adicionar contato\n");
    printf("2. Remover contato\n");
    printf("3. Buscar contato\n");
    printf("4. Listar contatos\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();
    printf("--------------------------------------\n");
    return opcao;
}

// Função para verificar se a entrada dos dados está vazia
int entradaVazia(char *entrada) {
    return strlen(entrada) == 0;
}

// Função para validar número de telefone
int validarTelefone(char *telefone) {
    for (int i = 0; telefone[i] != '\0'; i++) {
        if (!isdigit(telefone[i]) && telefone[i] != ' ' && telefone[i] != '(' && telefone[i] != ')' && telefone[i] != '-') {
            return 0; // Retorna 0 se algum caractere for diferente de "(", ")", "-", espaço ou numeral
        }
    }
    return 1; // Retorna 1 se todos os caracteres forem válidos
}

// Função para validar se o e-mail contém "@" e "."
int validarEmail(char *email) {
    char *arroba = strchr(email, '@');
    char *ponto = strrchr(email, '.');

    return arroba != NULL && ponto != NULL && ponto > arroba;
}

// Função principal para interagir com o usuário
int main() {
    No *listaContatos = NULL;
    int opcao;
    char nome[50], telefone[20], email[50];

    printf("========== Lista de Contatos =========\n");

    do {
        opcao = menu();
        switch (opcao) {
            case 0: // Sair
                printf("Saindo...\n");
                break;

            case 1: // Adicionar contato
                do {
                    printf("Digite o nome: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0'; // Remover o '\n' do final

                    if (entradaVazia(nome)) {
                    printf("Erro: O nome não foi digitado.\n");
                    }
                } while (entradaVazia(nome));

                do {
                    printf("Digite o telefone: ");
                    fgets(telefone, sizeof(telefone), stdin);
                    telefone[strcspn(telefone, "\n")] = '\0';

                    if (entradaVazia(telefone) || !validarTelefone(telefone)) {
                        printf("Erro: O telefone não pode conter letras.\n");
                    }
                } while (entradaVazia(telefone) || !validarTelefone(telefone));

                do {
                    printf("Digite o email: ");
                    fgets(email, sizeof(email), stdin);
                    email[strcspn(email, "\n")] = '\0';

                    if (entradaVazia(email) || !validarEmail(email)) {
                        printf("Erro: O Email digitado é inválido (sem @ e .).\n");
                    }
                } while (entradaVazia(email) || !validarEmail(email));

                Contato novoContato = criarContato(nome, telefone, email);
                adicionarContato(&listaContatos, novoContato);
                break;

            case 2: // Remover contato
                printf("Digite o nome do contato a ser removido: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerContato(&listaContatos, nome);
                break;

            case 3: // Buscar contato
                printf("Digite o nome do contato a ser buscado: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                buscarContatos(listaContatos, nome);
                break;

            case 4: // Listar contatos
                listarContatos(listaContatos);
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
