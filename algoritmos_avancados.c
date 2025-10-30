#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.
#define MAX_S 50

typedef struct No{
    char nome[MAX_S];
    char pistas[MAX_S];
    struct No* esquerda;
    struct No* direita;
}No;

typedef struct Pista{
    char nomeP[MAX_S];
    struct Pista* esquerda;
    struct Pista* direita;
}Pista;

struct No* menuPrincipal(No* raiz);
struct No* criarSala(const char* nome, const char* pista);
struct No* conectarSala(struct No* raiz, const char *nome, const char* pista);
struct No* explorarSalas(No* raiz, int opcao, struct Pista** arvorePistas);

//FUNÇÕES DAS PISTAS
struct Pista* criarPistas(const char* pista);
struct Pista* conectarPistas(struct Pista* raizP, const char* pista);
void emOrdem(struct Pista* raizP);



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

    setlocale(LC_ALL, "");
    No* nome = NULL;
    Pista* nomeP = NULL;


    int opcao;

    nome = conectarSala(nome, "Hall de Entrada", "Pegadas de lama");
    nome = conectarSala(nome, "Cozinha", "Pedaços de caco de vidro");
    nome = conectarSala(nome, "Sala de estar", "Chave perdida");
    nome = conectarSala(nome, "Varanda", "Vasos quebrados");
    nome = conectarSala(nome, "Quarto", "Lençol machado");
    nome = conectarSala(nome, "Banheiro", "Arma jogada no chão");
    nome = conectarSala(nome, "Biblioteca", "Livros com páginas faltando");



    No* atual = nome;
    Pista* atualP = nomeP;

    do{
        menuPrincipal(atual);
        scanf(" %d", &opcao);

        switch(opcao)
        {
            case 1:
                atual = explorarSalas(atual, opcao, &nomeP);
                printf("Indo para: %s\n\n", atual->nome);
            break;

            case 2:
                atual = explorarSalas(atual, opcao, &nomeP);
                printf("Indo para: %s\n\n", atual->nome);
            break;

            case 3:
                printf("\n------------------\n");
                printf("LISTANDO AS PISTAS");
                printf("\n------------------\n");
                sleep(1);
                emOrdem(nomeP);
                printf("------------------\n");
            break;

            case 0:
                printf("Saindo do sistema...");
            break;
            default:
                printf("Opção inválida, por favor escolha a correta!\n\n");
            break;
        }

        sleep(1);
    }while(opcao != 0);

    return 0;
}

struct No* menuPrincipal(No* raiz)
{
    printf("==================================\n");
    printf(" Escolha a opção que você deseja\n");
    printf("==================================\n");
    printf("1 - Ir para esquerda\n");
    printf("2 - Ir para direita\n");
    printf("3 - Listar Pistas\n");
    printf("0 - sair do sistema\n");
    printf("-----------------------------------\n");
    printf("Comodo atual: %s\nPista encontrada: %s\n", raiz->nome, raiz->pistas);
    printf("-----------------------------------\n");
    printf("Opção: ");
}

////////////////////////////// FUNÇÕES DA ÁRVORE DOS COMODOS //////////////////////////////////
//FUNÇÃO DE CRIAR NÓ
struct No* criarSala(const char* nome, const char* pista)
{
    struct No* novo = (struct No*) malloc(sizeof(struct No));

    if(novo == NULL)
    {
        sleep(1);
        printf("Erro ao alocar memória!");
        return NULL;
    }

    strcpy(novo->nome, nome);
    strcpy(novo->pistas, pista);
    novo->esquerda = NULL;
    novo->direita = NULL;

    return novo;
}

//função para adicionar
struct No* conectarSala(struct No* raiz, const char *nome, const char* pista)
{
    if (raiz == NULL)
    {
        return criarSala(nome, pista);
    }

    if (strcmp(nome, raiz->nome) < 0)
    {
        raiz->esquerda = conectarSala(raiz->esquerda, nome, pista);
    }
    else
    {
        raiz->direita = conectarSala(raiz->direita, nome, pista);
    }

    return raiz;
}

struct No* explorarSalas(No* raiz, int opcao, struct Pista** arvorePistas)
{
    if (raiz == NULL)
    {
        printf("Cômodo sem saída!\n");
        return NULL;
    }

    No* proximo = NULL;

    if (opcao == 1)
    {
        proximo = raiz->esquerda;
    }
    else if (opcao == 2)
    {
        proximo = raiz->direita;
    }
    else
    {
        printf("Não há salas nesse sentido!\n");
        return raiz;
    }

    if (proximo != NULL)
    {
        // Agora sim: adiciona a pista da sala para onde foi
        *arvorePistas = conectarPistas(*arvorePistas, proximo->pistas);
    }
    else
    {
        printf("Não há sala nesse lado!\n");
    }

    return proximo;
}


//////////////////////////// FUNÇÕES DA ÁRVORE DAS PISTAS ///////////////////////////////////
//CRIANDO AS PISTAS
struct Pista* criarPistas(const char* pista)
{
    struct Pista* novaP = (struct Pista*) malloc(sizeof(struct Pista));

    if (novaP == NULL)
    {
        printf("Erro ao alocar memória...");
        sleep(1);
        return NULL;
    }

    strcpy(novaP->nomeP, pista);
    novaP->esquerda = NULL;
    novaP->direita = NULL;

    return novaP;
}


//CONECTANDO AS PISTAS
struct Pista* conectarPistas(struct Pista* raizP, const char* pista)
{  
    if (raizP == NULL)
    {
        return criarPistas(pista);
    }
    if(strcmp(pista, raizP->nomeP) < 0)
    {
        raizP->esquerda = conectarPistas(raizP->esquerda, pista);
    }
    else{
        raizP->direita = conectarPistas(raizP->direita, pista);
    }
    return raizP;
}

//ORDENANDO AS PITAS EM ORDEM ALFABÉTICA
void emOrdem(struct Pista* raizP)
{
    if(raizP != NULL)
    {
        emOrdem(raizP->esquerda);
        printf("%s\n", raizP->nomeP);
        emOrdem(raizP->direita);
    }
}