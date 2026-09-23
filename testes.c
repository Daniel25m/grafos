/* Testes da implementacao entregue em trabalho.c. */

#include <stdio.h>

#define main trabalho_main
#include "trabalho.c"
#undef main

static int total_checar;
static int total_ok;

static void checar(const char *descricao, int condicao)
{
    total_checar++;
    if (condicao) {
        total_ok++;
        printf("[OK] %s\n", descricao);
    } else {
        printf("[FALHOU] %s\n", descricao);
    }
}

static int grau_vertice(Vertice grafo[], int vertice)
{
    int grau = 0;
    Aresta *aresta = grafo[vertice].a;

    while (aresta != NULL) {
        grau++;
        aresta = aresta->prox;
    }

    return grau;
}

static void testar_arestas_e_conectividade(void)
{
    Vertice *grafo;
    const char *nomes[] = {"Ana", "Bruno", "Carla", "Duda"};

    criarGrafo(&grafo, 4, nomes);
    checar("grafo novo inicia sem contatos", grau_vertice(grafo, 0) == 0);
    checar("indice invalido e rejeitado", acrescentarAresta(grafo, 4, 0, 4) == 0);
    checar("indice negativo e rejeitado", acrescentarAresta(grafo, 4, -1, 1) == 0);
    checar("aresta valida e aceita", acrescentarAresta(grafo, 4, 0, 1) == 1);
    checar("aresta nao orientada aparece nos dois vertices",
        grau_vertice(grafo, 0) == 1 && grau_vertice(grafo, 1) == 1);
    checar("grafo parcialmente conectado nao e conexo", eConexo(grafo, 4) == 0);

    acrescentarAresta(grafo, 4, 1, 2);
    acrescentarAresta(grafo, 4, 2, 3);
    checar("cadeia que alcanca todos os vertices e conexa", eConexo(grafo, 4) == 1);

    destruirGrafo(&grafo, 4);
}

static void testar_consultas(void)
{
    Vertice *grafo;
    const char *nomes[] = {"Hub", "P1", "P2", "P3", "Isolado"};

    criarGrafo(&grafo, 5, nomes);
    acrescentarAresta(grafo, 5, 0, 1);
    acrescentarAresta(grafo, 5, 0, 2);
    acrescentarAresta(grafo, 5, 0, 3);

    checar("hub tem tres contatos", grau_vertice(grafo, 0) == 3);
    checar("pontas tem exatamente um contato",
        grau_vertice(grafo, 1) == 1 && grau_vertice(grafo, 2) == 1 &&
        grau_vertice(grafo, 3) == 1);
    checar("vertice isolado tem grau zero", grau_vertice(grafo, 4) == 0);
    checar("estrela com vertice isolado possui grupos isolados", eConexo(grafo, 5) == 0);

    /* As consultas tambem sao executadas para inspecao das mensagens. */
    exibirDetalhesRedeSocial(grafo, 5);
    destruirGrafo(&grafo, 5);
}

static void testar_laco_e_empate(void)
{
    Vertice *grafo;
    const char *nomes[] = {"A", "B", "C", "D"};

    criarGrafo(&grafo, 4, nomes);
    checar("laco valido e aceito", acrescentarAresta(grafo, 4, 0, 0) == 1);
    checar("laco ocupa uma entrada na lista", grau_vertice(grafo, 0) == 1);
    acrescentarAresta(grafo, 4, 1, 2);
    acrescentarAresta(grafo, 4, 1, 3);
    acrescentarAresta(grafo, 4, 2, 3);
    checar("empate de maior grau e calculado corretamente",
        grau_vertice(grafo, 1) == 2 && grau_vertice(grafo, 2) == 2 &&
        grau_vertice(grafo, 3) == 2);

    destruirGrafo(&grafo, 4);
}

static void testar_grafo_original(void)
{
    Vertice *grafo;
    const char *nomes[] = {
        "Ana Beatriz", "Bruno Ferreira", "Camila Duarte", "Diego Santos",
        "Eduarda Lima", "Felipe Costa", "Gabriela Rocha", "Henrique Alves",
        "Isabela Martins", "Joao Pedro", "Karina Souza", "Lucas Oliveira",
        "Mariana Pires", "Nicolas Barros", "Otavio Ramos", "Paula Fernandes",
        "Quesia Nogueira", "Rafael Teixeira", "Sofia Cardoso", "Thiago Almeida"
    };
    int conexoes[][2] = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7},
        {1, 8}, {2, 9}, {3, 10}, {4, 11}, {5, 12}, {6, 13},
        {8, 9}, {8, 15}, {10, 11}, {12, 13}, {13, 14}, {14, 15},
        {16, 17}
    };
    int quantidade_conexoes = sizeof(conexoes) / sizeof(conexoes[0]);
    int conexao_index;

    criarGrafo(&grafo, 20, nomes);
    for (conexao_index = 0; conexao_index < quantidade_conexoes; conexao_index++)
        acrescentarAresta(grafo, 20, conexoes[conexao_index][0], conexoes[conexao_index][1]);

    checar("Ana Beatriz tem o maior grau, igual a 7", grau_vertice(grafo, 0) == 7);
    checar("Henrique Alves tem exatamente um contato", grau_vertice(grafo, 7) == 1);
    checar("Quesia Nogueira tem exatamente um contato", grau_vertice(grafo, 16) == 1);
    checar("Rafael Teixeira tem exatamente um contato", grau_vertice(grafo, 17) == 1);
    checar("Sofia Cardoso nao tem contatos", grau_vertice(grafo, 18) == 0);
    checar("Thiago Almeida nao tem contatos", grau_vertice(grafo, 19) == 0);
    checar("o grafo original possui grupos isolados", eConexo(grafo, 20) == 0);

    destruirGrafo(&grafo, 20);
}

int main(void)
{
    testar_arestas_e_conectividade();
    testar_consultas();
    testar_laco_e_empate();
    testar_grafo_original();

    printf("\nRESUMO: %d de %d checagens passaram.\n", total_ok, total_checar);
    return total_ok == total_checar ? 0 : 1;
}
