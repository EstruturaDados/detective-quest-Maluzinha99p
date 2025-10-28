#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.
#define MAX_S 50

typedef struct No{
    char nome[MAX_S];
    struct No* esquerda;
    struct No* direita;
}No;

void menuPrincipal();
struct No* criarSala(const char* nome);
struct No* conectarSala(struct No* raiz, const char *nome);
struct No* explorarSalas(No* raiz, char* opcao);

int main() {

    // 🌱 Nível Novato: Mapa da Mansão com Árvore Binária
    //
    // - Crie uma struct Sala com nome, e dois ponteiros: esquerda e direita.
    // - Use funções como criarSala(), conectarSalas() e explorarSalas().
    // - A árvore pode ser fixa: Hall de Entrada, Biblioteca, Cozinha, Sótão etc.
    // - O jogador deve poder explorar indo à esquerda (e) ou à direita (d).
    // - Finalize a exploração com uma opção de saída (s).
    // - Exiba o nome da sala a cada movimento.
    // - Use recursão ou laços para caminhar pela árvore.
    // - Nenhuma inserção dinâmica é necessária neste nível.
    No* nome = NULL;
    char opcao[2];

    nome = conectarSala(nome, "Hall de Entrada");
    nome = conectarSala(nome, "Cozinha");
    nome = conectarSala(nome, "Sala de estar");
    nome = conectarSala(nome, "Varanda");
    nome = conectarSala(nome, "Quarto");
    nome = conectarSala(nome, "Banheiro");
    nome = conectarSala(nome, "Quarto");
    nome = conectarSala(nome, "Biblioteca");

    do{
        menuPrincipal();
        scanf(" %c", &opcao[0]);

        switch(opcao[0])
        {
            case 'e':
                printf("Comodo: %s\n",explorarSalas(&nome, opcao));
            break;
            case 'd':
                printf("Comodo: %s\n",explorarSalas(&nome, opcao));
            break;
            case 's':
                printf("Saindo do sistema...");
            break;
            default:
                printf("Opção inválida, por favor escolha a correta!\n\n");
            break;
        }
        sleep(1);
    }while(opcao[0] != 's');
    

    // 🔍 Nível Aventureiro: Armazenamento de Pistas com Árvore de Busca
    //
    // - Crie uma struct Pista com campo texto (string).
    // - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
    // - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
    // - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
    // - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
    // - Não precisa remover ou balancear a árvore.
    // - Use funções para modularizar: inserirPista(), listarPistas().
    // - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

    // 🧠 Nível Mestre: Relacionamento de Pistas com Suspeitos via Hash
    //
    // - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
    // - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
    // - A chave pode ser o nome do suspeito ou derivada das pistas.
    // - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
    // - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
    // - Adicione um contador para saber qual suspeito foi mais citado.
    // - Exiba ao final o “suspeito mais provável” baseado nas pistas coletadas.
    // - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
    // - Em caso de colisão, use lista encadeada para tratar.
    // - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

    return 0;
}

void menuPrincipal()
{
    printf("==================================\n");
    printf(" Escolha a opção que você deseja\n");
    printf("==================================\n");
    printf("E - esquerda\n");
    printf("D - direita\n");
    printf("S - sair do sistema\n");
    printf("-----------------------------------\n");
    printf("Ambiente atual: sla\n");
    printf("-----------------------------------\n");
    printf("Opção: ");
}

//FUNÇÃO DE CRIAR NÓ
struct No* criarSala(const char* nome)
{
    struct No* novo = (struct No*) malloc(sizeof(struct No));

    if(novo == NULL)
    {
        sleep(1);
        printf("Erro ao alocar memória!");
        return NULL;
    }

    strcpy(novo->nome, nome);

    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

//função para adicionar
struct No* conectarSala(struct No* raiz, const char *nome)
{
    if(raiz == NULL)
    {
        return criarSala(nome);
    }
    
    if(strcmp(nome, raiz->nome) < 0)
    {
        raiz->esquerda = conectarSala(raiz->esquerda, nome);
    }
    else{
        raiz->direita = conectarSala(raiz->direita, nome);
    }

    return raiz;
}

struct No* explorarSalas(No* raiz, char* opcao)
{
    if(raiz == NULL)
    {
        printf("Comodo sem saída!\n");
        return NULL;
    }

    if(opcao == 'e')
    {
        return raiz->nome;
        explorarSalas(raiz->esquerda, opcao);
    }
    else
    {
        return raiz->nome;
        explorarSalas(raiz->direita, opcao);
    }
}