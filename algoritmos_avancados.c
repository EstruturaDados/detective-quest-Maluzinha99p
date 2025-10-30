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
struct No* conectarSala(struct No* raiz, const char *nome, const char* pista, struct Pista** arvorePistas);
struct No* explorarSalas(No* raiz, char opcao);

//FUNÇÕES DAS PISTAS
struct Pista* criarPistas(const char* pista);
struct Pista* conecatarPistas(struct Pista* raizP, const char* pista);
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

    nome = conectarSala(nome, "Hall de Entrada", "Pegadas de lama", &nomeP);
    nome = conectarSala(nome, "Cozinha", "Pedaços de caco de vidro", &nomeP);
    nome = conectarSala(nome, "Sala de estar", "Chave perdida", &nomeP);
    nome = conectarSala(nome, "Varanda", "Vasos quebrados", &nomeP);
    nome = conectarSala(nome, "Quarto", "Lençol machado", &nomeP);
    nome = conectarSala(nome, "Banheiro", "Arma jogada no chão", &nomeP);
    nome = conectarSala(nome, "Biblioteca", "Livros com páginas faltando", &nomeP);



    No* atual = nome;
    Pista* atualP = nomeP;

    do{
        menuPrincipal(atual);
        scanf(" %d", &opcao);

        switch(opcao)
        {
            case 1:
                atual = explorarSalas(atual, opcao);
                printf("Indo para: %s\n\n", atual->nome);
            break;

            case 2:
                atual = explorarSalas(atual, opcao);
                printf("Indo para: %s\n\n", atual->nome);
            break;

            case 3:
                printf("\n------------------\n");
                printf("LISTANDO AS PISTAS");
                printf("\n------------------\n");
                sleep(1);
                emOrdem(atualP);
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
struct No* conectarSala(struct No* raiz, const char *nome, const char* pista, struct Pista** arvorePistas)
{
    if (raiz == NULL)
    {
        *arvorePistas = conecatarPistas(*arvorePistas, pista);
        return criarSala(nome, pista);
    }

    if (strcmp(nome, raiz->nome) < 0)
    {
        raiz->esquerda = conectarSala(raiz->esquerda, nome, pista, arvorePistas);
    }
    else
    {
        raiz->direita = conectarSala(raiz->direita, nome, pista, arvorePistas);
    }

    *arvorePistas = conecatarPistas(*arvorePistas, pista);

    return raiz;

}

struct No* explorarSalas(No* raiz, char opcao)
{
    if(raiz == NULL)
    {
        printf("Comodo sem saída!\n");
        return NULL;
    }

    if(opcao == 1)
    {
        return raiz->esquerda;
    }
    else if(opcao == 2)
    {
        return raiz->direita;
    }
    else{
        printf("Não há salas nesse sentido!\n");
    }



    return raiz;
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
struct Pista* conecatarPistas(struct Pista* raizP, const char* pista)
{  
    if (raizP == NULL)
    {
        return criarPistas(pista);
    }
    if(strcmp(pista, raizP->nomeP) < 0)
    {
        raizP->esquerda = conecatarPistas(raizP->esquerda, pista);
    }
    else{
        raizP->direita = conecatarPistas(raizP->direita, pista);
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