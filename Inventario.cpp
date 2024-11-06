#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 50  // Aumentado o limite de produtos para 50

typedef struct {
    int id;
    char nome[50];
    float preco;
    int quantidade;
} Produto;

// Função auxiliar para ler uma string de entrada
void lerString(char *string, int tamanho) {
    fgets(string, tamanho, stdin);
    string[strcspn(string, "\n")] = 0;  // Remove o newline do final da string
}

// Função auxiliar para buscar o índice de um produto pelo ID
int buscarProdutoPorID(const Produto produtos[], int numProdutos, int id) {
    for (int i = 0; i < numProdutos; i++) {
        if (produtos[i].id == id) {
            return i;
        }
    }
    return -1;  // Retorna -1 se não encontrar
}

// Função para adicionar um novo produto com ID automático
void adicionarProduto(Produto produtos[], int *numProdutos, int *proximoID) {
    if (*numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }
    
    Produto novoProduto;
    novoProduto.id = (*proximoID)++;  // Atribui o próximo ID e incrementa

    printf("Digite o nome do produto: ");
    getchar();  // Limpar o buffer do teclado
    lerString(novoProduto.nome, sizeof(novoProduto.nome));
    
    printf("Digite o preco do produto: ");
    scanf("%f", &novoProduto.preco);
    
    printf("Digite a quantidade do produto: ");
    scanf("%d", &novoProduto.quantidade);

    produtos[(*numProdutos)++] = novoProduto;
    printf("Produto adicionado com sucesso. ID: %d\n", novoProduto.id);
}

// Função para listar todos os produtos
void listarProdutos(const Produto produtos[], int numProdutos) {
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("Lista de Produtos:\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("ID: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n", 
               produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }
}

// Função para atualizar um campo do produto
void atualizarCampoProduto(Produto produtos[], int numProdutos, int id, const char *campo) {
    int index = buscarProdutoPorID(produtos, numProdutos, id);
    if (index == -1) {
        printf("Produto nao encontrado.\n");
        return;
    }

    if (strcmp(campo, "preco") == 0) {
        printf("Digite o novo preco para %s: ", produtos[index].nome);
        scanf("%f", &produtos[index].preco);
        printf("Preco atualizado com sucesso.\n");
    } else if (strcmp(campo, "quantidade") == 0) {
        printf("Digite a nova quantidade para %s: ", produtos[index].nome);
        scanf("%d", &produtos[index].quantidade);
        printf("Quantidade atualizada com sucesso.\n");
    } else {
        printf("Campo desconhecido.\n");
    }
}

// Função para remover um produto
void removerProduto(Produto produtos[], int *numProdutos, int id) {
    int index = buscarProdutoPorID(produtos, *numProdutos, id);
    if (index == -1) {
        printf("Produto nao encontrado.\n");
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
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    int numProdutos = 0;
    int proximoID = 1;  // Inicializa o próximo ID disponível
    int opcao;

    do {
        opcao = menu();

        switch (opcao) {
            case 1:
                adicionarProduto(produtos, &numProdutos, &proximoID);
                break;
            case 2:
                listarProdutos(produtos, numProdutos);
                break;
            case 3: {
                int id;
                printf("Digite o ID do produto para atualizar o preço: ");
                scanf("%d", &id);
                atualizarCampoProduto(produtos, numProdutos, id, "preco");
                break;
            }
            case 4: {
                int id;
                printf("Digite o ID do produto para atualizar a quantidade: ");
                scanf("%d", &id);
                atualizarCampoProduto(produtos, numProdutos, id, "quantidade");
                break;
            }
            case 5: {
                int id;
                printf("Digite o ID do produto para remover: ");
                scanf("%d", &id);
                removerProduto(produtos, &numProdutos, id);
                break;
            }
            case 6:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção invalida.\n");
        }

    } while (opcao != 6);

    return 0;
}

