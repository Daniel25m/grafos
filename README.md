# Grafos

Implementação em C de um grafo não orientado representado por listas de
adjacência.

## Sobre o projeto

Cada vértice possui uma lista ligada de arestas incidentes. O programa cria um
grafo com 20 vértices, adiciona as conexões entre os usuários e imprime a lista
de adjacência de cada vértice.

Uma aresta entre os vértices `v1` e `v2` é armazenada nas listas dos dois
vértices. Laços, como uma aresta de `v7` para `v7`, são tratados sem duplicar a
estrutura.

## Estruturas principais

- `Vertice`: armazena o nome do vértice e o ponteiro para sua lista de arestas.
- `Aresta`: armazena o outro extremo da aresta e o ponteiro para o próximo item
  da lista.

## Funções

- `criarGrafo`: aloca e inicializa o vetor de vértices.
- `acrescentarAresta`: adiciona uma aresta entre dois vértices válidos.
- `imprimirGrafo`: exibe o grafo em formato de lista de adjacência.
- `destruirGrafo`: libera as listas de arestas e o vetor de vértices.

## Compilação e execução

Com o GCC instalado, execute:

```bash
gcc -Wall -Wextra -pedantic trabalho.c -o trabalho
./trabalho
```

Ao final da execução, o programa aguarda uma tecla para ser encerrado.

## Arquivos

- `trabalho.c`: implementação principal do grafo que iremos entregar.
- `testes.c`: arquivo destinado a testes adicionais.
- `pdf.txt`: link para acessar pdf que precisamos entregar.
- `projeto-rede-social.pdf`: descritivo do projeto.
- `TODO.md`: coisas pendentes do projeto.