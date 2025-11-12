#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


// Capacidade máxima da mochila
#define MAX_ITENS 10

// Estrutura para representar um item na mochila
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
} Item;

// Vetor estático que representa a mochila
Item mochila[MAX_ITENS];
// Contador para rastrear o número atual de itens na mochila
int num_itens = 0;

//Limpa o buffer de entrada. Importante após scanf("%d").
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Adiciona um novo item à mochila.
void adicionar_item() {
    if (num_itens >= MAX_ITENS) {
        printf("\n Mochila Cheia! Nao eh possivel adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome do item: ");
    // Leitura do nome (permite espaços)
    if (scanf(" %49[^\n]", mochila[num_itens].nome) != 1) {
        printf("Erro na leitura do nome.\n");
        limpar_buffer();
        return;
    }

    printf("Tipo do item (Ex: Pocao, Arma, Vestimenta): ");
    // Leitura do tipo (permite espaços)
    if (scanf(" %29[^\n]", mochila[num_itens].tipo) != 1) {
        printf("Erro na leitura do tipo.\n");
        limpar_buffer();
        return;
    }

    printf("Quantidade: ");
    if (scanf("%d", &mochila[num_itens].quantidade) != 1 || mochila[num_itens].quantidade <= 0) {
        printf("Erro: Quantidade invalida. Item nao adicionado.\n");
        limpar_buffer();
        return;
    }

    num_itens++;
    printf("\n Item '%s' adicionado com sucesso! (Total: %d/%d)\n", 
           mochila[num_itens - 1].nome, num_itens, MAX_ITENS);
}

//Lista todos os itens atualmente na mochila.
void listar_itens() {
    if (num_itens == 0) {
        printf("\n A mochila esta vazia!\n");
        return;
    }

    printf("\n--- Itens Cadastrados na Mochila (%d/%d) ---\n", num_itens, MAX_ITENS);
    printf("+--------------------+------------------+----------+\n");
    printf("| NOME               | TIPO             | QUANT.   |\n");
    printf("+--------------------+------------------+----------+\n");

    for (int i = 0; i < num_itens; i++) {
        // Formatação para tabela: %-ns alinha à esquerda com 'n' espaços
        printf("| %-18.18s | %-16.16s | %-8d |\n", 
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }

    printf("+--------------------+------------------+----------+\n");
}

/**
 * Remove um item da mochila pelo nome.
 * Implementa busca sequencial.
 */
void remover_item() {
    if (num_itens == 0) {
        printf("\n A mochila esta vazia, nada para remover.\n");
        return;
    }

    char nome_remover[50];
    printf("\n--- Remover Item ---\n");
    printf("Digite o NOME exato do item a ser removido: ");
    if (scanf(" %49[^\n]", nome_remover) != 1) {
        printf("Erro na leitura do nome.\n");
        limpar_buffer();
        return;
    }

    int indice_encontrado = -1;

    // Busca Sequencial (Obrigatoria para o Nível Novato)
    for (int i = 0; i < num_itens; i++) {
        // strcmp retorna 0 se as strings forem identicas
        if (strcmp(mochila[i].nome, nome_remover) == 0) {
            indice_encontrado = i;
            break; // Item encontrado, sai do loop
        }
    }

    if (indice_encontrado != -1) {
        // Item encontrado. Move os itens subsequentes uma posição para frente
        // Isso sobrescreve o item a ser removido
        for (int i = indice_encontrado; i < num_itens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }

        num_itens--; // Diminui o contador de itens
        printf("\n Item '%s' removido com sucesso.\n", nome_remover);
    } else {
        printf("\n Item '%s' nao encontrado na mochila.\n", nome_remover);
    }
}

//Exibe o menu de opcoes.
void exibir_menu() {
    printf("\n==================================\n");
    printf("|    Mochila do Aventureiro   |\n");
    printf("==================================\n");
    printf("| 1. Adicionar Item              |\n");
    printf("| 2. Remover Item por Nome       |\n");
    printf("| 3. Listar Todos os Itens       |\n");
    printf("| 0. Sair                        |\n");
    printf("==================================\n");
    printf("Escolha uma opcao: ");
}

//Funcao principal do programa.
int main() {
    int opcao;

    // Loop principal do programa
    do {
        exibir_menu();
        
        // Leitura da opcao
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida. Digite um numero.\n");
            limpar_buffer(); // Limpa o buffer após erro de leitura
            opcao = -1; // Garante que o loop continue
            continue;
        }
        
        // Limpa o buffer apos a leitura de um int, para nao atrapalhar a proxima leitura de string
        limpar_buffer(); 

        switch (opcao) {
            case 1:
                adicionar_item();
                break;
            case 2:
                remover_item();
                break;
            case 3:
                listar_itens();
                break;
            case 0:
                printf("\n Ate logo, Aventureiro! Mochila guardada.\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
