/* 	Integrantes: 
	- Daniel Monteiro Malacarne - 10420454; 
	- Murillo Henrique Sakamoto - 10426242 
	- Beatriz Bellini - 10419741 */

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
	const char *nome;
	Aresta *a;
} Vertice;

// declaracoes das funcoes para manipulacao de grafos
void criarGrafo(Vertice **G, int ordem, const char *nomes[]);
void destruirGrafo(Vertice **G, int ordem);
int  acrescentarAresta(Vertice G[], int ordem, int v1, int v2);
void imprimirGrafo(Vertice G[], int ordem);
void listarUsuariosSemContatos(Vertice G[], int ordem);
void listarUsuariosComUmContato(Vertice G[], int ordem);
void listarUsuariosComMaisContatos(Vertice G[], int ordem);
int eConexo(Vertice G[], int ordem);
void exibirDetalhesRedeSocial(Vertice G[], int ordem);

// cria um grafo com a ordem informada e inicialmente sem arestas
void criarGrafo(Vertice **G, int ordem, const char *nomes[])
{
	int i;
	*G = (Vertice *) malloc(sizeof(Vertice) * ordem); /* aloca memoria para um vetor de vertices */
	
	for(i = 0; i < ordem; i++) {
		(*G)[i].nome = nomes[i];
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


// imprime os contatos da turma usando somente os nomes dos usuários
void imprimirGrafo(Vertice G[], int ordem){
	int i;
	Aresta *aux;

	printf("\nContatos da turma:\n");

	for (i=0; i<ordem; i++){
		printf("\n    %s: ", G[i].nome);
		aux= G[i].a;
		for( ; aux != NULL; aux= aux->prox)
			printf("  %s", G[aux->outroExtremo].nome);
	}
	printf("\n\n");

}

/* lista os usuários cujo grau é zero, isto é, sem nenhuma aresta incidente. */
void listarUsuariosSemContatos(Vertice G[], int ordem){
	int i;
	int encontrou = 0;

	printf("Usuários que não contatam ninguém da turma:\n");
	for (i = 0; i < ordem; i++) {
		if (G[i].a == NULL) {
			printf("- %s\n", G[i].nome);
			encontrou = 1;
		}
	}

	if (!encontrou)
		printf("- Todos os usuários possuem pelo menos um contato.\n");
	printf("\n");
}

/* percorre cada lista de adjacência e seleciona os usuários de grau um. */
void listarUsuariosComUmContato(Vertice G[], int ordem){
	int i;
	int quantidadeContatos;
	int encontrou = 0;
	Aresta *aux;

	printf("Usuários que contatam exatamente uma pessoa da turma:\n");
	for (i = 0; i < ordem; i++) {
		quantidadeContatos = 0;
		for (aux = G[i].a; aux != NULL; aux = aux->prox)
			quantidadeContatos++;

		if (quantidadeContatos == 1) {
			printf("- %s\n", G[i].nome);
			encontrou = 1;
		}
	}

	if (!encontrou)
		printf("- Nenhum usuário possui exatamente um contato.\n");
	printf("\n");
}

/* encontra o maior grau e lista todos os usuários que possuem esse grau. */
void listarUsuariosComMaisContatos(Vertice G[], int ordem){
	int i;
	int quantidadeContatos;
	int maiorGrau = 0;
	Aresta *aux;

	for (i = 0; i < ordem; i++) {
		quantidadeContatos = 0;
		for (aux = G[i].a; aux != NULL; aux = aux->prox)
			quantidadeContatos++;

		if (quantidadeContatos > maiorGrau)
			maiorGrau = quantidadeContatos;
	}

	printf("Usuário(s) com mais contatos na turma:\n");
	for (i = 0; i < ordem; i++) {
		quantidadeContatos = 0;
		for (aux = G[i].a; aux != NULL; aux = aux->prox)
			quantidadeContatos++;

		if (quantidadeContatos == maiorGrau)
			printf("- %s\n", G[i].nome);
	}
	printf("\n");
}

/*
 * marca o vertice inicial e propaga a marca pelas arestas. quando nenhuma
 * nova marca puder ser feita, o grafo e conexo somente se todos os vertices
 * tiverem sido alcancados.
 */
int eConexo(Vertice G[], int ordem){
	int i;
	int houveNovoVertice;
	int todosMarcados = 1;
	int *marcado;
	Aresta *aux;

	if (ordem <= 0)
		return 0;

	marcado = (int *) calloc(ordem, sizeof(int));
	if (marcado == NULL)
		return 0;

	marcado[0] = 1;
	do {
		houveNovoVertice = 0;
		for (i = 0; i < ordem; i++) {
			if (!marcado[i])
				continue;

			for (aux = G[i].a; aux != NULL; aux = aux->prox) {
				if (!marcado[aux->outroExtremo]) {
					marcado[aux->outroExtremo] = 1;
					houveNovoVertice = 1;
				}
			}
		}
	} while (houveNovoVertice);

	for (i = 0; i < ordem; i++) {
		if (!marcado[i]) {
			todosMarcados = 0;
			break;
		}
	}

	free(marcado);
	return todosMarcados;
}

/* reune as consultas e a lista de adjacencia em um unico relatorio. */
void exibirDetalhesRedeSocial(Vertice G[], int ordem){
	printf("\n========== DETALHES DA REDE SOCIAL ==========\n");
	imprimirGrafo(G, ordem);
	listarUsuariosSemContatos(G, ordem);
	listarUsuariosComUmContato(G, ordem);
	listarUsuariosComMaisContatos(G, ordem);

	if (eConexo(G, ordem))
		printf("A turma forma um único grupo conectado.\n\n");
	else
		printf("A turma possui grupos isolados e não é totalmente conectada.\n\n");
}

// constroi a rede da turma, exibe suas consultas e libera a memoria alocada.
int main(int argc, char *argv[]) 
{
    int i;
	Vertice *G;
	int ordemG = 20; /* vertices identificados de 0 ate 19 */
	const char *nomes[] = {
		"Ana Beatriz", "Bruno Ferreira", "Camila Duarte", "Diego Santos",
		"Eduarda Lima", "Felipe Costa", "Gabriela Rocha", "Henrique Alves",
		"Isabela Martins", "João Pedro", "Karina Souza", "Lucas Oliveira",
		"Mariana Pires", "Nicolas Barros", "Otávio Ramos", "Paula Fernandes",
		"Quésia Nogueira", "Rafael Teixeira", "Sofia Cardoso", "Thiago Almeida"
	};
		
	criarGrafo(&G, ordemG, nomes);
	acrescentarAresta(G,ordemG,0,1);
	acrescentarAresta(G,ordemG,0,2);
	acrescentarAresta(G,ordemG,0,3);
	acrescentarAresta(G,ordemG,0,4);
	acrescentarAresta(G,ordemG,0,5);
	acrescentarAresta(G,ordemG,0,6);
	acrescentarAresta(G,ordemG,0,7);
	acrescentarAresta(G,ordemG,1,8);
	acrescentarAresta(G,ordemG,2,9);
	acrescentarAresta(G,ordemG,3,10);
	acrescentarAresta(G,ordemG,4,11);
	acrescentarAresta(G,ordemG,5,12);
	acrescentarAresta(G,ordemG,6,13);
	acrescentarAresta(G,ordemG,8,9);
	acrescentarAresta(G,ordemG,8,15);
	acrescentarAresta(G,ordemG,10,11);
	acrescentarAresta(G,ordemG,12,13);
	acrescentarAresta(G,ordemG,13,14);
	acrescentarAresta(G,ordemG,14,15);
	acrescentarAresta(G,ordemG,16,17);

	exibirDetalhesRedeSocial(G, ordemG);
       
	destruirGrafo(&G, ordemG);
	
	printf("Pressione uma tecla para terminar\n");
    getchar();
	return(0);
}