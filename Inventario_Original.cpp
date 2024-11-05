#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_PRODUTOS 5

struct Produto {
    int id;
    char nome[50];
    float preco;
    int quantidade;
};

	void medirTempoExecucao(void (*func)()) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    func();  // Executa a fun��o passada como par�metro
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execu��o: %f segundos\n", cpu_time_used);
}

void medirUsoMemoria() {
    // Esta fun��o pode ser chamada ap�s opera��es para verificar uso de mem�ria
    malloc_stats();  // Esta fun��o imprime estat�sticas de aloca��o de mem�ria no terminal
}

void adicionarProduto(struct Produto produtos[], int *numProdutos) {
    if (*numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }
    
    produtos[*numProdutos].id = *numProdutos + 1;
    printf("Digite o nome do produto: ");
    scanf("%s", produtos[*numProdutos].nome);
    printf("Digite o preco do produto: ");
    scanf("%f", &produtos[*numProdutos].preco);
    printf("Digite a quantidade do produto: ");
    scanf("%d", &produtos[*numProdutos].quantidade);
    
    (*numProdutos)++;
    printf("Produto adicionado com sucesso.\n");
}

void listarProdutos(struct Produto produtos[], int numProdutos) {
    printf("Lista de Produtos:\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("ID: %d | Nome: %s | Pre�o: %.2f | Quantidade: %d\n", 
               produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }
}

void atualizarPreco(struct Produto produtos[], int numProdutos) {
    int id, encontrado = 0;
    float novoPreco;
    printf("Digite o ID do produto para atualizar o pre�o: ");
    scanf("%d", &id);

    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].id == id) {
            encontrado = 1;
            printf("Digite o novo preco para %s: ", produtos[i].nome);
            scanf("%f", &novoPreco);
            produtos[i].preco = novoPreco;
            printf("Preco atualizado com sucesso.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Produto n�o encontrado.\n");
    }
}

void atualizarQuantidade(struct Produto produtos[], int numProdutos) {
    int id, encontrado = 0;
    int novaQuantidade;
    printf("Digite o ID do produto para atualizar a quantidade: ");
    scanf("%d", &id);

    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].id == id) {
            encontrado = 1;
            printf("Digite a nova quantidade para %s: ", produtos[i].nome);
            scanf("%d", &novaQuantidade);
            produtos[i].quantidade = novaQuantidade;
            printf("Quantidade atualizada com sucesso.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Produto n�o encontrado.\n");
    }
}

void removerProduto(struct Produto produtos[], int *numProdutos) {
    int id, encontrado = 0;
    printf("Digite o ID do produto para remover: ");
    scanf("%d", &id);

    for (int i = 0; i < *numProdutos; i++) {
        if (produtos[i].id == id) {
            encontrado = 1;
            for (int j = i; j < *numProdutos - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            (*numProdutos)--;
            printf("Produto removido com sucesso.\n");
            break;
        }
    }
    if (!encontrado) {
        printf("Produto n�o encontrado.\n");
    }
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Adicionar Produto\n");
    printf("2. Listar Produtos\n");
    printf("3. Atualizar Preco\n");
    printf("4. Atualizar Quantidade\n");
    printf("5. Remover Produto\n");
    printf("6. Sair\n");
    printf("Escolha uma op��o: ");
}

int main() {
    struct Produto produtos[MAX_PRODUTOS];
    int numProdutos = 0;
    int opcao;

    do {
        menu();
        scanf("%d", &opcao);

        if (opcao == 1) {
            adicionarProduto(produtos, &numProdutos);
        } else if (opcao == 2) {
            listarProdutos(produtos, numProdutos);
        } else if (opcao == 3) {
            atualizarPreco(produtos, numProdutos);
        } else if (opcao == 4) {
            atualizarQuantidade(produtos, numProdutos);
        } else if (opcao == 5) {
            removerProduto(produtos, &numProdutos);
        } else if (opcao != 6) {
            printf("Op��o inv�lida.\n");
        }

    } while (opcao != 6);
    
     printf("Vers�o N�o Fatorada:\n");
    medirTempoExecucao(executarVersaoNaoFatorada);
    medirUsoMemoria();

    printf("Encerrando o programa.\n");
    return 0;
}

