#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 5

struct Produto {
    int id;
    char nome[50];
    float preco;
    int quantidade;
};

// Função auxiliar para ler uma string de entrada
void lerString(char *string, int tamanho) {
    fgets(string, tamanho, stdin);
    string[strcspn(string, "\n")] = 0;  // Remove o newline do final da string
}

// Função auxiliar para buscar o índice de um produto pelo ID
int buscarProdutoPorID(struct Produto produtos[], int numProdutos, int id) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].id == id) {
            return i;
        }
    }
    return -1;  // Retorna -1 se não encontrar
}

// Função para adicionar um novo produto
void adicionarProduto(struct Produto produtos[], int *numProdutos) {
    if (*numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }
    
    struct Produto novoProduto;
    novoProduto.id = *numProdutos + 1;

    printf("Digite o nome do produto: ");
    getchar();  // Limpar o buffer do teclado
    lerString(novoProduto.nome, sizeof(novoProduto.nome));
    
    printf("Digite o preco do produto: ");
    scanf("%f", &novoProduto.preco);
    
    printf("Digite a quantidade do produto: ");
    scanf("%d", &novoProduto.quantidade);

    produtos[(*numProdutos)++] = novoProduto;
    printf("Produto adicionado com sucesso.\n");
}

// Função para listar todos os produtos
void listarProdutos(struct Produto produtos[], int numProdutos) {
    printf("Lista de Produtos:\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("ID: %d | Nome: %s | Preço: %.2f | Quantidade: %d\n", 
               produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }
}

// Função genérica para atualizar preço ou quantidade de um produto
void atualizarProduto(struct Produto produtos[], int numProdutos, int isPreco) {
    int id;
    printf("Digite o ID do produto para atualizar: ");
    scanf("%d", &id);

    int index = buscarProdutoPorID(produtos, numProdutos, id);
    if (index == -1) {
        printf("Produto não encontrado.\n");
        return;
    }

    if (isPreco) {
        printf("Digite o novo preco para %s: ", produtos[index].nome);
        scanf("%f", &produtos[index].preco);
        printf("Preco atualizado com sucesso.\n");
    } else {
        printf("Digite a nova quantidade para %s: ", produtos[index].nome);
        scanf("%d", &produtos[index].quantidade);
        printf("Quantidade atualizada com sucesso.\n");
    }
}

// Função para remover um produto
void removerProduto(struct Produto produtos[], int *numProdutos) {
    int id;
    printf("Digite o ID do produto para remover: ");
    scanf("%d", &id);

    int index = buscarProdutoPorID(produtos, *numProdutos, id);
    if (index == -1) {
        printf("Produto não encontrado.\n");
        return;
    }

    for (int j = index; j < *numProdutos - 1; j++) {
        produtos[j] = produtos[j + 1];
    }
    (*numProdutos)--;
    printf("Produto removido com sucesso.\n");
}

// Função para exibir o menu e obter a opção do usuário
int menu() {
    int opcao;
    printf("\nMenu:\n");
    printf("1. Adicionar Produto\n");
    printf("2. Listar Produtos\n");
    printf("3. Atualizar Preco\n");
    printf("4. Atualizar Quantidade\n");
    printf("5. Remover Produto\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

int main() {
    struct Produto produtos[MAX_PRODUTOS];
    int numProdutos = 0;
    int opcao;

    do {
        opcao = menu();

        switch (opcao) {
            case 1:
                adicionarProduto(produtos, &numProdutos);
                break;
            case 2:
                listarProdutos(produtos, numProdutos);
                break;
            case 3:
                atualizarProduto(produtos, numProdutos, 1);
                break;
            case 4:
                atualizarProduto(produtos, numProdutos, 0);
                break;
            case 5:
                removerProduto(produtos, &numProdutos);
                break;
            case 6:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 6);

    return 0;
}

