#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<memory.h>

// implementacao de um grafo usando uma lista de adjacencia

// celula de uma lista de arestas
typedef struct aresta {
	int    outroExtremo;
	struct aresta *prox;
} Aresta;

// cada vertice possui um ponteiro para sua lista de arestas incidentes
typedef struct vertice{
	int nome;
	Aresta *a;
} Vertice;

// declaracoes das funcoes para manipulacao de grafos
void criarGrafo(Vertice **G, int ordem);
void destruirGrafo(Vertice **G, int ordem);
int  acrescentarAresta(Vertice G[], int ordem, int v1, int v2);
void imprimirGrafo(Vertice G[], int ordem);

// cria um grafo com a ordem informada e inicialmente sem arestas
void criarGrafo(Vertice **G, int ordem)
{
	int i;
	*G = (Vertice *) malloc(sizeof(Vertice) * ordem); /* aloca memoria para um vetor de vertices */
	
	for(i = 0; i < ordem; i++) {
		(*G)[i].nome= i;
		(*G)[i].a= NULL;    /* deixa o vertice sem arestas incidentes */
	}
}

// desaloca a memoria dinamica usada para armazenar um grafo
void destruirGrafo(Vertice **G, int ordem){
	int i;
    Aresta *p, *n;
    
	for(i=0; i<ordem; i++){ /* remove a lista de adjacencia de cada vertice */
	    p = (*G)[i].a;
        while (p!= NULL){
              n= p->prox;
              free(p);
              p= n;
        }
	}
	free(*G);  /* remove o vetor de vertices */
}

// acrescenta uma nova aresta em um grafo previamente criado
// para um grafo nao orientado, armazena as duas direcoes da aresta
int acrescentarAresta(Vertice G[], int ordem, int v1, int v2){
    Aresta * A1, *A2;
    
	if (v1<0 || v1 >= ordem) /* testa se o primeiro vertice e valido */
	   return 0;
	if (v2<0 || v2 >= ordem)
	   return 0;
	
	/* acrescenta a aresta na lista do vertice v1 */
	A1 = (Aresta *) malloc(sizeof(Aresta));
	A1->outroExtremo = v2;
	A1->prox = G[v1].a;
	G[v1].a = A1;

	if (v1 == v2) return 1; /* a aresta e um laco */

	/* acrescenta a aresta na lista do vertice v2 */	
	A2= (Aresta *) malloc(sizeof(Aresta));
	A2->outroExtremo = v1;
	A2->prox = G[v2].a;
	G[v2].a = A2;
	
	return 1;
}


// imprime um grafo com uma notacao similar a uma lista de adjacencia
void imprimirGrafo(Vertice G[], int ordem){
	int i;
	Aresta *aux;

	printf("\nOrdem:   %d",ordem);
	printf("\nLista de Adjacencia:\n");

	for (i=0; i<ordem; i++){
		printf("\n    v%d: ", i);
		aux= G[i].a;
		for( ; aux != NULL; aux= aux->prox)
			printf("  v%d", aux->outroExtremo);
	}
	printf("\n\n");

}

// programa simples para testar a representacao do grafo
int main(int argc, char *argv[]) 
{
    int i;
	Vertice *G;
	int ordemG = 8; /* vertices identificados de 0 ate 7 */
		
	criarGrafo(&G, ordemG);
	acrescentarAresta(G,ordemG,0,1);
	acrescentarAresta(G,ordemG,0,2);
	acrescentarAresta(G,ordemG,0,7);
	acrescentarAresta(G,ordemG,2,4);
	acrescentarAresta(G,ordemG,2,5);
	acrescentarAresta(G,ordemG,2,5);
	acrescentarAresta(G,ordemG,3,5);
	acrescentarAresta(G,ordemG,4,6);
	acrescentarAresta(G,ordemG,3,6);
	acrescentarAresta(G,ordemG,7,7);

	imprimirGrafo(G, ordemG);
       
	destruirGrafo(&G, ordemG);
	
	printf("Pressione uma tecla para terminar\n");
    getchar();
	return(0);
}